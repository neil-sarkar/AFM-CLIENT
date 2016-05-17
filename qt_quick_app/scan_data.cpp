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
#include <QPainter>

ScanData::ScanData(int num_columns, int num_rows, int ratio, int delta_x, int delta_y)
{
    m_num_columns = num_columns;
    m_num_rows = num_rows;

    m_ratio = ratio;
    m_delta_x = delta_x;
    m_delta_y = delta_y;

    m_prev_max = INT32_MIN;
    m_prev_min = INT32_MAX;

    raw_data.reserve(m_num_rows + 1);
    for (int i = 0; i < m_num_rows; i++)
        raw_data[i] = new ScanLine(m_num_columns);

    // Initialize the image to be all white
    m_image = QImage(m_num_columns, m_num_rows, QImage::Format_RGB32);
    m_image.fill(Qt::white);
    QPainter p;
    p.begin(&m_image);
    p.drawText(0,0,"hello");
    // for (int i = 0; i < m_num_columns; i++) {
    //     for (int j = 0; j < m_num_rows; j++) {
    //         m_image.setPixel(i, j, qRgb(255,255,255));
    //     }
    // }
    m_current_size = 0;
}

ScanData::~ScanData() {
    for (unsigned int i = 0; i < raw_data.size(); i++) {
        delete raw_data[i];
    }
}

QVariantList ScanData::get_latest_line() {
    mutex.lock();
    QVariantList data;
    for (int i = m_num_rows - 1; i >= 0; i--) {
        if (raw_data[i]->drawn) {
            for (int j = 0; j < m_num_columns; j++) {
                data.append(j);
                data.append(i);
                data.append(raw_data[i]->data[j]);
            }
            mutex.unlock();
            return data;
        }
    }
   mutex.unlock();
   return data;
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

qint64 ScanData::size() { //
    return m_current_size;
}

bool ScanData::append(coordinate x, coordinate y, point z) {
    assert(!is_full());

    raw_data[y]->add_point(x, z);
    if (raw_data[y]->is_full()) {
        raw_data[y]->compute_average();
    }
    m_current_size += 1;
    return true;
}

void ScanData::print() {
    for (int i = 0; i < 1; i++) {
//        qDebug() << raw_data[i]->drawn << raw_data[i]->min << raw_data[i]->max;
        for (int j = 0; j < m_num_columns; j++)
            qDebug() << raw_data[i]->data[j];
    }
}

QString ScanData::generate_png() {
     int color_index;
     QColor color;

     // Step 1: Compute the max and the min of the leveled image
     double scan_max = INT32_MIN, scan_min = INT32_MAX;

     // Find the max and min of the lines we've yet draw -- assumes that we add lines to the raw_data sequentially (index 0 to n, not the other way)
     for (int i = 0; i < m_num_rows; i++) {
        if (raw_data[i]->size == 0)
            break;
        if (raw_data[i]->drawn)
            continue;
        if (raw_data[i]->max - raw_data[i]->average > scan_max) {
            scan_max = raw_data[i]->max - raw_data[i]->average;
        }
        if (raw_data[i]->min - raw_data[i]->average < scan_min) {
            scan_min = raw_data[i]->min - raw_data[i]->average;
        }
    }

     // Find the extreme max and min for the entire scan
     if (scan_max < m_prev_max) {
         scan_max = m_prev_max;
     }
     if (scan_min > m_prev_min) {
         scan_min = m_prev_min;
     }
     bool same_range = (m_prev_max == scan_max && m_prev_min == scan_min);

     double range = scan_max - scan_min;
     for (int i = 0; i < m_num_rows; i++) {
         if (raw_data[i]->size == 0) {
             continue;
         }

         if (same_range && raw_data[i]->drawn) {
             continue;
         }

         for (int j = 0; j < raw_data[i]->size; j++) {
             double z_value = raw_data[i]->data[j] - raw_data[i]->average;
             if (scan_max == scan_min)
                 color_index = 0;
             else {
                 color_index = (int)((z_value - scan_min)*color_map.size() / range);
             }
             if(color_index >= color_map.size()) color_index = color_map.size() - 1;
             if(color_index < 0) color_index = 0;
             color = color_map[color_index];
             m_image.setPixel(j, i, qRgb(color.red(),color.green(),color.blue()));
         }
         raw_data[i]->drawn = true;
     }

     m_prev_min = scan_min;
     m_prev_max = scan_max;
     QByteArray ba;
     QBuffer buffer(&ba);
     buffer.open(QIODevice::WriteOnly);
     m_image.save(&buffer, "PNG"); // writes image into ba in PNG format
     return ba.toBase64();
}
