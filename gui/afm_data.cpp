#include "afm_data.h"

/**
 * @brief   afm_data is the constructor for the class.
 *          Once the object is created, these params cannot be changed.
 * @param n_pts
 * @param n_lines
 * @param _ratio    For grid scan. Refer to the ratio Enum.
 */
afm_data::afm_data(int n_pts, int n_lines, int _ratio){
    numpts = n_pts;
    numlines = n_lines;
    ratio = _ratio;
    ratio_enum_to_deltaxy(ratio);
}

/**
 * @brief afm_data::is_scan_data_full For master data store only
 * @return True if all data has been received
 */

bool afm_data::is_data_full(){
    //Every vector should have the same dimension, so just pick any and compare its size
    if((numlines * numpts * 2) == (zoffset_fwd.size() + zoffset_rev.size())){
        return true;
    } else {
        return false;
    }
}

/**
 * @brief afm_data::get_datapoint_count
 * @return The total number of data points collected thus far (sum of fwd and reverse)
 */

int afm_data::get_datapoint_count(){
    return zoffset_fwd.size() + zoffset_rev.size() + zoffset_rev_temp.size();
}

/**
 * @brief afm_data::get_scan_progress
 * @return A percentage of how much data is left. For UI use only.
 */
int afm_data::get_scan_progress(){
   // qDebug() << "get_datapoint_count " << get_datapoint_count();
    float pct = (double)(get_datapoint_count() / (numlines * numpts * 2.0));
   // qDebug() << "get_scan_progress " << pct;
    return pct * 100;
}

bool afm_data::get_rev_mode(){
    return rev_mode;
}

/**
 * @brief   afm_data::append_scan_data appends contents of new ordinate vectors
 *          zoffset, zamp, and zphase into the master(main) data.
 *          It also computes the x and y coords of these input ordinate vectors
 *          using existing bookeeping.
 * @param z_offset_adc
 * @param z_amp_adc
 * @param z_phase_adc
 * @return  0 if new data was added into the main vectors
 *          1 if the master ordinate vectors are full, meaning we have collected all the data
 *          -1 if fault encountered
 */
int afm_data::append_data(QVector<double> z_offset_adc,
                            QVector<double> z_amp_adc,
                            QVector<double> z_phase_adc){
    //1. Check if everybody has the same size
    if(!(z_offset_adc.size() == z_amp_adc.size() && z_amp_adc.size() == z_phase_adc.size())) {
        append_error = true;
        return -1;
    } else {
        append_error = false;
    }

    //2. Check if we are already full
    //Every vector should have the same dimension, so just pick any and compare its size
    //This should be done in reverse mode.
//    if(x.size() == numlines * numpts && rev_mode){
//        return 1;
//    }

    for(int i=0; i<z_offset_adc.size(); i++) {
        //5. Compute and Load the x and y coordinates.
        //The main bookkeeping algorithm is here
        if(x.size() == 0){
            //Corner case: First element, we start at (0,0)
            x.append(0);
            y.append(0);
            rev_mode = false;
        } else if(x_index_pos + 1 == numpts && !rev_mode) {
            //This indicates that we are at the boundary for data point loading
            //If already in reverse mode, then move to a new line, and set rev_mode to false
            //Else, set rev_mode to true
            rev_mode = true;
            zoffset_rev_temp.clear();
            zamp_rev_temp.clear();
            zphase_rev_temp.clear();
        } else if (x_index_pos == 0 && rev_mode){
           rev_mode = false;
           //Append rev temp array into rev master arrays
           //Clear the temp arrays
           zoffset_rev.append(zoffset_rev_temp);
           zamp_rev.append(zamp_rev_temp);
           zphase_rev.append(zphase_rev_temp);
           zoffset_rev_temp.clear();
           zamp_rev_temp.clear();
           zphase_rev_temp.clear();
           //Create a new row
           x.append(0); //Do not increment x_index_pos here. Stay the same.
           y.append(y.last()+delta_y);
        } else {
            //Nothing special, do it normally
            //If forward mode, add delta_x to x, and append y
            //If reverse mode, do nothing with x and y.
            if(rev_mode){
                x_index_pos--;
            } else {
                x.append(x.last()+delta_x);
                y.append(y.last());
                x_index_pos++;
            }
        }

        //4. Load the new ordinate vectors into master, one at a time
        if(rev_mode){
            //Load backwards into temp if it's rev_mode
            zoffset_rev_temp.prepend(z_offset_adc.at(i));
            zamp_rev_temp.prepend(z_amp_adc.at(i));
            zphase_rev_temp.prepend(z_phase_adc.at(i));
        } else {
            if(x.size()==1){ //corner case
                x_index_pos = 0;
            }
            //Load forwards normally
            zoffset_fwd.append(z_offset_adc.at(i));
            zamp_fwd.append(z_amp_adc.at(i));
            zphase_fwd.append(z_phase_adc.at(i));
        }
    }

    //corner case for the last data point in reverse
    if(get_datapoint_count() == numlines * numpts * 2){
        zoffset_rev.append(zoffset_rev_temp);
        zamp_rev.append(zamp_rev_temp);
        zphase_rev.append(zphase_rev_temp);
    }

    //6. Are the vectors full yet?
    if(is_data_full()){
         return 1;
     } else {
         return 0;
     }
}

