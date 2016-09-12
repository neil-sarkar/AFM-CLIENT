#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

extern const QString ADC_Read;
extern const QString AFM_Begin_Auto_Approach;
extern const QString AFM_Calibrate;
extern const QString AFM_Generate_Force_Curve;
extern const QString AFM_Get_Auto_Approach_Status;
extern const QString AFM_Read_Signal_Phase_Offset;
extern const QString AFM_Set_Dac_Table;
extern const QString AFM_Set_Scan_Parameters;
extern const QString AFM_Set_Signal_Generation;
extern const QString AFM_Start_Frequency_Sweep_AD5932;
extern const QString AFM_Start_Frequency_Sweep_AD9837;
extern const QString AFM_Start_Scan;
extern const QString AFM_Step_Scan;
extern const QString AFM_Stop_Auto_Approach;
extern const QString AFM_Get_Resistances;
extern const QString DAC_Read;
extern const QString DAC_Set_Max_Value;
extern const QString DAC_Write;
extern const QString DDS_Set_AD5932;
extern const QString DDS_Set_AD9837;
extern const QString Motor_Run_Continuous;
extern const QString Motor_Set_Direction;
extern const QString Motor_Set_Microstep;
extern const QString Motor_Set_Single_Step;
extern const QString Motor_Set_Speed;
extern const QString Motor_Set_State_Asleep;
extern const QString Motor_Set_State_Awake;
extern const QString Motor_Stop_Continuous;
extern const QString PGA_Set;
extern const QString PID_Disable;
extern const QString PID_Enable;
extern const QString PID_Set_Derivative;
extern const QString PID_Set_PM;
extern const QString PID_Set_Integral;
extern const QString PID_Set_Proportional;
extern const QString PID_Set_Setpoint;
extern const QString Stage_Set_Pulse_Step;
extern const QString Stage_Set_Pulse_Width;
extern const QString Scanner_Set_Dwell_Time;
extern const QString Scanner_Set_Num_Averages;
extern const QString Scanner_Set_Send_Back_Count;
extern const QString Scanner_Set_Leveling_Direction;
extern const QString Scanner_Set_Zoom;
extern const QString AFM_Get_Auto_Approach_State;

extern const char Message_Delimiter;
extern const char Newline_Character;
extern const char Escape_Character;
extern const char Mask_Character;
extern const char AFM_Success_Response;
extern const int Special_Message_Character;
extern const int Auto_Approach_Info_Character;
extern const int Auto_Approach_Stopped_Character;
extern const int Num_Meta_Data_Bytes;
extern const int Message_Size_Minimum;
extern const int Set_Receive_Bytes_Error;

#endif // CONSTANTS_H
