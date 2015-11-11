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

///**
// * @brief afm_data::is_scan_data_full
// * @return True if all data has been received
// */

//bool afm_data::is_data_full(){
//    //Every vector should have the same dimension, so just pick any and compare its size
//    if(x.size() == numlines * numpts){
//        return true;
//    } else {
//        return false;
//    }
//}

///**
// * @brief   afm_data::append_scan_data appends contents of new ordinate vectors
// *          zoffset, zamp, and zphase into the master(main) data.
// *          It also computes the x and y coords of these input ordinate vectors
// *          using existing bookeeping.
// * @param z_offset_adc
// * @param z_amp_adc
// * @param z_phase_adc
// * @return  0 if new data was added into the main vectors
// *          1 if the master ordinate vectors are full, meaning we have collected all the data
// *          -1 if fault encountered
// */
//int afm_data::append_data(QVector<double> z_offset_adc,
//                                QVector<double> z_amp_adc,
//                                QVector<double> z_phase_adc){
//    //1. Check if everybody has the same size
//    if(!(z_offset_adc.size() == z_amp_adc.size() && z_amp_adc.size() == z_phase_adc.size())) {
//        return -1;
//    }

//    //2. Check if it's already full
//    //Every vector should have the same dimension, so just pick any and compare its size
//    if(x.size() == numlines * numpts){
//        return 1;
//    }

//        //2. Compute and Load the x and y coordinates.
//        //Some special magic might be required here for non-grid schemes
//        //Error if computed size is larger than specified during object creation
//    for(int i=0; i<z_offset_adc.size(); i++) {
//        if(x.last()/delta_x == numpts) {
//        //If x is at end of the line, then go into new line
//            x.append(0);
//            y.append(y.last()+delta_y);
//        } else {
//            //Else append new data in x
//            x.append(x.last()+delta_x);
//            y.append(y.last());
//        }
//    }

//    //3. Load the new ordinate vectors into master
//        zoffset.append(z_offset_adc);
//        zamp.append(z_amp_adc);
//         zphase.append(z_phase_adc);

//    //4. Vector size validity check
//     if(!(x.size() == y.size() && y.size() == zamp.size())) {
//         return -1;
//     }

//    //5. Are the vectors full yet?
//     if(x.size() == numlines * numpts){
//         return 1;
//     } else {
//         return 0;
//     }
//}

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

///**
// * @brief afm_data::print_all debug fcn only
// */
//void afm_data::print_all(){
//    qDebug() << "afm_data PRINT BEGIN";
//    qDebug() << "x,y,zoffset,zamp,zphase";
//    for(int i=0; i<x.size(); i++) {
//        qDebug() << x.at(i) << "," << y.at(i) << "," << zoffset.at(i)<< "," << zamp.at(i)<< "," << zphase.at(i);
//    }
//}

//int afm_data::get_numpts(){
//    return numpts;
//}
//int afm_data::get_numlines() {
//    return numlines;
//}
//int afm_data::get_ratio(){
//    return ratio;
//}

