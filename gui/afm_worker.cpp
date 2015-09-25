#include "afm_worker.h"
#include <QMessageBox>
#include <QTime>

/* Serial Configuration */
#define AFM_MANUFACTURER "FTDI" //Should change this later on to ICPI
#define AFM_MAX_DATA_SIZE 1     //Basically write 1 character at a time
#define AFM_POLL_TIMEOUT 50     //Poll the buffer every 1ms
#define AFM_LONG_TIMEOUT 5000   //Longer timeout for large data

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))

void delay_1(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);

    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void afm_worker::init(){
    serial = new QSerialPort(this);
}

bool afm_worker::open(QString serialPortName, qint32 baud_rate)
{
    serial->setBaudRate(baud_rate);
    serial->setPortName(serialPortName);
    serial_open = serial->open(QIODevice::ReadWrite);
    return serial_open;
}

void afm_worker::close()
{
    // Prevent accidental segmentation -- use protection.
    if(serial_open) {
        serial->close();
        serial_open = false;
    }
    return;
}

bool afm_worker::isOpen(){
    return serial_open;
}

int afm_worker::writeByte(char byte)
{
    if (serial->write(&byte, AFM_MAX_DATA_SIZE) > -1) {
        return AFM_SUCCESS;
    } else {
#if AFM_DEBUG
        QString hex_equivalent_print = QString("%1").arg(byte, 0, 16);
        qDebug() << "afm_worker::writeByte failed to write 0x" << hex_equivalent_print;
#endif
        return AFM_FAIL;
    }
}

/*
 * Collects the bytes to send
 * After all the bytes are collected, call writeMsg() to actually send it out
 */
int afm_worker::addPayloadByte(char byte)
{
    payload_out_buffer += byte;
}

/*
 * Clear the payload out buffer before sending anything
 */
void afm_worker::clearPayloadBuffer()
{
    payload_out_buffer.clear();
}

/*
 * A wrapper function for sending serial message.
 * writeByte should not be used, since it does not escape special characters.
 */
int afm_worker::writeMsg(char msg_id, QByteArray payload)
{
    int writeByte_result; //local var for debugging only

    //Close the last message, in case the last message was bad
    writeByte_result = writeByte(SERIAL_MSG_NEWLINE);

    //Increment and Write the message tag
    message_tag++;

    if (message_tag >= 255)
        message_tag = 1;
    else if (message_tag == SERIAL_MSG_NEWLINE || message_tag == SERIAL_MSG_ESCAPE)
        message_tag++; // Assumes the special characters are not consecutive...

    writeByte_result = writeByte(message_tag);

    //Write the message ID
    writeByte_result = writeByte(msg_id);

    //Write the message payload, and mask as nessessary
    for (auto payload_byte : payload) {
        // Special Bytes
        if (payload_byte == SERIAL_MSG_NEWLINE || payload_byte == SERIAL_MSG_ESCAPE) {
            writeByte(SERIAL_MSG_ESCAPE);
            writeByte(payload_byte | SERIAL_MSG_MASK);
        } else {
            writeByte(payload_byte);
        }
    }

    //Close the message
    writeByte(SERIAL_MSG_NEWLINE);

#if AFM_DEBUG
    qDebug() << "Sent TAG " << QString().sprintf("%2p", message_tag) << " ID " << msg_id << " " << QString().sprintf("%2p", msg_id) << " payload 0x" << payload.toHex();
#endif

    return AFM_SUCCESS;
}

/*
 * Send a message with msg_id using payload that is currently stored.
 */
int afm_worker::writeMsg(char msg_id)
{
    int result = writeMsg(msg_id, payload_out_buffer);

    payload_out_buffer.clear();

    return result;
}



