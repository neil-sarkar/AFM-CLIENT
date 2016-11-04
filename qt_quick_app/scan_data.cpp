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

ScanData::ScanData(int num_columns, int num_rows, int ratio, int delta_x, int delta_y, QString unit, bool use_level, double scale_value)
{
    m_unit = unit;
    m_num_columns = num_columns;
    m_num_rows = num_rows;

    m_ratio = ratio;
    m_delta_x = delta_x;
    m_delta_y = delta_y;

    m_scale_value = scale_value;
    m_same_range = false;
    m_use_level = use_level;

    // force image size of 1024x1024
    m_scale_x = display_image_dimensions/num_columns;
    m_scale_y = display_image_dimensions/num_rows;

    m_prev_max = INT32_MIN;
    m_prev_min = INT32_MAX;

    m_leveled_max = INT32_MIN;
    m_leveled_min = INT32_MAX;

    raw_data.reserve(m_num_rows + 1);
    for (int i = 0; i < m_num_rows; i++)
        raw_data[i] = new ScanLine(m_num_columns);

    leveled_lines = new double*[m_num_rows];
    for (int i = 0; i < m_num_rows; i++)
        leveled_lines[i] = new double[m_num_columns];

    // Initialize the image to be all white
    //m_image = QImage(m_num_columns*m_aspect_portrait, m_num_rows*m_aspect_landscape, QImage::Format_RGB32);
    m_image = QImage(display_image_dimensions, display_image_dimensions, QImage::Format_RGB32);
    m_image.fill(Qt::white);
    m_leveled_image = QImage(display_image_dimensions, display_image_dimensions, QImage::Format_RGB32);
    m_leveled_image.fill(Qt::white);
    m_current_size = 0;
}

ScanData::~ScanData() {
    for (unsigned int i = 0; i < raw_data.size(); i++) {
        delete raw_data[i];
    }
    for (int i = 0; i < m_num_rows; i++)
        delete[] leveled_lines[i];
    delete[] leveled_lines;
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
        if(m_use_level)
            raw_data[y]->compute_slope();
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

QVariantList ScanData::generate_all(int current_line) {
    qDebug() << "Processing Set[" << m_unit <<"] " << current_line;
    QVariantList results;
    results.append(current_line);
    results.append(generate_png());
    if(!m_same_range)
        results.append(generate_z_bar(m_prev_min, m_prev_max));
    else
        results.append("");
    if(m_use_level)
    {
        results.append(generate_leveled_png(current_line));
        results.append(generate_z_bar(m_leveled_min, m_leveled_max));
    }
    else
    {
        results.append("");
        results.append("");
    }
    return results;
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
     m_same_range = (m_prev_max == scan_max && m_prev_min == scan_min);

     double range = scan_max - scan_min;
     for (int i = 0; i < m_num_rows; i++) {
         if (raw_data[i]->size == 0) {
             continue;
         }

         if (m_same_range && raw_data[i]->drawn) {
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
            for (int row_rep = 0; row_rep < m_scale_y; row_rep++) {
               for (int col_rep = 0; col_rep < m_scale_x; col_rep++) {
                  m_image.setPixel(j*m_scale_x+col_rep, i*m_scale_y+row_rep, qRgb(color.red(),color.green(),color.blue()));
               }
            }
         }
         raw_data[i]->drawn = true;
     }

     m_prev_min = scan_min;
     m_prev_max = scan_max;
     QByteArray ba;
     QBuffer buffer(&ba);
     buffer.open(QIODevice::WriteOnly);
     m_image.save(&buffer, "PNG"); // writes image into ba in PNG format
     buffer.close();
     return ba.toBase64();
}

QString ScanData::generate_leveled_png(int current_line) {
    // Redraw entire image with every single line -- no point to naively assume slope wont change
    double slope_avg = 0.0;
    for (int y = 0; y <= current_line; y++)
    {
        slope_avg += raw_data[y]->slope;
    }
    slope_avg /= (current_line + 1);

    m_leveled_max = INT32_MIN;
    m_leveled_min = INT32_MAX;

    // find max and min + store leveled profile
    for (int y = 0; y <= current_line; y++)
    {
        double z_offset = raw_data[y]->average - slope_avg*double(raw_data[y]->size)/2;
        for (int x = 0; x < m_num_columns; x++)
        {
            double leveled_z = raw_data[y]->data[x] - z_offset - slope_avg*x;
            if (leveled_z > m_leveled_max)
                m_leveled_max = leveled_z;
            if (leveled_z < m_leveled_min)
                m_leveled_min = leveled_z;
            leveled_lines[y][x] = leveled_z;
        }
    }

    //draw the image
    double leveled_to_color_map = color_map.size()/(m_leveled_max-m_leveled_min);
    int color_index;
    QColor color;
    for (int y = 0; y <= current_line; y++) {
        for (int x = 0; x < m_num_columns; x++) {
           if (m_leveled_max == m_leveled_min)
               color_index = 0;
           else {
               color_index = (int)((leveled_lines[y][x] - m_leveled_min)*leveled_to_color_map);
           }
           if(color_index >= color_map.size()) color_index = color_map.size() - 1;
           if(color_index < 0) color_index = 0;
           color = color_map[color_index];
           for (int row_rep = 0; row_rep < m_scale_y; row_rep++) {
              for (int col_rep = 0; col_rep < m_scale_x; col_rep++) {
                 m_leveled_image.setPixel(x*m_scale_x+col_rep, y*m_scale_y+row_rep, qRgb(color.red(),color.green(),color.blue()));
              }
           }
        }
    }

    //write image to string
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    m_leveled_image.save(&buffer, "PNG"); // writes image into ba in PNG format
    buffer.close();
    return ba.toBase64();
}

QString ScanData::generate_z_bar(double min_value, double max_value) {
    QImage z_bar = color_bar.copy();
    QPainter painter(&z_bar);
    QString format = "%1 %2";
    double min_val;
    double max_val;
    if (m_use_level)
    {
        min_val = 0;
        max_val = max_value - min_value;
    }
    else
    {
        min_val = min_value;
        max_val = max_value;
    }
    painter.setFont(QFont("Roboto-Thin", 12));
    painter.drawText(27,4,99,34,Qt::AlignCenter, format.arg(QLocale::system().toString(m_scale_value*max_val,'g',3), m_unit));
    painter.drawText(27,986,99,34,Qt::AlignCenter, format.arg(QLocale::system().toString(m_scale_value*min_val,'g',3), m_unit));
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    z_bar.save(&buffer, "PNG"); // writes image into ba in PNG format
    buffer.close();
    return ba.toBase64();
}
