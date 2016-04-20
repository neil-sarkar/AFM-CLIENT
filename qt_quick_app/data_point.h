#ifndef DATA_POINT_H
#define DATA_POINT_H

class DataPoint {
public:
    double x;
    double y;
    double z;
    bool drawn;

    DataPoint(double x_, double y_, double z_) {
        x = x_;
        y = y_;
        z = z_;
        drawn = false;
    }

    DataPoint() {
    }
};


#endif // DATA_POINT_H
