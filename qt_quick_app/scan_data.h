#ifndef SCANDATA_H
#define SCANDATA_H

#include <QObject>
#include <QVector>
#include <QImage>
#include "data_point.h"

class ScanData : public QObject
{
    Q_OBJECT
public:
    explicit ScanData(int num_points, int num_lines, int ratio, int delta_x, int delta_y, bool is_forward);
    bool append(int z);
    bool is_full();
    int size();
    void print();
    int max_size();
    QList<DataPoint> data;
    QString generate_png();

signals:

public slots:

private:
    int m_num_columns;
    int m_num_rows;
    int m_ratio;
    int m_x_index;
    int m_y_index;
    int m_delta_x;
    int m_delta_y;
    int m_max;
    int m_min;
    int m_prev_min;
    int m_prev_max;
    bool m_is_forward;
    QImage m_image;
};

#endif // SCANDATA_H
