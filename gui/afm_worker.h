#ifndef AFM_WORKER_H
#define AFM_H
#define AFM_BAUD_RATE 76800

#include <QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QSerialPort> //For QT5
#include <QSerialPortInfo>
#include <QString>
//#include <QVector>
#include <math.h>
#include <QTime>

/*AFM Configuration*/
#define AFM_DEBUG                            1  // 1: display debug messages
#define AFM_MICRO_CONNECTED                  1  // 1: microcontroller, 0: uC not plugged in
#define AFM_SUCCESS 0
#define AFM_FAIL -1

/*
 *  Serial Communication Specifics
 */

//Maximum size allowed for a message before it is discarded. For protection against bad serial connection.
#define SERIAL_MSG_MAX_SIZE 50000
#define AFM_WORKER_SERIAL_MSG_INCOMPLETE -1
#define AFM_WORKER_SERIAL_MSG_TOO_LONG -2

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))

/**
 * @brief The afm_worker class owns the serial object. It implements the serial protocol, including
 *          masking/unmasking/Message Tag Assignment for both sending and receiving.
 *          Call into relevant slots to send a message. It will emit signals when messages are received as well.
 */

class afm_worker: public QObject{
    Q_OBJECT

private:
    unsigned __int8 message_tag = 1;
    QByteArray payload_out_buffer, serial_incoming_buffer;
    QByteArray incoming_message;
    QSerialPort *serial;
    bool escape_char_received = false;
    bool serial_open = false;
    void writeMsg(unsigned char message_id, QByteArray payload);
    void getNextMsg(char incoming_byte);
    void processIncomingBuffer();

public:
    int writeByte(char byte);
     ~afm_worker();

signals:
    void process_uart_resp(QByteArray new_uart_resp);
    void push_recv_queue(unsigned char message_id, unsigned char message_tag, int writeByte_result);
    void finished();

public slots:
    // Started by main.cpp
    void init_serial_port();
    // Used by send worker
    bool open_serial_port(QString serialPortName, qint32 baud_rate);
    void close_serial_port();
    // Not sure
    bool serial_port_is_open();

    /*
     * All the functions that will write to the MCU
     * They are all void because the receiver thread handles the return
     */
    // Used by afm.cpp
    void clearPayloadBuffer();
    void addPayloadByte(char byte);
    void writeMsg(unsigned char msg_id);

    // Used by receive worker
    void onReadyRead();
};

#endif // AFM_H
