#ifndef AFM_DATA_H
#define AFM_DATA_H

#include <QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QVector>

/**
 * @brief   The afm_data class manages scan data returned by the
 *          AFM and generation of gwyddion files. Each afm_data
 *          object is essentially a scan.
 *
 */

/* Automatically Code Generation BEGIN
   [[[cog
   from CodeValet import CodeValet
   c = CodeValet()
   c.afm_data_h_define()
   ]]]*/
   /* Automatically Generated Code - Editing is futile! */
   #define RATIO_7_1  8
   #define RATIO_3_1  4
   #define RATIO_1_1  2
   #define RATIO_0_1  1
//[[[end]]]

class afm_data : public QObject {
Q_OBJECT

private:
int numpts, numlines, ratio;
double delta_x;
double delta_y;

/*
 * Note - the data doesn't have to be in grid form.
 * Gwyddion Simple XYZ format supports non-grid data.
 * This class can be easily modified to save non-grid data.
 */

// Master data vectors for this scan
QVector<double> x;
QVector<double> y;
QVector<double> zoffset;
QVector<double> zamp;
QVector<double> zphase;

public:
afm_data(int n_pts, int n_lines, int _ratio); //Constructor
int append_data(QVector<double> z_offset_adc,
                QVector<double> z_amp_adc,
                QVector<double> z_phase_adc);
void ratio_enum_to_deltaxy(int ratio_enum);
bool is_data_full();
void print_all();
int get_numpts();
int get_numlines();
int get_ratio();

};

#endif // AFM_DATA_H

