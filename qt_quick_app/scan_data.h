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
    explicit ScanData(int num_columns, int num_points, int ratio, int delta_x, int delta_y, QString unit);
    ~ScanData();
    bool append(coordinate x, coordinate y, point z);
    bool is_full();
    bool is_almost_full();
    qint64 size();
    void print();
    int max_size();
    std::vector<ScanLine*> raw_data;
    
    QVector<ScanLine> leveled_data;
    QString generate_png();
    QString generate_z_bar();
    QVariantList generate_all();
    QVariantList get_latest_line();

signals:

public slots:

private:
    int m_num_columns;
    int m_num_rows;
    int m_ratio;
    int m_delta_x;
    int m_delta_y;
    int m_scale_x;
    int m_scale_y;
    double m_prev_min;
    double m_prev_max;
    bool m_same_range;
    qint64 m_current_size;
    QImage m_image;
    QString m_unit;
};

#endif // SCANDATA_H
