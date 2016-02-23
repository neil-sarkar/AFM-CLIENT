#include "scan_data.h"
#include "assert.h"
#include "QDebug"

ScanData::ScanData(int num_points, int num_lines, int ratio)
{
    m_num_columns = num_points;
    m_num_rows = num_lines;
    m_ratio = ratio;
    m_x_index = -1;
    m_y_index = -1;
}

int ScanData::max_size() {
    return m_num_rows * m_num_columns;
}

bool ScanData::is_full() {
    return (data.size() == max_size());
}

int ScanData::size() {
    return data.size();
}

bool ScanData::append(double z_amplitude, double z_offset, double z_phase) {
    assert(!is_full());
    m_x_index = (m_x_index + 1) % m_num_columns;
    if (m_x_index == 0)
        m_y_index++;
    DataPoint point;
    point.x = m_x_index;
    point.y = m_y_index;
    point.z_offset = z_offset;
    point.z_amplitude = z_amplitude;
    point.z_phase = z_phase;
    data.append(point);
    qDebug() << point.x << point.y;
    return true;
}

QVariantList ScanData::package_data_for_ui(int num_points) {
    // data comes back as a series of x y z, and then tacks on the average z
    QVariantList latest_data;
    double sum = 0;
    num_points = std::min(num_points, size());
    for (int i = 0 ; i < num_points; i++) {
        DataPoint point = data[size() - i - 1];
        latest_data.append(point.x);
        latest_data.append(point.y);
        latest_data.append(point.z_offset);
        sum += point.z_offset;
    }
    double average = sum / num_points;
    for (int i = 2; i < num_points * 3; i += 3) {
        latest_data[i] = (latest_data[i]).toDouble() - average;
    }
    return latest_data;
}

void ScanData::print() {
    for (DataPoint data_point : data) {
        qDebug() << data_point.x << data_point.y << data_point.z_amplitude << data_point.z_offset << data_point.z_phase;
    }
}
