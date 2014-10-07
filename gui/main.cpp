#include "mainwindow.h"

//gotta follow this to add QtSerial Port
//http://qt-project.org/wiki/QtSerialPort#fn1921400492531950a902bc4

    QMutex mutex;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1000,600);
    w.show();


//    //On Startup, populate the COM Port Combobox
//    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
//        qDebug() << "Name        : " << info.portName();
//        qDebug() << "Description : " << info.description();
//        qDebug() << "Manufacturer: " << info.manufacturer();

//        if(info.manufacturer()==AFM_MANUFACTURER){
//            w.afm.setPort(info);
//            if (w.afm.open(QIODevice::ReadWrite)){
//                qDebug() << "Sin Value: " << sin(M_PI);
//                w.afm.writeDAC(2,1);
//                //1+sin and 1-sin
//                //qDebug() << "DAC Value: " << w.afm.readDAC(2);
//                //qDebug() << "ADC Value: " << w.afm.readADC(1);

//                while(1){
//                    for(int i=0; i< 360; i++){
//                         //w.afm.writeDAC(0, 1+sin(i*M_PI/360));
//                        // w.afm.writeDAC(0,1);
//                        // w.afm.writeDAC(2,2);
//                        //sleep(0.1);
//                        //w.afm.writeDAC(2, 1-sin(i*M_PI/360));
//                        w.afm.writeDAC(11, 2.5 - (i/10));
//                    }
//                }
//                w.afm.close();
//            }
//        }

//    calculateLineScan(3000,2000,1000);

    return a.exec();
}

