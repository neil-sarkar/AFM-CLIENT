#include "afm.h"

/* Serial Configuration */
#define AFM_MANUFACTURER "FTDI" //Should change this later on to ICPI

#define BYTES_TO_WORD(low, high) (((high) << 8) | (low))

//constexpr int pcb3_dacTable;

void icspiAFM::writeDAC(qint8 dacID, double val)
{
//    if(val>AFM_DAC_MAX_VOLTAGE){
//        return AFM_FAIL;
//    }
    qint16 digitalValue = val / AFM_DAC_SCALING;
    qDebug() << "O" << "DAC Digital Value to be written:" << (digitalValue);
    emit addPayloadByte(dacID);
    emit addPayloadByte((digitalValue & 0xFF));
    emit addPayloadByte((digitalValue >> 8));

    emit writeMsg(AFM_DAC_WRITE_SELECT);
}

void icspiAFM::readDAC(qint8 dacID)
{
    emit addPayloadByte(dacID);
    emit writeMsg(AFM_DAC_READ_SELECT);
}

void icspiAFM::readADC(qint8 adcID)
{
    emit addPayloadByte(adcID);
    emit writeMsg(AFM_ADC_READ_SELECT);
}

void icspiAFM::setRasterStep()
{
//    writeByte(AFM_RASTER_STEP_SELECT);
//    writeByte();
//    writeByte();
//    writeByte();
//    writeByte();
}

/*
void icspiAFM::memsSetOffset(double val)
{
    setPGA_pcb3(PGA_Z_OFFSET, val);
    //There should be a comparison against a maximum value for offset voltage
}

void icspiAFM::memsSetFrequency(double val)
{
    setPGA_pcb3(PGA_Z_OFFSET, val);
    //return AFM_SUCCESS;
}

void icspiAFM::memsSetAmplitude(double val)
{
    //writeDAC(DAC_ZAMP, val);
    setPGA_pcb3(PGA_AMPLITUDE, val);
    //return AFM_SUCCESS;
}
*/

void icspiAFM::memsSetBridgeVoltage(double val)
{
    writeDAC(DAC_BR1, val);
}

void icspiAFM::pidEnable()
{
    clearPayloadBuffer();
    emit writeMsg(AFM_PID_ENABLE_SELECT);
}

void icspiAFM::pidDisable()
{
    clearPayloadBuffer();
    emit writeMsg(AFM_PID_DISABLE_SELECT);
}

void icspiAFM::pidSetP(float P)
{
    emit addPayloadByte(((char *)&P)[0]);
    emit addPayloadByte(((char *)&P)[1]);
    emit addPayloadByte(((char *)&P)[2]);
    emit addPayloadByte(((char *)&P)[3]);
    //There should be a max allowed P value. Return FAIL if P value over the range
    emit writeMsg(AFM_PID_P_SELECT);
}

void icspiAFM::pidSetI(float I)
{
    emit addPayloadByte(((char *)&I)[0]);
    emit addPayloadByte(((char *)&I)[1]);
    emit addPayloadByte(((char *)&I)[2]);
    emit addPayloadByte(((char *)&I)[3]);
    //There should be a max allowed I value. Return FAIL if I value over the range
    emit writeMsg(AFM_PID_I_SELECT);
}

void icspiAFM::pidSetD(float D)
{
    emit addPayloadByte(((char *)&D)[0]);
    emit addPayloadByte(((char *)&D)[1]);
    emit addPayloadByte(((char *)&D)[2]);
    emit addPayloadByte(((char *)&D)[3]);
    //There should be a max allowed I value. Return FAIL if D value over the range
    emit writeMsg(AFM_PID_D_SELECT);
}

void icspiAFM::pidSetValues(qint8 P, qint8 I, qint8 D)
{
    pidSetP(P);
    pidSetI(I);
    pidSetD(D);
}

void icspiAFM::pidSetPoint(float val)
{
    quint16 _setpoint = (float)val / (float)AFM_ADC_SCALING;

    emit addPayloadByte((_setpoint & 0xFF));
    emit addPayloadByte((_setpoint & 0xFF00) >> 8);

    emit writeMsg(AFM_PID_SETPOINT_SELECT);
}

void icspiAFM::stageSetPulseWidth(qint8 val)
{
    //Val should be checked against a value range
    emit addPayloadByte(val);
    emit writeMsg(AFM_STAGE_PW_SELECT);
}

void icspiAFM::stageSetDirForward()
{
    emit writeMsg(AFM_PCBMOT_STAGE_DIR_FWD_SELECT);
}

void icspiAFM::stageSetDirBackward()
{
    emit writeMsg(AFM_PCBMOT_STAGE_DIR_REVERSE_SELECT);
}

void icspiAFM::stageSetStep()
{
    emit writeMsg(AFM_STAGE_PULSE_STEP);
}

