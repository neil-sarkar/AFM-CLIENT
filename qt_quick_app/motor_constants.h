#ifndef MOTOR_CONSTANTS_H
#define MOTOR_CONSTANTS_H
struct MotorCommands {
    const int SetSpeed = 0x32;
    const int SetSpeed = 0x32;
} MotorCommands // initialize SerialPortConstants here

struct MotorCommandResponseLength {
    const int SetSpeed = 2;
    const int
};

#endif // MOTOR_CONSTANTS_H


#define AFM_STEPMOT_SLEEP_RSPLEN    2
#define AFM_STEPMOT_SPEED  0x32
#define AFM_STEPMOT_SPEED_RSPLEN    2
#define AFM_STEPMOT_DIR  0x36
#define AFM_STEPMOT_DIR_RSPLEN    2
#define AFM_STEPMOT_CONT_GO  0x33
#define AFM_STEPMOT_CONT_GO_RSPLEN    2
#define AFM_STEPMOT_CONT_STOP  0x37
#define AFM_STEPMOT_CONT_STOP_RSPLEN    2
#define AFM_STEPMOT_MICROSTEP  0x30
#define AFM_STEPMOT_MICROSTEP_RSPLEN    2
#define AFM_STEPMOT_SINGLESTEP  0x31
#define AFM_STEPMOT_SINGLESTEP_RSPLEN    2
