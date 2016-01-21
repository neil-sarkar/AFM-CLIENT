#ifndef SERIAL_PORT_CONSTANTS_H
#define SERIAL_PORT_CONSTANTS_H
// This file contains all constants related to the serial port class
// It allow us to have the notation SerialPortConstants.CONSTANT_NAME

struct SerialPortConstants {
    const QString AFM_PORT_NAME = "FTDI";
    const int AFM_BAUD_RATE = 76800;
    const int AFM_SUCCESS = 0;
    const int AFM_FAIL = -1;
} SerialPortConstants; // initialize SerialPortConstants here

#endif // SERIAL_PORT_CONSTANTS_H
