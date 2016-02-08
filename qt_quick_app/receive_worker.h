#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include <QObject>
#include "command_node.h"
#include "thread_safe_queue.h"

class ReceiveWorker : public QObject
{
    Q_OBJECT
public:
    explicit ReceiveWorker(QObject *parent = 0);
    static const unsigned char MCU_Reset_Message[5];
    static const int MCU_Reset_Message_Length = 5;

signals:
    void command_received();
    void response_byte_received();
    void mcu_reset_message_received();
    void auto_approach_info_received(QByteArray);

public slots:
    void enqueue_command(CommandNode*);
    void enqueue_response_byte(char);

private slots:
    void build_working_response();

private:
    ThreadSafeQueue<CommandNode*> command_queue;
    ThreadSafeQueue<char> response_byte_queue;
    QByteArray working_response;
    bool complete_message;
    void process_working_response();
    void handle_asynchronous_message();
    bool is_mcu_reset_message(); // must be a better way to check equality of two qbyteararys
    bool is_auto_approach_info();
    bool is_auto_approach_stopped_message();
    void handle_auto_approach_stopped_message();
    void assert_return_integrity(CommandNode* node, unsigned char tag, unsigned char id, int length);
    int num_commands_received;
    bool escape;


};

#endif // RECEIVEWORKER_H
