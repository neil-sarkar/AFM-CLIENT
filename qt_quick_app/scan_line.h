#ifndef SCANLINE_H
#define SCANLINE_H

#include "data_point.h"
#include "data_point.h"

class ScanLine
{
public:
    ScanLine(int capacity_);
    bool is_full();
    void add_point(int x, int z);
    void compute_average();
    ScanLine generate_leveled_line();
    int size;

    int* data;
    int sum;
    int capacity;
    double average;
    bool drawn;
    int max;
    int min;

};

#endif // SCANLINE_H