void icspiAFM::stageStepForward()
{
    stageSetDirForward();
    stageSetStep();
}

void icspiAFM::stageStepBackward()
{
    stageSetDirBackward();
    stageSetStep();
}

void icspiAFM::stepMotSetSpeed(int speed){
    qDebug() << "O" << "Set Motor Speed" << speed;
    emit addPayloadByte((qint8)speed); //low byte
    emit addPayloadByte(qint8(speed >> 8)); //high byte
    emit writeMsg(AFM_STEPMOT_SPEED);
}

void icspiAFM::stepMotSetState(int state){
    qDebug() << "O" << "Set Motor State" << state;
    if(state == MOT_SLEEP) { //Sleep
        emit clearPayloadBuffer();
        emit writeMsg(AFM_STEPMOT_SLEEP);
    } else if (state == MOT_WAKE) { //Wake
        emit clearPayloadBuffer();
        emit writeMsg(AFM_STEPMOT_WAKE);
    }
}

void icspiAFM::stepMotSetDir(int dir){
    if(dir==MOT_FWD) { //Forward
        emit addPayloadByte(0x66);
        emit writeMsg(AFM_STEPMOT_DIR);
    } else if (dir == MOT_BACK) { //Backward
        emit addPayloadByte(0x62);
        emit writeMsg(AFM_STEPMOT_DIR);
    }
}

void icspiAFM::stepMotSetMicrostep(int microstep_enum){
    emit addPayloadByte((qint8)microstep_enum);
    emit writeMsg(AFM_STEPMOT_MICROSTEP);
}

void icspiAFM::stepMotContGo(){
    emit clearPayloadBuffer();
    emit writeMsg(AFM_STEPMOT_CONT_GO);
}

void icspiAFM::stepMotContStop(){
    emit clearPayloadBuffer();
    emit writeMsg(AFM_STEPMOT_CONT_STOP);
}

void icspiAFM::stepMotSingleStep(){
    emit clearPayloadBuffer();
    emit writeMsg(AFM_STEPMOT_SINGLESTEP);
}

void icspiAFM::setDDSSettings(quint16 numPoints,
                              quint32 startFrequency,
                              quint16 stepSize)
{
    qDebug() << "O" << "Writing to DDS settings";
    // Set DDS settings

    qDebug() << "O" << "Start Freq: " << (quint32)startFrequency;
    // start freq
    // Scale according to the device
    //TODO config device
    double scale = double(qPow(2.0,28) / (5.0*qPow(10,6))); //todo make me constant
    startFrequency = double(startFrequency) * scale;
    emit addPayloadByte((qint8)startFrequency); // LSB low byte
    emit addPayloadByte((qint8)(startFrequency >> 8)); // LSB high byte
    emit addPayloadByte((qint8)(startFrequency >> 16)); // MSB low byte
    emit addPayloadByte((qint8)(startFrequency >> 24)); // MSB high byte

    qDebug() << "O" <<  "Step Size - High Byte: " << (quint16)(stepSize >> 8) << " Low Byte: " << (quint8)stepSize;
    // step size
    stepSize = double(stepSize) * scale;
    emit addPayloadByte((qint8)stepSize); // low byte
    emit addPayloadByte((qint8)(stepSize >> 8)); // high bye

    qDebug() << "O" << "Num Points - High Byte: " << (quint16)(numPoints >> 8) << " Low Byte: " << (quint8)numPoints;
    // num points
    emit addPayloadByte((qint8)numPoints); // low byte
    emit addPayloadByte((qint8)(numPoints >> 8)); // high bye

    emit writeMsg(AFM_DDS_AD9837_SET); //TODO make this configurable
}

// Start the frequency sweep. The data will be fetched from the receiver
void icspiAFM::frequencySweep(quint16 numPoints,
                              quint16 startFrequency,
                              quint16 stepSize)
{
    //writeDAC(AFM_DAC_VCO_ID, 0); // write 0V
    setDDSSettings(numPoints, startFrequency, stepSize);

    // start frequency sweep ASSUMING REV 3 BOARD!!!
    emit clearPayloadBuffer();
    emit writeMsg(AFM_FREQ_SWEEP_AD9837); //TODO make this configurable
}

void icspiAFM::rasterStep(float /*val1*/, float /*val2*/)
{
    //Not too sure about this function
}

void icspiAFM::autoApproach_mcu(double setpoint)
{
    quint16 _setpoint = (double)setpoint / (double)AFM_ADC_SCALING;

    emit addPayloadByte((_setpoint & 0xFF));
    emit addPayloadByte((_setpoint & 0x0F00) >> 8);

    emit writeMsg(AFM_AUTOAPPR_BEGIN);
}

void icspiAFM::autoApproach_mcu_status(){
    clearPayloadBuffer();
    emit writeMsg(AFM_AUTOAPPR_STATUS);
}