void afm_worker::getNextMsg(){
    forever {
        QByteArray incoming_message;
        char incoming_byte = 0x00;
        bool message_complete = false, escape_char_received = false;
        int msg_length = 0;
        int status = -1;

        while (!message_complete) {
            //Read one byte at a time
            // If the port is not open then we don't bother.
            if(serial_open) {
                if (serial->bytesAvailable() > 0) {
                    status = serial->read(&incoming_byte, 1);
                    qDebug() << " SR" << status;
                    // QByteArray test_message = readAll();
                    qDebug() << "RECV  0x" << incoming_byte;
                } else {
                    delay_1(10);
                }
            }
            // Take care of the incoming byte...

            if (incoming_byte == SERIAL_MSG_NEWLINE) {
                // Newline char received. Is everything we got so far a valid message?
                if (incoming_message.size() >= 2) {
                    // Check length... should be at least two bytes
                    message_complete = true;
                    break;
                } else {
                    // Otherwise, it was an empty or invalid message. Discard and move on.
                    incoming_message.clear();
                }
            } else if (incoming_byte == SERIAL_MSG_ESCAPE && !escape_char_received) {
                // Is this escape char?
                escape_char_received = true;
            } else if (escape_char_received) {
                // Do we need to unmask this?
                incoming_message += incoming_byte & ~SERIAL_MSG_MASK;
                escape_char_received = false;
            } else {
                // None of the above. Collect it in message QByteArray
                incoming_message += incoming_byte;
            }
        }

    #if AFM_DEBUG
        if (incoming_message.size() > 0) {
            //QString hex_equivalent_print = QString("%1").arg(raw_response.toHex(), 0, 16);
            qDebug() << "  0x" << incoming_message.toHex()
                     << " Size:" << incoming_message.size();
        }
    #endif
    }
}

/*
 * Waits until there is a complete message received, then returns that message.
 *
 * It should only return one message at a time. Masking will be removed.
 */
void afm_worker::getNextMsg1()
{
    // If the port is not open then we don't bother.
    if(!serial_open) {
        return;
    }

    QByteArray incoming_message;
    char incoming_byte = 0x00;
    bool message_complete = false, escape_char_received = false;
    int msg_length = 0;

    while (!message_complete) {
        //Read one byte at a time
        if (serial->bytesAvailable() > 0)
            int status = serial->read(&incoming_byte, 1);
        //qDebug() << " SR" << status;
// QByteArray test_message = readAll();
        // qDebug() << "  0x" << test_message.toHex();

        //  if(incoming_byte != '\0' && status > 0){

        if (!serial_incoming_buffer.isEmpty()) {
            incoming_byte = serial_incoming_buffer.at(msg_length);
            msg_length++;
            printf(" 0x%02x", incoming_byte);
        } else {
            // The incoming buffer is empty but the last message was not a complete one
            // Do nothing and return
            return;
        }

        // Take care of the incoming byte...

        if (incoming_byte == SERIAL_MSG_NEWLINE) {
            // Newline char received. Is everything we got so far a valid message?
            if (incoming_message.size() >= 2) {
                // Check length... should be at least two bytes
                message_complete = true;
                break;
            } else {
                // Otherwise, it was an empty or invalid message. Discard and move on.
                incoming_message.clear();
            }
        } else if (incoming_byte == SERIAL_MSG_ESCAPE && !escape_char_received) {
            // Is this escape char?
            escape_char_received = true;
        } else if (escape_char_received) {
            // Do we need to unmask this?
            incoming_message += incoming_byte & ~SERIAL_MSG_MASK;
            escape_char_received = false;
        } else {
            // None of the above. Collect it in message QByteArray
            incoming_message += incoming_byte;
        }
    }

    serial_incoming_buffer.remove(0, msg_length);

#if AFM_DEBUG
    if (incoming_message.size() > 0) {
        //QString hex_equivalent_print = QString("%1").arg(raw_response.toHex(), 0, 16);
        qDebug() << "  0x" << incoming_message.toHex()
                 << " Size:" << incoming_message.size();
    }
#endif

    update_uart_resp(incoming_message);
    return;
}