/**
 * @brief ratio_enum_to_deltaxy
 * @param ratio_enum
 */
void afm_data::ratio_enum_to_deltaxy(int ratio_enum){
    switch(ratio_enum) {
    case RATIO_7_1:
        delta_x = 7;
        delta_y = 1;
        break;
    case RATIO_3_1:
        delta_x = 3;
        delta_y = 1;
        break;
    case RATIO_1_1:
        delta_x = 1;
        delta_y = 1;
        break;
    case RATIO_0_1:
        delta_x = 1;
        delta_y = 0;
        break;
    }
}

/**
 * @brief afm_data::print_all debug fcn only
 */
void afm_data::print_all(){
    qDebug() << "afm_data PRINT BEGIN";
    qDebug() << "x,y,zamp_fwd,zoffset_fwd,zphase_fwd,zoffset_rev";
    for(int i=0; i<x.size(); i++) {
        qDebug() << x.at(i) << "," << y.at(i) << "," << zamp_fwd.at(i)<< "," << zoffset_fwd.at(i)<< "," << zphase_fwd.at(i) << "," << zphase_rev.at(i);
    }
}

void afm_data::print_amp(){
  //  qDebug() << "afm_data PRINT BEGIN";
   // qDebug() << "x  y  zoffset";
    for(int i=0; i<x.size(); i++) {
        qDebug() << QString::number(y.at(i), 'f', 3) << " " << QString::number(x.at(i), 'f', 3)  << " " << QString::number(zoffset_fwd.at(i), 'f', 5) ;
    }
}

int afm_data::get_numpts(){
    return numpts;
}
int afm_data::get_numlines() {
    return numlines;
}
int afm_data::get_ratio(){
    return ratio;
}
bool afm_data::has_error(){
    return append_error;
}

QByteArray afm_data::save_txt(int type){
    QByteArray file_bytes;
    file_bytes.clear();
    QTextStream stream(&file_bytes, QIODevice::WriteOnly);
    for(int i=0; i<x.size(); i++){
        stream << QString::number(x.at(i), 'f', 3);
        stream << " ";
        stream << QString::number(y.at(i), 'f', 3);
        switch(type){
        case 1:
            stream << QString(" %1\n").arg(zoffset_fwd.at(i)).toUtf8();
            break;
        case 2:
            stream << QString(" %1\n").arg(zoffset_rev.at(i)).toUtf8();
            break;
        }
    }
    return file_bytes;
}

/**
 * @brief afm_data::save_gxyzf
 * @return Raw bytes for writing to gxyzf file.
 */

