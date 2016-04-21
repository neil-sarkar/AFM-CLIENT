#include "scan_line.h"
#include "adc.h"
#include "assert.h"
#include <QDebug>

ScanLine::ScanLine(int capacity_) {
    capacity = capacity_;
    size = 0;
    sum = 0;
    average = 0;
    max = -ADC::RESOLUTION * 2;
    min = ADC::RESOLUTION * 2;
    data = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = 0;
    }
    drawn = false;
}

bool ScanLine::is_full() {
    return size == capacity;
}

void ScanLine::add_point(int x, int z) {

    data[x] = z;
    size += 1;
    sum += z;
    if (z > this->max)
        this->max = z;
    if (z < this->min)
        this->min = z;
    assert(z <= max && z >= min);
}

void ScanLine::compute_average() {
    if (this->size != 0)
        this->average = double(this->sum) / this->size;
}

ScanLine ScanLine::generate_leveled_line() {
    ScanLine leveled_line = ScanLine(this->capacity);
    qDebug() << size << capacity;
    for (int i = 0; i < this->size; i++) {
        leveled_line.add_point(i, this->data[i]);
    }
    return leveled_line;
}
