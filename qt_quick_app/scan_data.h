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
    explicit ScanData(int num_columns, int num_points, int ratio, int delta_x, int delta_y);
    bool append(int x, int y, int z);
    bool is_full();
    bool is_almost_full();
    quint64 size();
    void print();
    int max_size();
    DataPoint** data;
    QString generate_png();

signals:

public slots:

private:
    int m_num_columns;
    int m_num_rows;
    int m_ratio;
    int m_delta_x;
    int m_delta_y;
    int m_max;
    int m_min;
    int m_prev_min;
    int m_prev_max;
    quint64 m_current_size;
    QImage m_image;
};

#endif // SCANDATA_H
