#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H
#include "afm.h"
#include "serial_port.h"
#include "send_worker.h"
#include "receive_worker.h"
#include <QRgb>


class Builder
{
public:
    Builder();
    AFM* build_afm();
    void wire(AFM* & afm, SerialPort* & serial_port, SendWorker* & send_worker, ReceiveWorker* & receive_worker);
    void wire_hash_command_generated(QHash<int, AFMObject*> & collection, SendWorker* & send_worker);
    void generate_command_nodes();  // pull all the command nodes from .tsv file
    int bytes_to_int(QByteArray bytes, QList<QByteArray> line, int base);
    void generate_color_map();
    QColor interpolate_color(double percent, QVector<QColor> colors);

};

#endif // APPLICATIONBUILDER_H
