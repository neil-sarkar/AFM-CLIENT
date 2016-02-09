#include "scan_data.h"
#include "assert.h"
#include "QDebug"

ScanData::ScanData(int num_points, int num_lines, int ratio)
{
    m_num_points = num_points;
    m_num_lines = num_lines;
    m_ratio = ratio;
    m_x_index = -1;
    m_y_index = -1;
}

int ScanData::max_size() {
    return m_num_lines * m_num_points;
}

bool ScanData::is_full() {
    return (data.size() == max_size());
}

int ScanData::size() {
    return data.size();
}

bool ScanData::append(double z_amplitude, double z_offset, double z_phase) {
    assert(!is_full());
    m_x_index = (m_x_index + 1) % m_num_points;
    if (m_x_index == 0)
        m_y_index++;
    DataPoint point;
    point.x = m_x_index;
    point.y = m_y_index;
    point.z_offset = z_offset;
    point.z_amplitude = z_amplitude;
    point.z_phase = z_phase;
    data.append(point);
    return true;
}

void ScanData::print() {
    for (DataPoint data_point : data) {
        qDebug() << data_point.x << data_point.y << data_point.z_amplitude << data_point.z_offset << data_point.z_phase;
    }
}
