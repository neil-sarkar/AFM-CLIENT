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
    QVector<double>* amplitudeData=new QVector<double>();
    QVector<double>* phaseData=new QVector<double>();
    QVector<double>* frequencyData=new QVector<double>();
    QVector<double>* z_offset_adc = new QVector<double>();
    QVector<double>* z_amp_adc = new QVector<double>();
    QVector<double>* z_phase_adc = new QVector<double>();
    _abort = false;
    quint16 val;
    forever{
        //check buffer
        //if not empty poll UART
        //read all bytes
        //check struct type for correct return

        if (_abort) {
            emit finished();
            return;
        }


        if(!m_queue.empty()){
            while(res.isEmpty()){
                if (_abort) {
                    emit finished();
                    return;
                }
                res = r_afm.waitForData(AFM_SHORT_TIMEOUT);
            }
            _node = m_queue.front();
            if(!res.isEmpty() || !res.isNull()){
                    //push return buffer
                switch(_node.name){
                    case WRITE:
                        if(res.at(0) == AFM_DAC_WRITE_SELECT){
                            r_queue.push(new returnBuffer(WRITE, AFM_SUCCESS));
                            shift = 1;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACZOFFSETFINE:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));

                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACZOFFSETFINE, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACZOFFSETCOARSE:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACZOFFSETCOARSE, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                    break;
                    case DACBFRD1:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACBFRD1, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACBFRD2:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACBFRD2, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACBFRD3:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACBFRD3, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACZAMP:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACZAMP, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACBR1:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACBR1, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACBR2:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACBR2, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACX1:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACX1, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACX2:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACX2, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACY1:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACY1, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case DACY2:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_DAC_READ_SELECT){
                            r_queue.push(new returnBuffer(DACY2, float(((float)val)/AFM_DAC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case -1:
                    break;
                    case ADCZOFFSET:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_ADC_READ_SELECT){
                            r_queue.push(new returnBuffer(ADCZOFFSET, float(((float)val)/AFM_ADC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case ADC:
                        val=(((unsigned char)res.at(1) << 8) | (unsigned char)res.at(0));
                        if(res.at(2) == AFM_ADC_READ_SELECT){
                            r_queue.push(new returnBuffer(ADC, float(((float)val)/AFM_ADC_SCALING)));
                            shift = 3;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case SETDACVALUES:
                        if(res.at(0) == AFM_SET_DAC_MAX){
                            r_queue.push(new returnBuffer(ADCZOFFSET, AFM_SUCCESS));
                            shift = 1;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case STAGESETSTEP:
                        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_STEP_SELECT){
                            r_queue.push(new returnBuffer(STAGESETSTEP,AFM_SUCCESS));
                            shift = 2;
                        }
                        else{
                        //    return AFM_FAIL;
                        }
                    break;
                    case SETDIRFORWARD:
                        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_DIR_FORW_SELECT){
                            r_queue.push(new returnBuffer(SETDIRFORWARD,AFM_SUCCESS));
                            shift = 2;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case SETDIRBACKWARD:
                        if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_DIR_REVERSE_SELECT){
                            r_queue.push(new returnBuffer(SETDIRBACKWARD,AFM_SUCCESS));
                            shift = 2;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case SETPULSEWIDTH:
                            if(res.at(0) == 'o' && res.at(1) == AFM_STAGE_PW_SELECT){
                                r_queue.push(new returnBuffer(SETPULSEWIDTH,AFM_SUCCESS));
                                shift = 2;
                            }
                            else{
                                //return AFM_FAIL;
                            }
                    break;
                    case SCANPARAMETERS:

                        if(res.at(1) == '@' && res.at(0) == 'o'){
                            shift = 2;
                            r_queue.push(new returnBuffer(SCANPARAMETERS,AFM_SUCCESS));
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case STARTSCAN:
                        if(res.at(0) == AFM_START_SCAN){
                            r_queue.push(new returnBuffer(STARTSCAN,AFM_SUCCESS));
                            shift = 1;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case SCANDATA:
                        for(int i = 0; i < res.length() - 1; i++){
                            z_offset_adc->append(res.at(i)&res.at(++i));
                            z_amp_adc->append(res.at(++i)&res.at(++i));
                            z_phase_adc->append(res.at(++i)&res.at(++i));
                        }

                        if(res.at(res.length() - 1) == AFM_SCAN_STEP){
                            r_queue.push(new returnBuffer(SCANDATA,AFM_SUCCESS,*z_offset_adc,*z_amp_adc,*z_phase_adc));
                            shift = _node.numBytes;
                        }
                        else{
                            //return AFM_FAIL;
                        }
                    break;
                    case FREQSWEEP:
                    // read numPoints*2 bytes + 1 byte of handshake data back
                        //QByteArray freqData = waitForData(AFM_LONG_TIMEOUT);
                        int bytesRead = res.size();
                        int success;
                        //qDebug() << "Bytes Read: " << bytesRead << " Bytes Expected: " << numPoints*2;
                        //bytesRead[freqData.cend()];
                        if (bytesRead != _node.numBytes) {
                            success = AFM_FAIL;
                        }

                        quint16 intVal;
                        quint16 phaseVal;
                        //qDebug() << "Test Bytes to Word: " << BYTES_TO_WORD((quint8)startFrequency, (quint8)(startFrequency >> 8));

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

                        // x-data
                        frequencyData->clear();
//                        for(int i = startFrequency; i < (startFrequency + stepSize*numPoints); i+= stepSize) {
//                            frequencyData->append(double(i));
//                        }

                        if(res.at(bytesRead-1) == AFM_SWEEP_START){
                                shift = _node.numBytes;
                                success = AFM_SUCCESS;
                                r_queue.push(new returnBuffer(FREQSWEEP,success,*amplitudeData,*phaseData,*frequencyData,bytesRead));
                        }

                        break;

                }
                m_queue.pop();
                res = res.remove(0,shift);

            }
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
