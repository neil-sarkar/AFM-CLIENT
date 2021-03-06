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
    static const unsigned char MCU_heartbeat_message[5];
    ThreadSafeQueue<CommandNode*> receive_command_queue;

signals:
    void command_received();
    void response_byte_received();
    void mcu_reset_message_received();
    void receive_returned();
    void auto_approach_info_received(QByteArray);
    void resend_command(CommandNode*);

public slots:
    void enqueue_command(CommandNode*);
    void enqueue_response_byte(char);

private slots:
    void build_working_response();
    void flush();

private:
    ThreadSafeQueue<char> response_byte_queue;
    QByteArray working_response;
    bool complete_message;
    void process_working_response();
    bool is_mcu_heartbeat_message();
    bool is_auto_approach_info();
    bool is_auto_approach_stopped_message();
    bool is_response_valid(CommandNode* node, unsigned char tag, unsigned char id, int length);
    void handle_auto_approach_stopped_message();
    void handle_hardware_reset();
    void handle_asynchronous_message();
    void handle_invalid_response(CommandNode *node);
    bool escape;


};

#endif // RECEIVEWORKER_H