void icspiAFM::autoApproach_mcu_stop(){
    clearPayloadBuffer();
    emit writeMsg(AFM_AUTOAPPR_STOP);
}

void icspiAFM::setDACMaxValues(char dacID, double _val)
{
    clearPayloadBuffer();

    quint16 _max = (double)_val / (double)AFM_DAC_SCALING;

    emit addPayloadByte((char)dacID);
    emit addPayloadByte((_max & 0xFF));
    emit addPayloadByte((_max & 0x0F00) >> 8);

    emit writeMsg(AFM_SET_DAC_MAX);
}

void icspiAFM::deviceCalibration(double val, char side)
{
    qint16 _max = val / AFM_DAC_SCALING;
    float a = 0.0000000003438;
    float b = 0.0000001379;
    float c = -0.0000545;
    float d = 0;
    float e = 0;
    float f = 0;

    char _a[sizeof(float)];

    memcpy(_a, &a, sizeof(float));

    char _b[sizeof(float)];
    memcpy(_b, &b, sizeof(float));

    char _c[sizeof(float)];
    memcpy(_c, &c, sizeof(float));

    char _d[sizeof(float)];
    memcpy(_d, &d, sizeof(float));

    char _e[sizeof(float)];
    memcpy(_e, &e, sizeof(float));

    char _f[sizeof(float)];
    memcpy(_f, &f, sizeof(float));


    //4 bytes (o, ‘l’/’r’/‘z’, max_voltage byte 1, max_voltage byte 2)

    emit addPayloadByte(side);
    emit addPayloadByte((_max & 0xFF));
    emit addPayloadByte((_max & 0x0F00) >> 8);

    //12 bytes (a, b, c) – fitted quadratic polynomial coefficients for direct p-v relation (single precision floating point)
    emit addPayloadByte(_a[0]);
    emit addPayloadByte(_a[1]);
    emit addPayloadByte(_a[2]);
    emit addPayloadByte(_a[3]);
    emit addPayloadByte(_b[0]);
    emit addPayloadByte(_b[1]);
    emit addPayloadByte(_b[2]);
    emit addPayloadByte(_b[3]);
    emit addPayloadByte(_c[0]);
    emit addPayloadByte(_c[1]);
    emit addPayloadByte(_c[2]);
    emit addPayloadByte(_c[3]);

    //12 bytes (d, e, f) – fitted quadratic polynomial coefficients for coupling r-v relation (single precision floating point)
    emit addPayloadByte(_d[0]);
    emit addPayloadByte(_d[1]);
    emit addPayloadByte(_d[2]);
    emit addPayloadByte(_d[3]);
    emit addPayloadByte(_e[0]);
    emit addPayloadByte(_e[1]);
    emit addPayloadByte(_e[2]);
    emit addPayloadByte(_e[3]);
    emit addPayloadByte(_f[0]);
    emit addPayloadByte(_f[1]);
    emit addPayloadByte(_f[2]);
    emit addPayloadByte(_f[3]);

    emit writeMsg(AFM_DEVICE_CALIBRATE);
}

void icspiAFM::scanParameters(double vmin_line,
                              double vmin_scan,
                              double vmax,
                              double numpts,
                              double numlines)
{
    /* We need to check that these parameters are valid
     * How?
     *
     *
     * */
    //qDebug() << AFM_DAC_SCALING << endl;
    qint16 _vminLine =  vmin_line / AFM_DAC_SCALING;
    qint16 _vminScan =  vmin_scan / AFM_DAC_SCALING;
    qint16 _vmax = vmax / AFM_DAC_SCALING;
    qint16 _numpts = numpts;
    qint16 _numLines = numlines;

    emit addPayloadByte(_vminLine & 0xFF);
    emit addPayloadByte((_vminLine & 0x0F00) >> 8);

    emit addPayloadByte(_vminScan & 0xFF);
    emit addPayloadByte((_vminScan & 0x0F00) >> 8);

    emit addPayloadByte(_vmax & 0xFF);
    emit addPayloadByte((_vmax & 0x0F00) >> 8);

    emit addPayloadByte(_numpts & 0xFF);
    emit addPayloadByte((_numpts & 0x0F00) >> 8);

    emit addPayloadByte(_numLines & 0xFF);
    emit addPayloadByte((_numLines & 0x0F00) >> 8);

    emit writeMsg(AFM_SCAN_PARAMETERS);
}

void icspiAFM::startScan()
{
    emit writeMsg(AFM_START_SCAN);
}

void icspiAFM::scanStep()
{
    emit writeMsg(AFM_SCAN_STEP);
}

void icspiAFM::startScan_4act()
{
    emit writeMsg(AFM_START_SCAN_4ACT);
}

void icspiAFM::scanStep_4act()
{
    emit writeMsg(AFM_SCAN_STEP_4ACT);
}

