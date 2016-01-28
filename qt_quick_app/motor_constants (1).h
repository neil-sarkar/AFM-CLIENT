#ifndef MOTOR_CONSTANTS_H
#define MOTOR_CONSTANTS_H
struct MotorConstants {
    const QString AFM_PORT_NAME = "FTDI";
    const int AFM_BAUD_RATE = 76800;
    const int AFM_SUCCESS = 0;
    const int AFM_FAIL = -1;
} MotorConstants; // initialize SerialPortConstants here
#endif // MOTOR_CONSTANTS_H
