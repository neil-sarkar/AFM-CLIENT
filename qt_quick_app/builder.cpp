#include "builder.h"
#include "afm.h"
#include "dac.h"
#include "adc.h"
#include "pga.h"
#include "serial_port.h"
#include "send_worker.h"
#include "receive_worker.h"
#include "constants.h"
#include <iostream>
#include <iomanip>

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

    Motor* motor = new Motor();
    PID* pid = new PID();

    return new AFM(pga_collection, dac_collection, adc_collection, motor, pid);
}


void Builder::wire_hash_command_generated(QHash<int, AFMObject*> & collection, SendWorker* & send_worker) {
    QHash<int, AFMObject*>::iterator i;
    for (i = collection.begin(); i != collection.end(); ++i)
        QObject::connect(i.value(), SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
}

void Builder::wire(AFM* & afm, SerialPort* & serial_port, SendWorker* & send_worker, ReceiveWorker* & receive_worker) {
    // Wire command_generated signal
    // There is likely a cleaner way to connect all the command_generated SIGNALS to the enqueue_command SLOT as command_generated is inherited from AFMObject
    QObject::connect(afm->motor, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(afm->pid, SIGNAL(command_generated(CommandNode*)), send_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    wire_hash_command_generated(afm->ADC_collection, send_worker);
    wire_hash_command_generated(afm->DAC_collection, send_worker);
    wire_hash_command_generated(afm->PGA_collection, send_worker);

    // Async serial communication handling (when the MCU sends a message without us making an associated call for that message)
    QObject::connect(receive_worker, SIGNAL(mcu_reset_message_received()), afm, SLOT(init()));

    // Misc connections
    QObject::connect(serial_port, SIGNAL(message_sent(CommandNode*)), receive_worker, SLOT(enqueue_command(CommandNode*)), Qt::DirectConnection);
    QObject::connect(serial_port, SIGNAL(byte_received(char)), receive_worker, SLOT(enqueue_response_byte(char)), Qt::DirectConnection);
    QObject::connect(send_worker, SIGNAL(command_dequeued(CommandNode*)), serial_port, SLOT(execute_command(CommandNode*)));
    QObject::connect(serial_port, SIGNAL(connected()), afm, SLOT(init()));
}

void Builder::generate_command_nodes() {
    QString path = "/Users/abali/Google Drive/Code/icspi/AFM-CLIENT/qt_quick_app/command_spec.tsv"; // change to relative path
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
           node.id= bytes_to_int(line[id_index], line);
           node.num_send_bytes = bytes_to_int(line[num_send_bytes_index], line);
           node.num_receive_bytes = bytes_to_int(line[num_receive_bytes_index], line);
           command_hash[line[message_index]] = node;
       }
    }
    qDebug() << "Loaded " << command_hash.size() << "command node types.";
}

int Builder::bytes_to_int(QByteArray bytes, QList<QByteArray> line) {
    bytes.resize(2); // force it to be two bytes long (might not be necessary)
    bytes = bytes.simplified(); // remove any newlines or carriage returns [MIGHT CAUSE ISSUES]
    bool conversion_successful; // need this to call toInt() method below
    int result = bytes.toInt(&conversion_successful, 16);

    if (conversion_successful)
        return result;

    qDebug() << "Parsing failed" << line;
}
