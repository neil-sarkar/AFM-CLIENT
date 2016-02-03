#include "constants.h"

QHash<QString, CommandNode> command_hash;
const QString ADC_Read = "ADC_Read";
const QString AFM_Begin_Auto_Approach = "AFM_Begin_Auto_Approach";
const QString AFM_Calibrate = "AFM_Calibrate";
const QString AFM_Generate_Force_Curve = "AFM_Generate_Force_Curve";
const QString AFM_Get_Auto_Approach_Status = "AFM_Get_Auto_Approach_Status";
const QString AFM_Read_Signal_Phase_Offset = "AFM_Read_Signal_Phase_Offset";
const QString AFM_Set_Dac_Table = "AFM_Set_Dac_Table";
const QString AFM_Set_Scan_Parameters = "AFM_Set_Scan_Parameters";
const QString AFM_Set_Signal_Generation = "AFM_Set_Signal_Generation";
const QString AFM_Start_Frequency_Sweep_AD5932 = "AFM_Start_Frequency_Sweep_AD5932";
const QString AFM_Start_Frequency_Sweep_AD9837 = "AFM_Start_Frequency_Sweep_AD9837";
const QString AFM_Start_Scan = "AFM_Start_Scan";
const QString AFM_Step_Scan = "AFM_Step_Scan";
const QString AFM_Stop_Auto_Approach = "AFM_Stop_Auto_Approach";
const QString DAC_Read = "DAC_Read";
const QString DAC_Set_Max_Value = "DAC_Set_Max_Value";
const QString DAC_Write = "DAC_Write";
const QString DDS_Set_AD5932 = "DDS_Set_AD5932";
const QString DDS_Set_AD9837 = "DDS_Set_AD9837";
const QString Motor_Run_Continuous = "Motor_Run_Continuous";
const QString Motor_Set_Direction = "Motor_Set_Direction";
const QString Motor_Set_Microstep = "Motor_Set_Microstep";
const QString Motor_Set_Single_Step = "Motor_Set_Single_Step";
const QString Motor_Set_Speed = "Motor_Set_Speed";
const QString Motor_Set_State_Asleep = "Motor_Set_State_Asleep";
const QString Motor_Set_State_Awake = "Motor_Set_State_Awake";
const QString Motor_Stop_Continuous = "Motor_Stop_Continuous";
const QString PGA_Set = "PGA_Set";
const QString PID_Disable = "PID_Disable";
const QString PID_Enable = "PID_Enable";
const QString PID_Set_Derivative = "PID_Set_Derivative";
const QString PID_Set_Integral = "PID_Set_Integral";
const QString PID_Set_Proportional = "PID_Set_Proportional";
const QString PID_Set_Setpoint = "PID_Set_Setpoint";
const QString Stage_Set_Pulse_Step = "Stage_Set_Pulse_Step";
const QString Stage_Set_Pulse_Width = "Stage_Set_Pulse_Width";

const char Message_Delimiter = 0x0A;
const char Newline_Character = 0x0A;
const char Escape_Character = 0x10;
const char Mask_Character = 0x80;
const int Num_Meta_Data_Bytes = 2; // tag and id are the only two bytes that are 'metadata'
const int Message_Size_Minimum = 2; // tag and id make up the minimum message
