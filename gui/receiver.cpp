#include "receiver.h"

#define AFM_SHORT_TIMEOUT 50
#define AFM_LONG_TIMEOUT 5000

void receiver::openPort(QSerialPortInfo _port){
    r_afm.close();
    r_afm.setPort(_port);
    r_afm.open(QIODevice::ReadWrite);
    r_afm.setBaudRate(76800);
}

void receiver::mainLoop()
{
    receivetype _node;
    QByteArray res;
    int shift = 0;
    _abort = false;
    quint16 val;

    double signal;
    double offset;
    double phase;

    /********************Return Buffers********************/
    QVector<double>* amplitudeData=new QVector<double>();
    QVector<double>* phaseData=new QVector<double>();
    QVector<double>* frequencyData=new QVector<double>();
    QVector<double>* z_offset_adc = new QVector<double>();
    QVector<double>* z_amp_adc = new QVector<double>();
    QVector<double>* z_phase_adc = new QVector<double>();



    forever{


        /**********************************************************
         * check to see if the buffer is not empty. If !empty read
         * data from the serial port. Based on the node in the queue
         * shift the serial buffer by the appropriate number of bytes.
         * Push a node onto the return queue with the data
         * Repeat.
         **********************************************************/

        if (_abort) {
            delete amplitudeData;
            delete phaseData;
            delete frequencyData;
            delete z_offset_adc;
            delete z_amp_adc;
            delete z_phase_adc;
            emit finished();
            return;
        }


        if(!m_queue.empty()){
            isError = false;
            _node = m_queue.front();
            while(res.isEmpty()){
                if (_abort) {
                    emit finished();
                    return;
                }
                if(_node.name == DEVICECALIBRATION || _node.name == AUTOAPPROACH)
                    res = r_afm.waitForData(AFM_LONG_TIMEOUT);
                else
                    res = r_afm.waitForData(AFM_SHORT_TIMEOUT);
            }

            if(!res.isEmpty() || !res.isNull()){
                switch(_node.name){
                    case WRITE:
                        if(res.at(0) == AFM_DAC_WRITE_SELECT){
                            r_queue.push(new returnBuffer(WRITE, AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACZOFFSETFINE:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACZOFFSETFINE, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACZOFFSETCOARSE:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACZOFFSETCOARSE, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                    break;
                    case DACBFRD1:                       
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                             val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACBFRD1, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACBFRD2:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACBFRD2, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACBFRD3:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACBFRD3, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACZAMP:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACZAMP, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACBR1:                        
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACBR1, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACBR2:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACBR2, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACX1:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACX1, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACX2:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACX2, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACY1:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACY1, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DACY2:
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(DACY2, float(((float)val)/AFM_DAC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case ADCZOFFSET:                        
                        if(res.at(2) == AFM_ADC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(ADCZOFFSET, float(((float)val)/AFM_ADC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case ADCPHASE:
                        if(res.at(2) == AFM_ADC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(ADCPHASE, float(((float)val)/AFM_ADC_SCALING)));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case ADC:
                        if(res.at(2) == AFM_ADC_READ_SELECT){
                            val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            r_queue.push(new returnBuffer(ADC, float(((float)val)/AFM_ADC_SCALING)));
                            shift = 3;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case READSIGNALPHASEOFFSET:
                        if(res.at(_node.numBytes) == AFM_ADC_READ_SPO){
                            signal = (((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                            offset =(((unsigned char)res.at(3) << 8) | (unsigned char)res.at(2));
                            phase =(((unsigned char)res.at(5) << 8) | (unsigned char)res.at(4));
                            r_queue.push(new returnBuffer(READSIGNALPHASEOFFSET,AFM_SUCCESS,signal/AFM_DAC_SCALING,offset/AFM_DAC_SCALING,phase/AFM_DAC_SCALING));
                            shift = _node.numBytes+1;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETDACVALUES:
                        if(res.at(0) == AFM_SET_DAC_MAX){
                            r_queue.push(new returnBuffer(ADCZOFFSET, AFM_SUCCESS));
                            shift = 1;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case STAGESETSTEP:
                        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_STEP_SELECT){
                            r_queue.push(new returnBuffer(STAGESETSTEP,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETDIRFORWARD:
                        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_DIR_FORW_SELECT){
                            r_queue.push(new returnBuffer(SETDIRFORWARD,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETDIRBACKWARD:
                        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_DIR_REVERSE_SELECT){
                            r_queue.push(new returnBuffer(SETDIRBACKWARD,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETPULSEWIDTH:
                        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_PW_SELECT){
                            r_queue.push(new returnBuffer(SETPULSEWIDTH,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case ABORTCONTINUOUS:
                        if(res.at(0) == 'o' && res.at(1) == AFM_ABORT_AUTO_APPROACH){
                            r_queue.push(new returnBuffer(ABORTCONTINUOUS,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case AUTOAPPROACH:
                        if(res.at(0) == 'o' && res.at(_node.numBytes) == AFM_AUTOAPPROACH_SELECT){
                            r_queue.push(new returnBuffer(AUTOAPPROACH,AFM_SUCCESS));
                            shift = _node.numBytes + 1;
                        }
                        else if(res.at(0) == 'f'){
                            r_queue.push(new returnBuffer(AUTOAPPROACH,AFM_FAIL));
                            shift = 2;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SCANPARAMETERS:

                        if(res.at(1) == AFM_SCAN_PARAMETERS && res.at(0) == 'o'){
                            shift = 2;
                            r_queue.push(new returnBuffer(SCANPARAMETERS,AFM_SUCCESS));
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case STARTSCAN:
                        if(res.at(0) == AFM_START_SCAN){
                            r_queue.push(new returnBuffer(STARTSCAN,AFM_SUCCESS));
                            shift = 1;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SCANDATA:
                        for(int i = 0; i < _node.numBytes - 1; i++){
                            z_offset_adc->append(res.at(i)&res.at(++i));
                            z_amp_adc->append(res.at(++i)&res.at(++i));
                            z_phase_adc->append(res.at(++i)&res.at(++i));
                        }

                        if(res.at(_node.numBytes) == AFM_SCAN_STEP){
                            r_queue.push(new returnBuffer(SCANDATA,AFM_SUCCESS,*z_offset_adc,*z_amp_adc,*z_phase_adc));
                            shift = _node.numBytes+1; //plus one for acknowledgement byte
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case PIDENABLE:
                        if(res.at(0) == AFM_PID_ENABLE_SELECT){
                            r_queue.push(new returnBuffer(PIDENABLE,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case PIDDISABLE:
                        if(res.at(0) == AFM_PID_DISABLE_SELECT){
                            r_queue.push(new returnBuffer(PIDDISABLE,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETP:
                        if(res.at(0) == AFM_PID_P_SELECT){
                            r_queue.push(new returnBuffer(SETP,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETI:
                        if(res.at(0) == AFM_PID_I_SELECT){
                            r_queue.push(new returnBuffer(SETI,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETD:
                        if(res.at(0) == AFM_PID_D_SELECT){
                            r_queue.push(new returnBuffer(SETD,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETPOINT:
                        if(res.at(0) == AFM_PID_SETPOINT_SELECT){
                            r_queue.push(new returnBuffer(SETPOINT,AFM_SUCCESS));
                            shift = _node.numBytes;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETDDS:
                        if(res.at(0) == AFM_DDS_SWEEP_SET){
                           r_queue.push(new returnBuffer(SETDDS,AFM_SUCCESS));
                           shift = 1;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case SETPGA:
                        if(res.at(0) == 'o' && res.at(1) == AFM_SET_PGA){
                           r_queue.push(new returnBuffer(SETPGA,AFM_SUCCESS));
                           shift = 2;
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case DEVICECALIBRATION:
                        if(res.at(_node.numBytes) == 'o')
                        {
                            r_queue.push(new returnBuffer(DEVICECALIBRATION,AFM_SUCCESS));
                            shift = _node.numBytes + 1; //acknowledge byte
                        }
                        else{
                            isError = true;
                        }
                    break;
                    case FREQSWEEP:

                        int bytesRead;
                        int success;

                        /* clear the ack from dds settings */
                        if(res.at(0) == AFM_DDS_SWEEP_SET){
                           shift = 1;
                           res = res.remove(0,shift);
                           bytesRead  = res.size();
                        }
                        if (bytesRead != _node.numBytes) {
                            success = AFM_FAIL;
                        }

                        quint16 intVal;
                        quint16 phaseVal;

                        // y data
                        amplitudeData->clear();
                        phaseData->clear();
                        for(int i = 0; i < _node.numBytes - 1; i+=4) {
                            intVal = BYTES_TO_WORD((quint8)res[i], (quint8)res[i+1]);
                            phaseVal = BYTES_TO_WORD((quint8)res[i+2],(quint8)res[i+3]);
                            qDebug() << "Int Val: " << intVal;
                            amplitudeData->append( double(intVal)/AFM_ADC_SCALING );
                            phaseData->append(double(phaseVal)/AFM_ADC_SCALING);
                        }


                        if(res.at(bytesRead-1) == AFM_SWEEP_START){
                                shift = _node.numBytes;
                                success = AFM_SUCCESS;
                                r_queue.push(new returnBuffer(FREQSWEEP,success,*amplitudeData,*phaseData,bytesRead));
                        }

                        break;

                }
                if(isError){

                    while(!m_queue.empty())
                        m_queue.pop();
                    res.clear();
                    emit serialError();
                }
                else{
                    //we good
                    m_queue.pop();
                    res = res.remove(0,shift);
                }


            }
        }
        else
        {
            //sometimes there are extra bytes in the buffer when we do an
            //approach. So if there is nothing in the receive queue just
            //empty the buffer to make sure
            res.clear();
        }
    };
}
void receiver::abort()
{
    _abort = true;
}
receiver::~receiver()
{
    emit finished();
}
