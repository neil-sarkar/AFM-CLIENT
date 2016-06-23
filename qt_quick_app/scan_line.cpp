#include "scan_line.h"
#include "adc.h"
#include "assert.h"
#include "globals.h"
#include <QDebug>
#include <algorithm> // for std::nth_element

ScanLine::ScanLine(coordinate capacity_) {
    capacity = capacity_;
    size = 0;
    sum = 0;
    average = 0;
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
    if (size != 0)
        average = double(sum) / size;
    if (size != 0) {
        std::vector<point> data_vector(data, data + size);
        std::nth_element(data_vector.begin(), data_vector.begin() + size/2, data_vector.end());
        average = data_vector[size/2];
    }
}

ScanLine ScanLine::generate_leveled_line() {
    ScanLine leveled_line = ScanLine(this->capacity);
    qDebug() << size << capacity;
    for (int i = 0; i < this->size; i++) {
        leveled_line.add_point(i, this->data[i]);
    }
    return leveled_line;
}
