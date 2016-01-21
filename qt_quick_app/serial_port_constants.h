#ifndef SERIAL_PORT_CONSTANTS_H
#define SERIAL_PORT_CONSTANTS_H
struct SerialPortConstants {
    const QString AFM_PORT_NAME = "FTDI";
    const int AFM_BAUD_RATE = 76800;
    const int AFM_SUCCESS = 0;
    const int AFM_FAIL = -1;
} SerialPortConstants;
#endif // SERIAL_PORT_CONSTANTS_H
