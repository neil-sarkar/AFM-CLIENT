#include "builder.h"
#include "afm.h"
#include "dac.h"
#include "adc.h"
#include "pga.h"
#include "dds.h"
#include "serial_port.h"
#include "send_worker.h"
#include "sweeper.h"
#include "receive_worker.h"
#include "constants.h"
#include "approacher.h"
#include "scanner.h"
#include "globals.h"
#include "force_curve_generator.h"
#include <iostream>
#include <iomanip>
#include <QFinalState>
#include <QImage>
#include <QBuffer>

Builder::Builder() {}

AFM* Builder::build_afm() {
    // Create the collection of DACs
    QHash<int, AFMObject*> dac_collection;
    dac_collection[DAC::Buffered_1] = new DAC(DAC::Buffered_1);
    dac_collection[DAC::Buffered_2] = new DAC(DAC::Buffered_2);
    dac_collection[DAC::Board_2] = new DAC(DAC::Board_2);
    dac_collection[DAC::Z_Amplitude] = new DAC(DAC::Z_Amplitude);
    dac_collection[DAC::Board_1] = new DAC(DAC::Board_1);
    dac_collection[DAC::Buffered_3] = new DAC(DAC::Buffered_3);
    dac_collection[DAC::Z_Offset_Fine] = new DAC(DAC::Z_Offset_Fine);
    dac_collection[DAC::Y_1] = new DAC(DAC::Y_1);
    dac_collection[DAC::Z_Offset_Coarse] = new DAC(DAC::Z_Offset_Coarse);
    dac_collection[DAC::Y_2] = new DAC(DAC::Y_2);
    dac_collection[DAC::X_1] = new DAC(DAC::X_1);
    dac_collection[DAC::X_2] = new DAC(DAC::X_2);

    // Create the collection of ADC
    QHash<int, AFMObject*> adc_collection;
    adc_collection[ADC::X_1] = new ADC(ADC::X_1);
    adc_collection[ADC::X_2] = new ADC(ADC::X_2);
    adc_collection[ADC::Y_1] = new ADC(ADC::Y_1);
    adc_collection[ADC::Y_2] = new ADC(ADC::Y_2);
    adc_collection[ADC::Z] = new ADC(ADC::Z);
    adc_collection[ADC::Z_Piezoresistor_Amplitude] = new ADC(ADC::Z_Piezoresistor_Amplitude);
    adc_collection[ADC::Phase] = new ADC(ADC::Phase);

    // PGA
    QHash<int, AFMObject*> pga_collection;
    pga_collection[PGA::X_1] = new PGA(PGA::X_1);
    pga_collection[PGA::X_2] = new PGA(PGA::X_2);
    pga_collection[PGA::Y_1] = new PGA(PGA::Y_1);
    pga_collection[PGA::Y_2] = new PGA(PGA::Y_2);
    pga_collection[PGA::Z_Fine] = new PGA(PGA::Z_Fine);
    pga_collection[PGA::DDS_Amplitude] = new PGA(PGA::DDS_Amplitude);
    pga_collection[PGA::Z_Coarse] = new PGA(PGA::Z_Coarse);
    pga_collection[PGA::Leveling] = new PGA(PGA::Leveling);

    PID* pid = new PID();
    Motor* motor = new Motor();
    Scanner* scanner = new Scanner(pid, dac_collection[DAC::Z_Offset_Fine]);
    Approacher* approacher = new Approacher(pid, adc_collection[ADC::Z_Piezoresistor_Amplitude]);
    Sweeper* sweeper = new Sweeper(pid);
    sweeper->dds = new DDS();
    ForceCurveGenerator* force_curve_generator = new ForceCurveGenerator();
    return new AFM(pga_collection, dac_collection, adc_collection, motor, sweeper, approacher, scanner, force_curve_generator);
}


