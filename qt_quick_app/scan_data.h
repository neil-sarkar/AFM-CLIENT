#ifndef SCANDATA_H
#define SCANDATA_H

#include <QObject>
#include <QVector>
#include "data_point.h"

class ScanData : public QObject
{
    Q_OBJECT
public:
    explicit ScanData(int num_points, int num_lines, int ratio);
    bool append(double z_offset, double z_amplitude, double z_phase);
    bool is_full();
    int size();
    void print();
    int max_size();

signals:

public slots:

private:
    int m_num_points;
    int m_num_lines;
    int m_ratio;
    int m_x_index;
    int m_y_index;
    double m_delta_x;
    double m_delta_y;
    QVector<DataPoint> data;
};


#endif // SCANDATA_H
