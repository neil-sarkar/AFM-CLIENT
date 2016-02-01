#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H
#include <QObject>
#include <QSerialPort>
#include <QList>
#include <QTimer>
#include "command_node.h"
#include "thread_safe_queue.h"

class SerialPort: public QObject
{
Q_OBJECT
    public:
        explicit SerialPort(QObject *parent = 0); // constructor
        ~SerialPort(); // destructor
        bool auto_connect();
        bool open(QString port_name, qint32 baud_rate); // opens the given serial port at the given baud rate, and handles any setup processes
        Q_INVOKABLE void close(); // closes the serial port, and handles any tear-down processes

    signals:
        void connected(); // emitted when afm is first connected to
        void disconnected(); // emitted when afm is first disconnected
        void message_sent(CommandNode*); // emitted after a full command has been sent
        void byte_received(char);

    public slots:
        void on_ready_read();
        void scan_for_ports();
        void check_connected(); // this method runs periodically as dictated by the port_scan_timer
        int write_byte(char byte);
        void execute_command(CommandNode*);

    private:
        ThreadSafeQueue<char> bytes_received_queue;
        QTimer* port_scan_timer;
        bool is_connected;
        QSerialPort* port;

};
#endif // SERIAL_PORT_H