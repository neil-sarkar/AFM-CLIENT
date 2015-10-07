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

/*AFM Configuration*/
#define AFM_DEBUG                            1  // 1: display debug messages
//#define AFM_USE_DUNCAN_BOARD                 0  // 1: Duncan's Board, 0: Mahdi's Board
#define AFM_MICRO_CONNECTED                  1  // 1: microcontroller, 0: uC not plugged in
#define AFM_SUCCESS 0
#define AFM_FAIL -1

/*
 *  Serial Communication Specifics
 */

//Maximum size allowed for a message before it is discarded. For protection against bad serial connection.
#define SERIAL_MSG_MAX_SIZE 50000
#define SERIAL_MSG_NEWLINE 0x0A
#define SERIAL_MSG_ESCAPE 0x10
#define SERIAL_MSG_MASK 0x80
#define AFM_WORKER_SERIAL_MSG_INCOMPLETE -1
#define AFM_WORKER_SERIAL_MSG_TOO_LONG -2

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))


class afm_worker: public QObject{
    Q_OBJECT

private:
    unsigned __int8 message_tag = 1;
    QByteArray payload_out_buffer, serial_incoming_buffer;
    QByteArray incoming_message;
    QSerialPort *serial;
    bool escape_char_received = false;
    bool serial_open = false;
    void writeMsg(char message_id, QByteArray payload);
    void getNextMsg(char incoming_byte);
    void processIncomingBuffer();

public:
    int writeByte(char byte);
     ~afm_worker();

signals:
    void process_uart_resp(QByteArray new_uart_resp);
    void push_recv_queue(char message_id, char message_tag, int writeByte_result);
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
    int addPayloadByte(char byte);
    void writeMsg(char msg_id);

    // Used by receive worker
    void onReadyRead();
};

#endif // AFM_H

