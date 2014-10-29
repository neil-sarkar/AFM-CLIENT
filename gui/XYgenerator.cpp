#include <XYGenerator.h>

using namespace arma;

int generateXYVoltages(int vMax,
                       int vMin,
                       int vMin2,
                       int numLines,
                       int numPoints,
                       mat& X,
                       mat& Y){
    //Maybe there should be a check for minimum and maximum bounds of input values

    mat lineScan_act1; //Dynamically Resized Based On Values
    mat lineScan_act2; //Dynamically Resized Based On Values
    mat thetaRange(2, numLines); //Contains min/max pair of theta values for each lineScan
    mat thetaMat(2, numLines);
    mat lineScanGrid;
    generateExtendedLineScanMatrices(vMax, vMin, vMin2, numLines,lineScan_act1, lineScan_act2);
    generateThetaMatrix(vMax, numLines, lineScan_act1, lineScan_act2, thetaRange, thetaMat);
    generateScanGrid(numLines,numPoints,lineScan_act1, lineScan_act2, thetaMat,thetaRange, lineScanGrid);
    mat lineScanGridMirrored(join_cols(lineScanGrid,flipud(lineScanGrid)));
    X.resize(lineScanGrid.n_rows*2, numLines);
    Y.resize(lineScanGrid.n_rows*2, numLines);

    for(int i=1; i<numLines; i++){
         X.col(i-1)=lineScanGridMirrored.col(((2*i)-1)-1)*3.3/4095;
         Y.col(i-1)=lineScanGridMirrored.col((2*i)-1)*3.3/4095;
    }
}

int generateExtendedLineScanMatrices(int vMax,
                     int vMin,
                     int vMin2,
                     int numLines,
                     mat& lineScan_act1,
                     mat& lineScan_act2)
{

    //Add some checks for inputs and return some error values that need to be displayed back on UI

    //Calculate maximum and minimum line power for actuators
    int maxLinePower = pow(vMax,2);
    int minLinePower = pow(vMin,2);

    for(int i=1; i <= numLines; i++){

        int linePower=((maxLinePower-minLinePower) * i / numLines) + minLinePower;//Calculate power for each lineScan
        int vStart=round(sqrt(linePower/2));  //Calculate starting voltage for both actuators.
        int numLineScanValues=vStart-vMin2;  //Calculate number of linescan values for each power

        vec nonLinearPart(numLineScanValues);
        vec linearPart(numLineScanValues);

        for(int j=1; j<= numLineScanValues; j++){
            //Calculate linear and non-linear parts of the linescan
            nonLinearPart(j-1)=round(sqrt(linePower - pow(vStart-j,2)));
            linearPart(j-1)=vStart-j;
        }

        //Based on the above calculated parts, generate extended linescans for both actuators
        //Dynamically resize the matrices based on the range of vallues for each Line Scan
        lineScan_act1.resize((linearPart.n_rows) + (nonLinearPart.n_rows), numLines);
        lineScan_act2.resize((linearPart.n_rows) + (nonLinearPart.n_rows), numLines);
        lineScan_act1.col(i-1)=join_cols(flipud(linearPart),nonLinearPart);
        lineScan_act2.col(i-1)=join_cols(flipud(nonLinearPart),linearPart);
    }
    return 0;
}

int generateThetaMatrix(int vMax,
                        int numLines,
                        const mat& lineScan_act1,
                        const mat& lineScan_act2,
                        mat& thetaRange,
                        mat& thetaMat)
{
    //mat thetaRange(2, numLines); //This variable stores pairs of min/max theta values for each line
    for(int i=1; i <= numLines; i++){
        vec theta; //Temporary Variable to hold all thetas
        for(int j=1; j<=lineScan_act1.n_rows; j++){
            theta.resize(j,1);
            if(lineScan_act1(j-1, i-1)!=0){
                theta(j-1)=(pow(lineScan_act1(j-1,i-1),2)-pow(lineScan_act2(j-1,i-1),2)) / pow(vMax,2) + M_PI/2;
            }
            else{
                theta(j-1)=M_PI/2;
            }
        }
        thetaMat.resize(theta.n_rows, numLines);
        thetaMat.col(i-1)=theta;
        thetaRange(0,i-1)=theta.min();
        thetaRange(1,i-1)=theta.max();
    }
}

int generateScanGrid(int numLines,
                     int numPoints,
                     const mat& lineScan_act1,
                     const mat& lineScan_act2,
                     const mat& thetaMat,
                     const mat& thetaRange,
                     mat& lineScanGrid)
{
    //Initialize matrix to hole numPoints values for each linescan x 2 actuators
    lineScanGrid.resize(numPoints, numLines*2);
    for(int i=1; i<=numLines; i++){
        //Replace this with linspace if it fails
        vec q=linspace(thetaRange(0,i-1),thetaRange(1, i-1),numPoints);
        for(int j=1; j<=numPoints; j++){
            //Calculate next point in theta range
            vec temp(abs(thetaMat.col(i-1)-q(j-1)));
            uword I;
            //q.print();
            temp.min(I); //Index gets filled in by reference
            lineScanGrid(j-1, ((2*i)-1)-1)=lineScan_act1(I,i-1);
            lineScanGrid(j-1, ((2*i)-1))=lineScan_act2(I,i-1);
        }

    }
    return 0;
}
