#ifndef CUBE_H
#define CUBE_H

#include <vector>

class Cube
{
public:
    Cube(): x_length(0), y_length(0), z_length(0){}
    Cube(double a, double b, double c): x_length(a), y_length(b), z_length(c), rotation(0){};
    Cube(double a, double b, double c, double rx, double ry, double rz): x_length(a), y_length(b), z_length(c), rotation(0),
	x(rx), y(ry), z(rz){};
    ~Cube(){};
    double get_x() {return x; }
    double get_y() {return y; }
    double get_z() {return z; }
    double get_rx(int i) {
    	double rx;
    	switch(i) {
    		case 0:
    			rx = x_length;
    			break;
    		case 1:
    			rx = x_length;
    			break;
    		case 2:
    			rx = y_length;
    			break;
    		case 3:
    			rx = y_length;
    			break;
    		case 4:
    			rx = z_length;
    			break;
    		case 5:
    			rx = z_length;
    			break;
		}
		return rx;
	}
	double get_ry(int i) {
    	double ry;
    	switch(i) {
    		case 0:
    			ry = y_length;
    			break;
    		case 1:
    			ry = z_length;
    			break;
    		case 2:
    			ry = x_length;
    			break;
    		case 3:
    			ry = z_length;
    			break;
    		case 4:
    			ry = x_length;
    			break;
    		case 5:
    			ry = y_length;
    			break;
		}
		return ry;
	}
	double get_rz(int i) {
    	double rz;
    	switch(i) {
    		case 0:
    			rz = z_length;
    			break;
    		case 1:
    			rz = y_length;
    			break;
    		case 2:
    			rz = z_length;
    			break;
    		case 3:
    			rz = x_length;
    			break;
    		case 4:
    			rz = y_length;
    			break;
    		case 5:
    			rz = x_length;
    			break;
		}
		return rz;
	}
//    std::vector<double> get_r(int i) {
//        std::vector<double> r;
//        r.resize(3);
//        switch (i) {
//            case 0:
//                r[0] = x_length;
//                r[1] = y_length;
//                r[2] = z_length;
//                break;
//            case 1:
//                r[0] = x_length;
//                r[1] = z_length;
//                r[2] = y_length;
//                break;
//            case 2:
//                r[0] = y_length;
//                r[1] = x_length;
//                r[2] = z_length;
//                break;
//            case 3:
//                r[0] = y_length;
//                r[1] = z_length;
//                r[2] = x_length;
//                break;
//            case 4:
//                r[0] = z_length;
//                r[1] = x_length;
//                r[2] = y_length;
//                break;
//            case 5:
//                r[0] = z_length;
//                r[1] = y_length;
//                r[2] = x_length;
//                break;
//            default:
//                r[0] = x_length;
//                r[1] = y_length;
//                r[2] = z_length;
//        }
//        return r;
//    }
    void set_x(double a) {x=a;}
    void set_y(double b) {y=b;}
    void set_z(double c) {z=c;}
    
    int rotation;

private:
    double x_length;
    double y_length;
    double z_length;
    double x=10000;
    double y=10000;
    double z=10000;
};

#endif /* CUBE_H */
