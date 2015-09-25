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


#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))


class afm_worker: public QObject{
    Q_OBJECT

private:
    unsigned __int8 message_tag = 1;
    QByteArray payload_out_buffer, serial_incoming_buffer;
    QSerialPort *serial;
    bool serial_open = false;
    int writeMsg(char msg_id, QByteArray payload);

public:
    int writeByte(char byte);

public slots:
    // Started by main.cpp
    void init();
    // Used by send worker
    bool open(QString serialPortName, qint32 baud_rate);
    void close();
    // Not sure
    bool isOpen();

    /*
     * All the functions that will write to the MCU
     * They are all void because the receiver thread handles the return
     */
    // Used by afm.cpp
    void clearPayloadBuffer();
    int addPayloadByte(char byte);
  //  int writeByte(char byte);
    int writeMsg(char msg_id);

    // Used by receive worker
    QByteArray waitForMsg();
};

#endif // AFM_H