void Builder::wire_hash_command_generated(QHash<int, AFMObject*> & collection, SendWorker* & send_worker) {
    QHash<int, AFMObject*>::iterator i;
    for (i = collection.begin(); i != collection.end(); ++i)
        QObject::connect(i.value(), SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
}

void Builder::wire(AFM* & afm, SerialPort* & serial_port, SendWorker* & send_worker, ReceiveWorker* & receive_worker) {
    // Wire command_generated signal
//     TODO: There is likely a cleaner way to connect all the command_generated SIGNALS to the enqueue_command SLOT as command_generated is inherited from AFMObject
     QObject::connect(afm, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
     QObject::connect(afm->motor, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
     QObject::connect(afm->scanner, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
     QObject::connect(afm->scanner->pid, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
     QObject::connect(afm->sweeper, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
     QObject::connect(afm->sweeper->dds, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
     QObject::connect(afm->approacher, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
     QObject::connect(afm->force_curve_generator, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
     wire_hash_command_generated(afm->ADC_collection, send_worker);
     wire_hash_command_generated(afm->DAC_collection, send_worker);
     wire_hash_command_generated(afm->PGA_collection, send_worker);

    // Async serial communication handling (when the MCU sends a message without us making an associated call for that message)
    QObject::connect(receive_worker, SIGNAL(prompt_dac_table_reset()), afm, SLOT(set_dac_table()));
    QObject::connect(afm, SIGNAL(dac_table_set()), afm, SLOT(init()));
    QObject::connect(serial_port, SIGNAL(resetting_mcu()), send_worker, SLOT(flush()), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(resetting_mcu()), receive_worker, SLOT(flush()), Qt::DirectConnection);
    QObject::connect(receive_worker, SIGNAL(auto_approach_info_received(QByteArray)), afm->approacher, SLOT(handle_auto_approach_info_message(QByteArray))); // why isn't this a qt direct connection
    QObject::connect(afm, SIGNAL(trigger_mcu_reset()), serial_port, SLOT(reset_mcu()));
    QObject::connect(receive_worker, SIGNAL(send_next_command()), send_worker, SLOT(dequeue_command()));
    QObject::connect(serial_port, SIGNAL(disconnected()), afm, SIGNAL(disconnected()));

    // Misc connections
    QObject::connect(serial_port, SIGNAL(message_sent(CommandNode*)), receive_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(byte_received(char)), receive_worker, SLOT(enqueue_response_byte(char)), Qt::DirectConnection);
    QObject::connect(send_worker, SIGNAL(command_dequeued(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));

    // Internal object connections
    QObject::connect(receive_worker, SIGNAL(response_byte_received()), receive_worker, SLOT(build_working_response()));
    QObject::connect(send_worker, SIGNAL(send_command_immediately()), send_worker, SLOT(dequeue_command()));
}

void Builder::generate_command_nodes() {
    QString path = ":/static/command_spec.tsv";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
       qDebug() << file.errorString();

    char delimiter = 0x9; // delimit with a tab in our tab separated values file
    int message_index, in_use_index, id_index, num_send_bytes_index, num_receive_bytes_index;
    QList<QByteArray> header_line = file.readLine().split(delimiter); // read the first line of the file to understand how the csv is laid out
    // In the worst way possible, extract the indices of the important information
    for (int i = 0; i < header_line.length(); i++) {
       QByteArray header = header_line[i].toLower();
       if (header == "message") {
           message_index = i;
       } else if (header == "in use") {
           in_use_index = i;
       } else if (header == "id") {
           id_index = i;
       } else if (header == "send byte length") {
           num_send_bytes_index = i;
       } else if (header == "reply msg length") {
           num_receive_bytes_index = i;
       }
    }

    while (!file.atEnd()) {
       QList<QByteArray> line = file.readLine().split(delimiter); // tab separated values
       if (line[in_use_index] == "1") {
           CommandNode node = CommandNode(); // create a new CommandNode
           node.id= bytes_to_int(line[id_index], line, 16);
           node.num_send_bytes = bytes_to_int(line[num_send_bytes_index], line, 10);
           node.num_receive_bytes = bytes_to_int(line[num_receive_bytes_index], line, 10);
           command_hash[line[message_index]] = node;
       }
    }
    qDebug() << "Loaded " << command_hash.size() << "command node types.";
}

int Builder::bytes_to_int(QByteArray bytes, QList<QByteArray> line, int base) {
    bytes = bytes.simplified(); // remove any newlines or carriage returns [MIGHT CAUSE ISSUES]
    bool conversion_successful; // need this to call toInt() method below
    int result = bytes.toInt(&conversion_successful, base);

    if (conversion_successful)
        return result;
    return -1;
}

QColor Builder::interpolate_color(double percent, QVector<QColor> colors) {
    double bucket_size = 100.0 / (colors.length() - 1);
//    qDebug() << bucket_size << colors.length();
    for (int i = 1; i < colors.length(); i++) {
        if (percent > bucket_size * i)
            continue;
        double factor = (bucket_size * i - percent) / (bucket_size);
        qDebug() << i << factor;
        int r1, g1, b1;
        r1 = colors[i].red();
        g1= colors[i].green();
        b1 = colors[i].blue();
        int r0, g0, b0;
        r0 = colors[i -1].red();
        g0= colors[i - 1].green();
        b0 = colors[i -1].blue();
//        int *r0, *g0, *b0;
//        colors[i - 1].getRgb(r0, g0, b0);
        int mixed_r = r1 * (1-factor) + r0 * factor;
        int mixed_g = g1 * (1-factor) + g0 * factor;
        int mixed_b = b1 * (1-factor) + b0 * factor;
        return QColor(std::min(mixed_r, 255), std::min(mixed_g, 255), std::min(mixed_b, 255));
    }
}

void Builder::generate_color_map() {
    QVector<QColor> colors;
    colors.append(QColor(88,28,0));
    colors.append(QColor(188,128,0));
    colors.append(QColor(252,252,128));

    for (int i = 0; i < 100; i += 0.01) {
        color_map[i] = interpolate_color(i, colors);
    }
//    QImage image(1, 100, QImage::Format_RGB32);
//    QColor value;
//    for (int i = 0; i < 100; i++) {
//            value = color_map[i];
//            int r1, g1, b1;
//            value.getRgb(&r1, &g1, &b1);
//            image.setPixel(0, i, qRgb(r1,g1,b1));
//        }
//    QByteArray ba;
//    QBuffer buffer(&ba);
//    buffer.open(QIODevice::WriteOnly);
//    image.save(&buffer, "PNG"); // writes image into ba in PNG format
//    qDebug() << ba.toBase64();
}
