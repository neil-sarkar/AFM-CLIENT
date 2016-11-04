#include "scan_line.h"
#include "adc.h"
#include "assert.h"
#include "globals.h"
#include <QDebug>

ScanLine::ScanLine(coordinate capacity_) {
    capacity = capacity_;
    size = 0;
    sum = 0;
    average = 0;
    this->slope = 0;
    this->max = INT32_MIN;
    this->min = INT32_MAX;

    data = new point[capacity];

    for (int i = 0; i < capacity; i++) {
        data[i] = 0;
    }

    drawn = false;
}

ScanLine::~ScanLine() {
    delete[] this->data;
}

bool ScanLine::is_full() {
    return size == capacity;
}

void ScanLine::add_point(coordinate x, point z) {
    data[x] = z;
    size += 1;
    sum += z;
    if (z > this->max)
        this->max = z;
    if (z < this->min)
        this->min = z;
}

void ScanLine::compute_average() {
    if (this->size != 0)
        this->average = double(this->sum) / this->size;
}

double ScanLine::compute_slope() {
    if (this->size != 0)
    {
        double numerator = 0.0;
        double denominator = 0.0;
        double x_average = double(this->size - 1)/2;
        double x_zero_mean;
        for(int i=0; i<this->size;i++)
        {
            x_zero_mean = i - x_average;
            numerator += x_zero_mean*(data[i]-this->average);
            denominator += x_zero_mean*x_zero_mean;
        }
        this->slope = numerator/denominator;
    }
    return this->slope;
}

ScanLine ScanLine::generate_leveled_line() {
    ScanLine leveled_line = ScanLine(this->capacity);
    qDebug() << size << capacity;
    for (int i = 0; i < this->size; i++) {
        leveled_line.add_point(i, this->data[i]);
    }
    return leveled_line;
}
