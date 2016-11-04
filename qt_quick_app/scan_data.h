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
    explicit ScanData(int num_columns, int num_points, int ratio, int delta_x, int delta_y, QString unit, bool use_level, double scale_value);
    ~ScanData();
    bool append(coordinate x, coordinate y, point z);
    bool is_full();
    bool is_almost_full();
    qint64 size();
    void print();
    int max_size();
    std::vector<ScanLine*> raw_data;
    double **leveled_lines;
    QVector<ScanLine> leveled_data;
    QString generate_png();
    QString generate_leveled_png(int curret_line);
    QString generate_z_bar(double min_value, double max_value);
    QVariantList generate_all(int current_line);
    QVariantList get_latest_line();
    void save_png(QString path_and_name);

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
    double m_leveled_min;
    double m_leveled_max;
    double m_scale_value;
    bool m_same_range;
    bool m_use_level;
    qint64 m_current_size;
    QImage m_image;
    QImage m_leveled_image;
    QString m_unit;
};

#endif // SCANDATA_H
