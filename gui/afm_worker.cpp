#include "afm_worker.h"
#include <QMessageBox>
#include <QTime>

/* Serial Configuration */
#define AFM_MANUFACTURER "FTDI" //Should change this later on to ICPI
#define AFM_MAX_DATA_SIZE 1     //Basically write 1 character at a time
#define AFM_POLL_TIMEOUT 50     //Poll the buffer every 1ms
#define AFM_LONG_TIMEOUT 5000   //Longer timeout for large data

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))

/*
 * Collect serial rx buffer from SerialObject, and put into the local QByteArray uart_resp.
 * Using uart_resp.isEmpty() as an indicator of when to read from serial rx buffer is bad,
 * because there might be partial data that reside within uart_resp when we last read serial rx.
 * It is much better to use an EOL or End of Message indicator, so that we know a message
 * inside uart_resp is incomplete. Now we go fetch it from the serial rx buffer, and so forth and
 * so on. This way we don't care if it was collected midway (Another option is to make r_afm
 * only return full messages, which would be the case if we use QIODevice readLine)
 */


/*
 * Replacing receive buffer with command buffer... using deque!
 *
 * mainThread and eventThread mydeque.push_back(), then serialThread would read and modify the front element.
 * If the message does not need a reply, serialThread would remove that element.
 * If a reply is expected, serialThread leaves it in mydeque.
 *      receive_worker will find it and destroy it as needed.
 *
 * Potential algorithm for QIODevice.readLine():
 *  Read a line, pass to uart_resp
 *      After we read a line, we would be sure that the next line is a full msg.
 *  uart_resp handlers do its thing. If it was not a full msg, we would discard it
 * >>> What if we miss a message? Does that ever happen?
 * >>> QT logic: look for matching Tag AND Cmd/Msg ID by look into the cmd deque
 *     Search through cmd deque with mydeque.at(i)
 *     If found a matching item, then mydeque.erase(mydeque.begin()+i); and proceed as usual
 *          (we missed those messages)
 *     If we did not find matching item, then increment error counter by 1. Load uart_resp with the next Line
 *          (unknown state. when err counter reaches some value, show error on UI and clear the deque with mydeque.clear())
 */

