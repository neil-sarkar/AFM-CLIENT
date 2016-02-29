#ifndef SCANDATA_H
#define SCANDATA_H

#include <QObject>
#include <QVector>
#include "data_point.h"

class ScanData : public QObject
{
    Q_OBJECT
public:
    explicit ScanData(int num_points, int num_lines, int ratio, int delta_x, int delta_y, bool is_forward);
    bool append(double z_offset, double z_amplitude, double z_phase);
    bool is_full();
    int size();
    void print();
    int max_size();
    QVariantList package_data_for_ui(int num_points, bool is_offset);
    QVariantList package_error_signal_for_ui(int num_points, int setpoint); // setpoint is int here because we convert it to bits
    QList<DataPoint> data;

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
    bool m_is_forward;
};


#endif // SCANDATA_H
