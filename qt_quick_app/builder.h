#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H
#include "afm.h"
#include "serial_port.h"
#include "send_worker.h"
#include "receive_worker.h"


class Builder
{
public:
    Builder();
    AFM* build_afm();
    void wire(AFM* & afm, SerialPort* & serial_port, SendWorker* & send_worker, ReceiveWorker* & receive_worker);
    void wire_hash_command_generated(QHash<int, AFMObject*> & collection, SendWorker* & send_worker);
};

#endif // APPLICATIONBUILDER_H