void icspiAFM::setPGA_pcb3(int channel, double val)
{
    clearPayloadBuffer();
    emit addPayloadByte(channel);

    qint8 newval = round(20 * log10(val / 100))*2+210;
    emit addPayloadByte(newval);

    emit writeMsg(AFM_SET_PGA_PCB3);
}

void icspiAFM::readSignalPhaseOffset()
{
    emit writeMsg(AFM_READ_SPO);
}

void icspiAFM::forceCurve()
{
    emit writeMsg(AFM_FORCE_CURVE);
}

/*
 * Sends the DAC Table to uC
 * Type:
 *      0 - This is a new request. The function shall transmit the DAC Table from beginning
 *      1 - This is a callback from a previous request.
 *          The function shall transmit next memory block of DAC Table
 *          THe function shall do nothing if all of DAC Table has been transmitted.
 */

void icspiAFM::setDACTable(int block)
{
   //Send the DACTable in batches of 256 points, each point is 2 bytes
   // so total 512 bytes per message
   emit clearPayloadBuffer();
   int start_byte = block * (AFM_DACTABLE_BLK_SIZE);
   for(int k=start_byte; k < start_byte+256; k++){
       auto current_value = pcb3_dacTable[k];
       emit addPayloadByte(current_value & 0xFF);
       emit addPayloadByte((current_value & 0x0F00) >> 8);
   }
   emit writeMsg(AFM_SET_DACTABLE);

}

    /*** ARCHIVED CODE ***
     * Generating the DAC Table in C++. First half is good. Second half is GG.
     * It's easier to just pre-generate it in MATLAB then send it out.
     * RIP

       //Generate the table
       int vmax=3971; //3.2V
       int vmin=124;  //0.1V

       int numpts=4096; //This assumes we always want an array of 4096 points
       quint64 maxpwr=qPow(vmax,2);
       auto minpwr=qPow(vmin,2);
       quint64 linepwr=maxpwr+minpwr;                    //calculate constant power dissipation for the entire line
       auto vstart=qSqrt(linepwr/2);            //Midpoint chosen as a place to start our calculations
       auto lin=linspace(vmin,vstart,vstart-vmin+1);  //Linear array starting at vmin and incrementing by 1 bit

       for(auto i=0; i < vstart-vmin; i++){ //MATLAB uses 1-indexing. C++ uses 0-indexing.
       lin.push_back(double(qSqrt(linepwr-qPow(lin[vstart-vmin-i+1],2))));
       //extending our 'lin' array by calculating the value that would give a constant power
       }

       auto stepSize=(maxpwr-minpwr)/(numpts-1);  //Used to create 4096 steps of equal displacement (equal power increase)
       auto absArray = lin;
       quint16 grid[4096] = {0};

       qDebug() << "BEGIN GRID";

       for (auto i=0; i < numpts; i++){
       unsigned j = 0;
       for(auto currentElem:absArray){
          absArray[j] = qFabs(qPow(currentElem,2)-stepSize*(i-1)-double(minpwr));
          j++;
       }
       //auto index = ;  //This indexing function probably isn't available in C
       grid[i]=lin[minElementIndex(absArray)];
       qDebug() << grid[i] << ",";
       }
     */
    /*
     * Generates n points linearly spaced vector. The spacing between the points is (x2-x1)/(n-1).
     *
     * x1,x2 — Point interval, pair of numeric scalars
     * Point interval, specified as a pair of numeric scalars.
     * x1 and x2 define the interval over which linspace generates points.
     * x1 and x2 must be real, in this C++ implementation.
     * x2 can be either larger or smaller than x1.
     * If x2 is smaller than x1, then the vector contains descending values.
     *
     * n — Number of points real numeric scalar
     * Number of points, specified as a real numeric scalar.

       std::vector<qreal> icspiAFM::linspace(double x1, double x2, int n) {
        std::vector<qreal> array;
        double step = (x2-x1) / (n-1);

        if(x1 < x2){
            while(x1 <= x2) {
                array.push_back(x1);
                x1 += step;           // could recode to better handle rounding errors
            }
        } else {
            while(x1 >= x2) {
                array.push_back(x1);
                x1 -= step;           // could recode to better handle rounding errors
            }
        }
        return array;
       }
     */


void icspiAFM::sigGen(quint8 ratio,double numpts,double numlines)
{
    qint16 _numpts = numpts;
    qint16 _numLines = numlines;

    emit addPayloadByte(ratio);

    emit addPayloadByte(_numpts & 0xFF);
    emit addPayloadByte((_numpts & 0x0F00) >> 8);

    emit addPayloadByte(_numLines & 0xFF);
    emit addPayloadByte((_numLines & 0x0F00) >> 8);

    emit writeMsg(AFM_SET_SIGGEN);
}