void afm_worker::init_serial_port(){
    serial = new QSerialPort(this);
    connect(this->serial, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

bool afm_worker::open_serial_port(QString serialPortName, qint32 baud_rate)
{
    serial->setBaudRate(baud_rate);
    serial->setPortName(serialPortName);
    serial_open = serial->open(QIODevice::ReadWrite);
    return serial_open;
}

void afm_worker::close_serial_port()
{
    // Prevent accidental segmentation -- use protection.
    if(serial_open) {
        serial->close();
        serial_open = false;
    }
    return;
}

bool afm_worker::serial_port_is_open(){
    return serial_open;
}

int afm_worker::writeByte(char byte)
{
    if (serial->write(&byte, 1) == 1) {
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
 * Send a message with msg_id using payload that is currently stored.
 */
void afm_worker::writeMsg(char message_id)
{
#if AFM_DEBUG
//    QString hex_equivalent_print = QString("%1").arg(message_id, 0, 16);
//    qDebug() << "afm_worker::writeMsg 0x" << hex_equivalent_print;
#endif
    writeMsg(message_id, payload_out_buffer);

    payload_out_buffer.clear();
}

/*
 * A wrapper function for sending serial message.
 * writeByte should not normally be used, since it does not escape special characters.
 *
 * Emits the push_recv_queue() signal once finished
 */
void afm_worker::writeMsg(char message_id, QByteArray payload)
{
    /* the outcome of sending. 0 if all successful, and negative number
     * indicates the number of bytes that failed to send.
     */
    int writeByte_result = 0;

    //Close the last message, in case the last message was bad
    writeByte_result += writeByte(SERIAL_MSG_NEWLINE);

    //Increment and Write the message tag
    message_tag++;
    if (message_tag >= 255) {
        message_tag = 1;
    } else if (message_tag == SERIAL_MSG_NEWLINE || message_tag == SERIAL_MSG_ESCAPE) {
        message_tag++; // Assumes the special characters are not consecutive...
    }
    writeByte_result += writeByte(message_tag);

    //Write the message ID
    writeByte_result += writeByte(message_id);

    //Write the message payload, and mask as nessessary
    for (auto payload_byte : payload) {
        // Special Bytes
        if (payload_byte == SERIAL_MSG_NEWLINE || payload_byte == SERIAL_MSG_ESCAPE) {
            writeByte_result += writeByte(SERIAL_MSG_ESCAPE);
            writeByte_result += writeByte(payload_byte | SERIAL_MSG_MASK);
        } else {
            writeByte_result += writeByte(payload_byte);
        }
    }

    //Close the message
    writeByte_result += writeByte(SERIAL_MSG_NEWLINE);

#if AFM_DEBUG
    qDebug() << "Sent TAG:" << QString().sprintf("%2p", message_tag) << " ID:" << message_id << QString().sprintf("%2p", message_id) << " payload 0x" << payload.toHex() << " success?" << writeByte_result;
#endif

    emit push_recv_queue(message_id, message_tag, writeByte_result);

    return;
}

void afm_worker::onReadyRead(){
    serial_incoming_buffer += serial->readAll();
    qDebug() << "afm_worker received readAll. serial_incoming_buffer = 0x" << serial_incoming_buffer.toHex();
    processIncomingBuffer();
}

void afm_worker::processIncomingBuffer(){
    while(serial_incoming_buffer.length() > 0) {
        getNextMsg(serial_incoming_buffer.at(0));
        serial_incoming_buffer.remove(0, 1);
    }
    return;
}


/*
 * Takes stuff from the incoming_bytes array and makes sense of them
 */
void afm_worker::getNextMsg(char incoming_byte){
    // char incoming_byte = 0x00;
    bool message_complete = false;

    //Read one byte at a time from the incoming buffer QByteaArray
    //Note that position is zero-based, and QByteArray.size() returns the size which starts from 1.
    //The serial_incoming_buffer should have enough bytes for a minimum message, including the escape byte
//        if (serial_incoming_buffer.length() > 0) {
//            incoming_byte = serial_incoming_buffer.at(0);
//            serial_incoming_buffer.remove(0, 1);
//        } else {
//            return -1;
//        }

    // Take care of the incoming byte...
    if (incoming_byte == SERIAL_MSG_NEWLINE) {
        // Newline char received. Is everything we got so far a valid message?
        if (incoming_message.size() >= 2) {
            // Check length... the message should be at least two bytes in size
            // Message size does not include the newline char
            message_complete = true;
        } else {
            // Otherwise, it was an empty or invalid message. Discard and move on.
            // Use message_position plus one to remove the newline char
            incoming_message.clear();
            return;
        }
    } else if (incoming_byte == SERIAL_MSG_ESCAPE && !escape_char_received) {
        // Is this escape char?
        escape_char_received = true;
    } else if (escape_char_received) {
        // Do we need to unmask this?
        incoming_message += incoming_byte & ~SERIAL_MSG_MASK;
        escape_char_received = false;
    } else {
        // None of the above. Collect it in incoming_message QByteArray
        incoming_message += incoming_byte;
    }

    if (incoming_message.length() > SERIAL_MSG_MAX_SIZE) {
        /*
         * A serial message should not be this long, like ever.
         * So we probably received a bunch of garbage data.
         * Clear incoming_message and move on.
         */
        incoming_message.clear();
        return;
    }

    if (message_complete) {
    #if AFM_DEBUG
        if (incoming_message.size() > 0) {
            //QString hex_equivalent_print = QString("%1").arg(raw_response.toHex(), 0, 16);
            qDebug() << "  0x" << incoming_message.toHex()
                     << " Size:" << incoming_message.size();
        }
    #endif

        if (incoming_message.size() > 0) {
            emit process_uart_resp(incoming_message);
            incoming_message.clear();
        }
        //Return how long the incoming_message was
        return;
    } else {
        return;
    }
}

afm_worker::~afm_worker()
{
    emit finished();
}
