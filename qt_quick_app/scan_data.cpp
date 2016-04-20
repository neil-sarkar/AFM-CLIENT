#include "scan_data.h"
#include "assert.h"
#include "adc.h"
#include "QDebug"
#include <QtGlobal>
#include "adc.h"
#include "globals.h"
#include <QImage>
#include <QBuffer>
#include <QtMath>

ScanData::ScanData(int num_columns, int num_rows, int ratio, int delta_x, int delta_y, bool is_forward)
{
    m_num_columns = num_columns;
    m_num_rows = num_rows;
    m_ratio = ratio;
    m_delta_x = delta_x;
    m_delta_y = delta_y;
    
    m_x_index = -1;
    m_y_index = -1;
    m_is_forward = is_forward;
    m_max = 0;
    m_min = ADC::RESOLUTION;
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

bool ScanData::append(int z) {
    assert(!is_full());
    
    m_x_index = (m_x_index + 1) % m_num_columns;
    if (m_x_index == 0)
        m_y_index += 1;
    
    DataPoint point;
    
    point.x = m_is_forward ? m_x_index : m_num_columns - m_x_index - 1;
    point.y = m_y_index;
    point.z = z;
    
    data.append(point);

    if (z > m_max)
        m_max = z;
    if (z < m_min)
        m_min = z;

    return true;
}


void ScanData::print() {
    for (DataPoint data_point : data) {
        qDebug() << data_point.x << data_point.y << data_point.z;
    }
}


QColor interpolate_color(double percent, QVector<QColor> colors) {
    double bucket_size = 100.0 / (colors.length() - 1);
    for (int i = 1; i < colors.length(); i++) {
        if (percent > bucket_size * i)
            continue;
        double factor = (bucket_size * i - percent) / (bucket_size);
        int r1, g1, b1;
        r1 = colors[i].red();
        g1= colors[i].green();
        b1 = colors[i].blue();
        int r0, g0, b0;
        r0 = colors[i -1].red();
        g0= colors[i - 1].green();
        b0 = colors[i -1].blue();
        int mixed_r = r1 * (1-factor) + r0 * factor;
        int mixed_g = g1 * (1-factor) + g0 * factor;
        int mixed_b = b1 * (1-factor) + b0 * factor;
        return QColor(std::min(mixed_r, 255), std::min(mixed_g, 255), std::min(mixed_b, 255));
    }
}

QColor get_color(double percent) {
    QVector<QColor> colors;
    colors.append(QColor(88,28,0));
    colors.append(QColor(188,128,0));
    colors.append(QColor(252,252,128));

    return interpolate_color(percent, colors);
}

QString ScanData::generate_png() { // TODO: enum z value types
    QImage image(m_num_rows, m_num_columns, QImage::Format_RGB32);
    double percentage;
    QColor value;
    int num_points = size();
    DataPoint point;
    for (int i = 0; i < num_points; i++) {
        point = data[i];
        if (m_max == m_min)
            percentage = 0;
        else {
            percentage = double(point.z - m_min)  / (m_max - m_min) * 100;
            percentage = floor(percentage * 100 + .5) / 100;
        }
        value = get_color(percentage);
        image.setPixel(point.x, point.y, qRgb(value.red(),value.green(),value.blue()));
    }
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG"); // writes image into ba in PNG format
    return ba.toBase64();
}
