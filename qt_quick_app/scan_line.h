#ifndef SCANLINE_H
#define SCANLINE_H

#include "data_point.h"
#include "data_point.h"
#include "globals.h"
#include <QtGlobal>

class ScanLine
{
public:
    ScanLine(coordinate capacity_);
    ~ScanLine();
    bool is_full();
    void add_point(coordinate x, point z);
    void compute_average();
    ScanLine generate_leveled_line();
    quint16 size;

    point* data; // can be positive or negative because this is a subtraction from the error signal
    qint64 sum;
    coordinate capacity;
    double average;
    bool drawn;
    double_point max; // plus/minus 2*4095
    double_point min;

};

#endif // SCANLINE_H
