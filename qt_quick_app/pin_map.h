#ifndef PIN_MAP_H
#define PIN_MAP_H

#include <QString>
#include <QList>
#define NEW_MCU
//#define OLD_MCU

struct Peripheral {
    QString name;
    int id;
    double default_value;

    Peripheral(QString name_, int id_, double default_value_ = 0) {
        name = name_;
        id = id_;
        default_value = default_value_;
    }
};

struct PinMap {
    #ifdef NEW_MCU
        PinMap() {
            dac_array.push_back(Peripheral(QString("z_offset_fine"), 6));
            dac_array.push_back(Peripheral(QString("y_1"), 2));
            dac_array.push_back(Peripheral(QString("z_offset_coarse"), 9));
            dac_array.push_back(Peripheral(QString("y_2"), 5));
            dac_array.push_back(Peripheral(QString("x_1"), 4));
            dac_array.push_back(Peripheral(QString("x_2"), 3));
            dac_array.push_back(Peripheral(QString("leveling"), 7));
            dac_array.push_back(Peripheral(QString("tip"), 8));

            adc_array.push_back(Peripheral(QString("x_1"), 4));
            adc_array.push_back(Peripheral(QString("x_2"), 1));
            adc_array.push_back(Peripheral(QString("y_1"), 2));
            adc_array.push_back(Peripheral(QString("y_2"), 3));
            adc_array.push_back(Peripheral(QString("z_1"), 23));
            adc_array.push_back(Peripheral(QString("z_piezoresistor_amplitude"), 0));
            adc_array.push_back(Peripheral(QString("phase"), 10));

            pga_array.push_back(Peripheral(QString("x_1"), 1, 100));
            pga_array.push_back(Peripheral(QString("x_2"), 2, 100));
            pga_array.push_back(Peripheral(QString("y_1"), 3, 100));
            pga_array.push_back(Peripheral(QString("y_2"), 4, 100));
            pga_array.push_back(Peripheral(QString("leveling"), 5, 0));
            pga_array.push_back(Peripheral(QString("fine_z"), 6, 20));
            pga_array.push_back(Peripheral(QString("coarse_z"), 7, 100));
            pga_array.push_back(Peripheral(QString("dds"), 8, 35));
        }
    #elif OLD_MCU
        PinMap() {
            dac_array.push_back(Peripheral(QString("z_offset_fine"), 6));
            dac_array.push_back(Peripheral(QString("y_1"), 2));
            dac_array.push_back(Peripheral(QString("z_offset_coarse"), 9));
            dac_array.push_back(Peripheral(QString("y_2"), 5));
            dac_array.push_back(Peripheral(QString("x_1"), 4));
            dac_array.push_back(Peripheral(QString("x_2"), 3));
            dac_array.push_back(Peripheral(QString("leveling"), 7));
            dac_array.push_back(Peripheral(QString("tip"), 8));

            adc_array.push_back(Peripheral(QString("x_1"), 4));
            adc_array.push_back(Peripheral(QString("x_2"), 1));
            adc_array.push_back(Peripheral(QString("y_1"), 2));
            adc_array.push_back(Peripheral(QString("y_2"), 3));
            adc_array.push_back(Peripheral(QString("z"), 23));
            adc_array.push_back(Peripheral(QString("z_piezoresistor_amplitude"), 0));
            adc_array.push_back(Peripheral(QString("phase"), 10));

            pga_array.push_back(Peripheral(QString("x_1"), 1));
            pga_array.push_back(Peripheral(QString("x_2"), 2));
            pga_array.push_back(Peripheral(QString("y_1"), 3));
            pga_array.push_back(Peripheral(QString("y_2"), 4));
            pga_array.push_back(Peripheral(QString("leveling"), 5));
            pga_array.push_back(Peripheral(QString("fine_z"), 6));
            pga_array.push_back(Peripheral(QString("coarse_z"), 7));
            pga_array.push_back(Peripheral(QString("dds"), 8));
        }
    #endif

    QList<Peripheral> dac_array;
    QList<Peripheral> adc_array;
    QList<Peripheral> pga_array;

};

#endif // PIN_MAP_H
