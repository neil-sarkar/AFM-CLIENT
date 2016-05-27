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
#include "pin_map.h"

Builder::Builder() {}

AFM* Builder::build_afm() {
    PinMap p;

    // Create the collection of DACs
    peripheral_collection dac_collection;
    for (int i = 0; i < p.dac_array.length(); i++) {
        dac_collection[p.dac_array[i].name] = new DAC(p.dac_array[i].id);
    }
    // Create the collection of ADC
    peripheral_collection adc_collection;
    for (int i = 0; i < p.adc_array.length(); i++) {
        adc_collection[p.adc_array[i].name] = new ADC(p.adc_array[i].id);
    }

    // PGA
    peripheral_collection pga_collection;
    for (int i = 0; i < p.pga_array.length(); i++) {
        pga_collection[p.pga_array[i].name] = new PGA(p.pga_array[i].id, p.pga_array[i].default_value);
    }

    PID* pid = new PID();
    Motor* motor = new Motor();
    Scanner* scanner = new Scanner(pid, dac_collection["z_offset_fine"]);
    Approacher* approacher = new Approacher(pid, adc_collection["z_piezoresistor_amplitude"]);
    Sweeper* sweeper = new Sweeper(pid);
    sweeper->dds = new DDS();
    ForceCurveGenerator* force_curve_generator = new ForceCurveGenerator();

    return new AFM(pga_collection, dac_collection, adc_collection, motor, sweeper, approacher, scanner, force_curve_generator);
}


void Builder::wire_hash_command_generated(peripheral_collection & collection, SendWorker* & send_worker) {
    peripheral_collection::iterator i;
    for (i = collection.begin(); i != collection.end(); ++i)
        QObject::connect(i.value(), SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
}

void Builder::wire(AFM* & afm, SerialPort* & serial_port, SendWorker* & send_worker, ReceiveWorker* & receive_worker) {
    // Wire command_generated signal
//     TODO: There is likely a cleaner way to connect all the command_generated SIGNALS to the enqueue_command SLOT as command_generated is inherited from AFMObject
     QObject::connect(afm, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
     QObject::connect(afm->motor, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
     QObject::connect(afm->scanner, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
     QObject::connect(afm->scanner->pid, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
     QObject::connect(afm->sweeper, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
     QObject::connect(afm->sweeper->dds, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
     QObject::connect(afm->approacher, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
     QObject::connect(afm->force_curve_generator, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::QueuedConnection);
     wire_hash_command_generated(afm->ADC_collection, send_worker);
     wire_hash_command_generated(afm->DAC_collection, send_worker);
     wire_hash_command_generated(afm->PGA_collection, send_worker);

    // Async serial communication handling (when the MCU sends a message without us making an associated call for that message)
     QObject::connect(serial_port, SIGNAL(connected()), afm, SLOT(init()));
    QObject::connect(serial_port, SIGNAL(resetting_mcu()), send_worker, SLOT(flush()), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(resetting_mcu()), receive_worker, SLOT(flush()), Qt::DirectConnection);
    QObject::connect(receive_worker, SIGNAL(auto_approach_info_received(QByteArray)), afm->approacher, SLOT(handle_auto_approach_info_message(QByteArray))); // why isn't this a qt direct connection
    QObject::connect(afm, SIGNAL(trigger_mcu_reset()), serial_port, SLOT(reset_mcu()));
    QObject::connect(receive_worker, SIGNAL(receive_returned()), send_worker, SLOT(handle_receive_return()), Qt::QueuedConnection);
    QObject::connect(serial_port, SIGNAL(disconnected()), afm, SIGNAL(disconnected()));

    // Misc connections
    QObject::connect(serial_port, SIGNAL(message_sent(CommandNode*)), receive_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(byte_received(char)), receive_worker, SLOT(enqueue_response_byte(char)), Qt::DirectConnection);
    QObject::connect(send_worker, SIGNAL(command_dequeued(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));
    QObject::connect(receive_worker, SIGNAL(resend_command(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));
    QObject::connect((PGA*)afm->PGA_collection[QString("fine_z")], SIGNAL(value_changed(double)), afm->scanner, SLOT(update_z_actuator_scale_factor(double)));
    QObject::connect((PGA*)afm->PGA_collection[QString("x_1")], SIGNAL(value_changed(double)), afm->scanner, SLOT(update_x_actuator_scale_factor(double)));
    QObject::connect((PGA*)afm->PGA_collection[QString("y_1")], SIGNAL(value_changed(double)), afm->scanner, SLOT(update_y_actuator_scale_factor(double)));

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
    int message_index = 0, in_use_index = 0, id_index = 0, num_send_bytes_index = 0, num_receive_bytes_index = 0;
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
    Q_UNUSED(line);
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
    return colors.back();
}


//rotate/flip a quadrant appropriately
static void hilbert_rot(int n, int *x, int *y, int rx, int ry) {
    if (ry == 0) {
        if (rx == 1) {
            *x = n-1 - *x;
            *y = n-1 - *y;
        }

        //Swap x and y
        int t  = *x;
        *x = *y;
        *y = t;
    }
}

//convert d to (x,y)
static void hilbert(int n, int d, int *x, int *y) {
    int rx, ry, s;
    *x = *y = 0;
    for (s=1; s<n; s*=2) {
        rx = 1 & (d/2);
        ry = 1 & (d ^ rx);
        hilbert_rot(s, x, y, rx, ry);
        *x += s * rx;
        *y += s * ry;
        d /= 4;
    }
}

void Builder::generate_color_map() {
    int n = 1<<7;
    for (int i = 0; i < n*n; i++) {
        int x, y;
        hilbert(n, i, &x, &y);
        color_map.push_back(QColor(x*2, 255-(i>>6), y*2));
    }
}
