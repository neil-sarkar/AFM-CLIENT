#include "scan_data.h"
#include "assert.h"
#include "adc.h"
#include "QDebug"
#include <QtGlobal>
#include "adc.h"
#include "globals.h"
#include "scan_line.h"
#include <QImage>
#include <QBuffer>
#include <QtMath>

ScanData::ScanData(int num_columns, int num_rows, int ratio, int delta_x, int delta_y)
{
    m_num_columns = num_columns;
    m_num_rows = num_rows;

    m_ratio = ratio;
    m_delta_x = delta_x;
    m_delta_y = delta_y;

    m_prev_max = -ADC::RESOLUTION * 2;
    m_prev_min = ADC::RESOLUTION * 2;


    for (int i = 0; i < m_num_rows; i++)
        raw_data.push_back(new ScanLine(m_num_columns));

    // Initialize the image to be all white
    m_image = QImage(m_num_columns, m_num_rows, QImage::Format_RGB32);
    for (int i = 0; i < m_num_columns; i++) {
        for (int j = 0; j < m_num_rows; j++) {
            m_image.setPixel(i, j, qRgb(255,255,255));
        }
    }
    m_current_size = 0;
}

int ScanData::max_size() {
    return m_num_rows * m_num_columns;
}

bool ScanData::is_full() {
    return (size() == max_size());
}

bool ScanData::is_almost_full() {
    // returns true if there's just one colunn left
    return (size() == max_size() - m_num_columns);
}

quint64 ScanData::size() { //
    return m_current_size;
}

bool ScanData::append(int x, int y, int z) {
    assert(!is_full());
//    qDebug() << x << y << z;
    raw_data[y]->add_point(x, z);
    if (raw_data[y]->is_full()) {
        raw_data[y]->compute_average();
    }
    m_current_size += 1;
    return true;
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

void ScanData::print() {
    for (int i = 0; i < 1; i++) {
        qDebug() << raw_data[i]->drawn << raw_data[i]->min << raw_data[i]->max;
        for (int j = 0; j < m_num_columns; j++)
            qDebug() << raw_data[i]->data[j];
    }
}

QColor get_color(double percent) {
    QVector<QColor> colors;
    colors.append(QColor(88,28,0));
    colors.append(QColor(188,128,0));
    colors.append(QColor(252,252,128));

    return interpolate_color(percent, colors);
}

QString ScanData::generate_png() {
     double percentage;
     QColor color;
     int num_points = size();

     // Step 1: Compute the max and the min of the leveled image
     double scan_max = -2 * ADC::RESOLUTION, scan_min = 2 * ADC::RESOLUTION;
     for (int i = 0; i < raw_data.size(); i++) {
         if (raw_data[i]->size > 0) {
            if (raw_data[i]->max - raw_data[i]->average > scan_max) {
                scan_max = raw_data[i]->max - raw_data[i]->average;
            }
            if (raw_data[i]->min - raw_data[i]->average < scan_min) {
                scan_min = raw_data[i]->min - raw_data[i]->average;
            }
        }
     }
     bool same_range = (m_prev_max == scan_max && m_prev_min == scan_min);

     for (int i = 0; i < m_num_rows; i++) {
         if (raw_data[i]->size == 0)
             continue;

         if (same_range && raw_data[i]->drawn)
             continue;

         for (int j = 0; j < raw_data[i]->size; j++) {
             double z_value = raw_data[i]->data[j] - raw_data[i]->average;
             if (scan_max == scan_min)
                 percentage = 0;
             else {
                 percentage = double(z_value - scan_min)  / (scan_max - scan_min) * 100;
                 percentage = floor(percentage * 100 + .5) / 100;
             }
             color = get_color(percentage);
             m_image.setPixel(j, i, qRgb(color.red(),color.green(),color.blue()));
         }

         raw_data[i]->drawn = true;
     }
     m_prev_min = scan_max;
     m_prev_max = scan_min;

     QByteArray ba;
     QBuffer buffer(&ba);
     buffer.open(QIODevice::WriteOnly);
     m_image.save(&buffer, "PNG"); // writes image into ba in PNG format
     return ba.toBase64();
}
