#ifndef CUBE_H
#define CUBE_H

#include <vector>

class Cube
{
public:
    Cube(): x_length(0), y_length(0), z_length(0){}
    Cube(double a, double b, double c): x_length(a), y_length(b), z_length(c), rotation(0){};
    ~Cube(){};
    double get_x() {return x; }
    double get_y() {return y; }
    double get_z() {return z; }
    std::vector<double> get_r(int i) {
        std::vector<double> r;
        r.resize(3);
        switch (i) {
            case 0:
                r[0] = x_length;
                r[1] = y_length;
                r[2] = z_length;
                break;
            case 1:
                r[0] = x_length;
                r[1] = z_length;
                r[2] = y_length;
            case 2:
                r[0] = y_length;
                r[1] = x_length;
                r[2] = z_length;
            case 3:
                r[0] = y_length;
                r[1] = z_length;
                r[2] = x_length;
            case 4:
                r[0] = z_length;
                r[1] = x_length;
                r[2] = y_length;
            case 5:
                r[0] = z_length;
                r[1] = y_length;
                r[2] = x_length;
            default:
                r[0] = x_length;
                r[1] = y_length;
                r[2] = z_length;
        }
        return r;
    }
    void set_x(double a) {x=a;}
    void set_y(double b) {y=b;}
    void set_z(double c) {z=c;}
    
    int rotation;

private:
    double x_length;
    double y_length;
    double z_length;
    double x;
    double y;
    double z;
};

#endif /* CUBE_H */