//NOTE!!! It seems gwiddion cannot read these files when you drag it in. MUST use File -> Open
//Seems gwyddion doesn't quite like the file format....
QByteArray afm_data::save_gxyzf(){
    QByteArray file_bytes;
    file_bytes.clear();

    QString header =
            QString("Gwyddion XYZ Field 1.0\nNChannels = 6\nNPoints = %1\nXRes = %2\nYRes = %3\nTitle1 = zamp_fwd\nTitle2 = zoffset_fwd\nTitle3 = zphase_fwd\nTitle4 = zamp_rev\nTitle5 = zoffset_rev\nTitle6 = zphase_rev\n")
            .arg(x.size()*y.size())
            .arg(x.size())
            .arg(y.size());

//    "Gwyddion XYZ Field 1.0\nNChannels = 6\n"
//              << "NPoints = " << QString::number(x.size()) << "\n"
//              << "Title1 = zamp_fwd\nTitle2 = zoffset_fwd\nTitle3 = zphase_fwd\n"
//              << "Title4 = zamp_rev\nTitle5 = zoffset_rev\nTitle6 = zphase_rev"

   // stream << header.toUtf8();
    //Remove the first four padding from string
    file_bytes.append(header.toUtf8());
    int temp1 = (8 - (file_bytes.size() % 8));
    qDebug() << "NUL " << temp1;
    //Padding
    for(int i=0; i<temp1; i++){
       file_bytes.append("\0"); //debugging only -- to change to "\0" later
       // stream << (quint8)0;
    }

   // return file_bytes;

  //  QDataStream stream(&file_bytes, QIODevice::WriteOnly);
 //   stream.setByteOrder(QDataStream::LittleEndian);

    for(int i=0; i<x.size(); i++){
      //  stream <<x.at(i)<<y.at(i)<<zamp_fwd.at(i)<<zoffset_fwd.at(i)<<zphase_fwd.at(i)<<zamp_rev.at(i)<<zoffset_rev.at(i)<<zphase_rev.at(i);
        file_bytes.append(reinterpret_cast<const char*>(&x.at(i)), sizeof(x.at(i)));
        file_bytes.append(reinterpret_cast<const char*>(&y.at(i)), sizeof(y.at(i)));
        file_bytes.append(reinterpret_cast<const char*>(&zamp_fwd.at(i)), sizeof(zamp_fwd.at(i)));
        file_bytes.append(reinterpret_cast<const char*>(&zoffset_fwd.at(i)), sizeof(zoffset_fwd.at(i)));
        file_bytes.append(reinterpret_cast<const char*>(&zphase_fwd.at(i)), sizeof(zphase_fwd.at(i)));
        file_bytes.append(reinterpret_cast<const char*>(&zamp_rev.at(i)), sizeof(zamp_rev.at(i)));
        file_bytes.append(reinterpret_cast<const char*>(&zoffset_rev.at(i)), sizeof(zoffset_rev.at(i)));
        file_bytes.append(reinterpret_cast<const char*>(&zphase_rev.at(i)), sizeof(zphase_rev.at(i)));
//        file_stream.append(x.at(i));
//        file_stream.append(y.at(i));
//        file_stream.append(x.at(i)+y.at(i)+zamp_fwd.at(i)+zoffset_fwd.at(i)+zphase_fwd.at(i)+zamp_rev.at(i)+zoffset_rev.at(i)+zphase_rev.at(i));
//        file_stream.append(x.at(i)+y.at(i)+zamp_fwd.at(i)+zoffset_fwd.at(i)+zphase_fwd.at(i)+zamp_rev.at(i)+zoffset_rev.at(i)+zphase_rev.at(i));
//        file_stream.append(x.at(i)+y.at(i)+zamp_fwd.at(i)+zoffset_fwd.at(i)+zphase_fwd.at(i)+zamp_rev.at(i)+zoffset_rev.at(i)+zphase_rev.at(i));
//        file_stream.append(x.at(i)+y.at(i)+zamp_fwd.at(i)+zoffset_fwd.at(i)+zphase_fwd.at(i)+zamp_rev.at(i)+zoffset_rev.at(i)+zphase_rev.at(i));
//        file_stream.append(x.at(i)+y.at(i)+zamp_fwd.at(i)+zoffset_fwd.at(i)+zphase_fwd.at(i)+zamp_rev.at(i)+zoffset_rev.at(i)+zphase_rev.at(i));
    }
    return file_bytes;
}

