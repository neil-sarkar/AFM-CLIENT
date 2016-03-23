#include "scan_data.h"
#include "assert.h"
#include "adc.h"
#include "QDebug"
#include <QtGlobal>

ScanData::ScanData(int num_points, int num_lines, int ratio, int delta_x, int delta_y, bool is_forward)
{
    m_num_columns = num_points;
    m_num_rows = num_lines;
    m_ratio = ratio;
    m_delta_x = delta_x;
    m_delta_y = delta_y;
    m_x_index = -1;
    m_y_index = -1;
    m_is_forward = is_forward;
}

int ScanData::max_size() {
    return m_num_rows * m_num_columns;
}

bool ScanData::is_full() {
    return (data.size() == max_size());
}

int ScanData::size() { //
    return data.size();
}

bool ScanData::append(int z_amplitude, int z_offset, int z_phase, int setpoint) {
    assert(!is_full());
    m_x_index = (m_x_index + 1) % m_num_columns;
    if (m_x_index == 0)
        m_y_index += 1;
    DataPoint point;
    point.x = m_is_forward ? m_x_index : m_num_columns - m_x_index - 1;
    point.y = m_y_index;
    point.z_offset = z_offset;
    point.z_phase = z_phase;
    point.z_error = setpoint - z_amplitude;
    data.append(point);
//    qDebug() << point.x << point.y;
    return true;
}

QVariantList ScanData::package_data_for_ui(int num_points, int z_type) {
    // data comes back as a series of x y z, and then tacks on the average z
    QVariantList latest_data;
    double sum = 0;
    num_points = std::min(num_points, size());
    for (int i = 0 ; i < num_points; i++) {
        DataPoint point = data[size() - i - 1];
        latest_data.append(point.x);
        latest_data.append(point.y);
        switch (z_type) {
            case 0:
                latest_data.append(point.z_offset);
                sum += point.z_offset;
                break;
            case 1:
                latest_data.append(point.z_phase);
                sum += point.z_phase;
                break;
            case 2:
                latest_data.append(point.z_error);
                sum += point.z_error;
                break;
        }
    }
    double average = sum / num_points;
    QVariant max = -1 * 10000000;
    QVariant min = 10000000;
    for (int i = 2; i < num_points * 3; i += 3) {
        latest_data[i] = (latest_data[i]).toDouble() - average;
        if (latest_data[i] > max)
            max = latest_data[i];
        if (latest_data[i] < min)
            min = latest_data[i];
    }

    // if (m_is_forward)
    latest_data.append(max);
    latest_data.append(min);
    return latest_data;
    
    // QVariantList latest_data_reversed; // could do this reversing in place with the averaging operation
    // for (int i = num_points * 3; i > 0; i -= 3) {
    //     latest_data_reversed.append(latest_data[i - 3]);
    //     latest_data_reversed.append(latest_data[i - 2]);
    //     latest_data_reversed.append(latest_data[i - 1]);
    // }
    // return latest_data_reversed;
}

void ScanData::print() {
    for (DataPoint data_point : data) {
        qDebug() << data_point.x << data_point.y << data_point.z_error << data_point.z_offset << data_point.z_phase;
    }
}
