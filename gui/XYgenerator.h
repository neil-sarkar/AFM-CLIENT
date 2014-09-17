#ifndef XYGENERATOR_H
#define XYGENERATOR_H

#include <armadillo>
using namespace arma;

int generateXYVoltages(int vMax,
                       int vMin,
                       int vMin2,
                       int numLines,
                       int numPoints,
                       mat& X,
                       mat& Y);

int generateExtendedLineScanMatrices(int vMax,
                                     int vMin,
                                     int vMin2,
                                     int numLines,
                                     mat& lineScan_act1,
                                     mat& lineScan_act2);

int generateThetaMatrix(int vMax,
                        int numLines,
                        const mat& lineScan_act1,
                        const mat& lineScan_act2,
                        mat& thetaRange,
                        mat& thetaMat1);
int generateScanGrid(int numLines,
                     int numPoints,
                     const mat& lineScan_act1,
                     const mat& lineScan_act2,
                     const mat& thetaMat,
                     const mat& thetaRange,
                     mat& lineScanGrid);
#endif // XYGENERATOR_H
