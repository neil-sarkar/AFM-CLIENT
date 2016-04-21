#ifndef SCANDATA_H
#define SCANDATA_H

#include <QObject>
#include <QVector>
#include <QImage>
#include "data_point.h"
#include "scan_line.h"

class ScanData : public QObject
{
    Q_OBJECT
public:
    explicit ScanData(int num_columns, int num_points, int ratio, int delta_x, int delta_y);
    ~ScanData();
    bool append(int x, int y, int z);
    bool is_full();
    bool is_almost_full();
    quint64 size();
    void print();
    int max_size();
    std::vector<ScanLine*> raw_data;
    QVector<ScanLine> leveled_data;
    QString generate_png();

signals:

public slots:

private:
    int m_num_columns;
    int m_num_rows;
    int m_ratio;
    int m_delta_x;
    int m_delta_y;
    double m_prev_min;
    double m_prev_max;
    quint64 m_current_size;
    QImage m_image;
};

#endif // SCANDATA_H
