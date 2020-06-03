#include <iostream>
#include <cmath>
#include "MovingMgr.h"

using namespace std;

bool MovingMgr::init_moving(int index, int balls_count){
    balls[index].set_x(box_dim-balls[index].get_r());
    balls[index].set_y(box_dim-balls[index].get_r());
    balls[index].set_z(box_dim-balls[index].get_r());
    for(int i = balls_count; i < index; i++) {
        double distance=balls[i].get_r()+balls[index].get_r();
        double distance_x=balls[index].get_x()-balls[i].get_x();
        double distance_y=balls[index].get_y()-balls[i].get_y();
        double distance_z=balls[index].get_z()-balls[i].get_z();
        if (pow(distance_x, 2)+pow(distance_y, 2)+pow(distance_z, 2)+eps<pow(distance, 2)) {
            return false;
        }
    }
    return true;
}


void MovingMgr::moving(int index, int balls_count, int axis) {
    switch(axis) {
        case 0: {
                double cur_x=balls[index].get_x();
                double max_x=balls[index].get_r();
                balls[index].set_x(max_x);
                for(int i=balls_count;i<index;i++) {
                    double distance=balls[i].get_r()+balls[index].get_r();
                    double distance_y=balls[index].get_y()-balls[i].get_y();
                    double distance_z=balls[index].get_z()-balls[i].get_z();
                    double a=1.0;
                    double b=-2.0*balls[i].get_x();
                    double c=pow(balls[i].get_x(), 2)+pow(distance_y, 2)+pow(distance_z, 2)-pow(distance, 2);
                    if (pow(b, 2)-4*a*c>0) {
                        double x= (-b+sqrt(pow(b, 2)-4*a*c))/(2*a);
                        if (x>max_x && x<=cur_x+eps) {
                            balls[index].set_x(x);
                            max_x=x;
                        }
                    }
                }
            }
            break;
        case 1: {
        		double cur_y=balls[index].get_y();
                double max_y=balls[index].get_r();
                balls[index].set_y(max_y);
                for(int i=balls_count;i<index;i++) {
                    double distance=balls[i].get_r()+balls[index].get_r();
                    double distance_x=balls[index].get_x()-balls[i].get_x();
                    double distance_z=balls[index].get_z()-balls[i].get_z();
                    double a=1.0;
                    double b=-2.0*balls[i].get_y();
                    double c=pow(balls[i].get_y(), 2)+pow(distance_x, 2)+pow(distance_z, 2)-pow(distance, 2);
                    if (pow(b, 2)-4*a*c>0) {
                        double y= (-b+sqrt(pow(b, 2)-4*a*c))/(2*a);
                        if (y>max_y && y<=cur_y+eps) {
                            balls[index].set_y(y);
                            max_y=y;
                        }
                    }
                }
            }
            break;
        case 2: {
        		double cur_z=balls[index].get_z();
                double max_z=balls[index].get_r();
                balls[index].set_z(max_z);
                for(int i=balls_count;i<index;i++) {
                    double distance=balls[i].get_r()+balls[index].get_r();
                    double distance_x=balls[index].get_x()-balls[i].get_x();
                    double distance_y=balls[index].get_y()-balls[i].get_y();
                    double a=1.0;
                    double b=-2.0*balls[i].get_z();
                    double c=pow(balls[i].get_z(), 2)+pow(distance_x, 2)+pow(distance_y, 2)-pow(distance, 2);
                    if (pow(b, 2)-4*a*c>0) {
                        double z= (-b+sqrt(pow(b, 2)-4*a*c))/(2*a);
                        if (z>max_z && z<=cur_z+eps) {
                            balls[index].set_z(z);
                            max_z=z;
                        }
                    }
                }
            }
            break;
    }
}


double MovingMgr::calculate_volume(int index){
	double max_x=0;
	double max_y=0;
	double max_z=0;
	for(int i=balls_count;i<index+1;i++) {
		if (balls[i].get_x()+balls[i].get_r()>max_x) {
			max_x=balls[i].get_x()+balls[i].get_r();
		}
		if (balls[i].get_y()+balls[i].get_r()>max_y) {
			max_y=balls[i].get_y()+balls[i].get_r();
		}
		if (balls[i].get_z()+balls[i].get_r()>max_z) {
			max_z=balls[i].get_z()+balls[i].get_r();
		}
	}
	return max_x*max_y*max_z;
}

/* Main Moving function */
void MovingMgr::moving_algorithm(){
    int count = 0;
    while (count < get_number()) {
        if (init_moving(count, balls_count)) {
        	double minimum_volume=pow(box_dim, 3);
        	double best_x=balls[count].get_x();
            double best_y=balls[count].get_y();
            double best_z=balls[count].get_z();
            double init_x=balls[count].get_x();
            double init_y=balls[count].get_y();
            double init_z=balls[count].get_z();
            double pre_x=0.0;
            double pre_y=0.0;
            double pre_z=0.0;
            double cur_x=balls[count].get_x();
            double cur_y=balls[count].get_y();
            double cur_z=balls[count].get_z();
        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in zyx directions until position remain unchanged
                pre_x=balls[count].get_x();
                pre_y=balls[count].get_y();
                pre_z=balls[count].get_z();
                moving(count, balls_count, 2);//zyx
                moving(count, balls_count, 1);//zyx
                moving(count, balls_count, 0);//zyx
                cur_x=balls[count].get_x();
                cur_y=balls[count].get_y();
                cur_z=balls[count].get_z();
        	}
        	if (calculate_volume(count) < minimum_volume+eps) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            balls[count].set_x(init_x);
            balls[count].set_y(init_y);
            balls[count].set_z(init_z);
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in zxy directions until position remain unchanged
                pre_x=balls[count].get_x();
                pre_y=balls[count].get_y();
                pre_z=balls[count].get_z();
                moving(count, balls_count, 2);//zxy
                moving(count, balls_count, 0);//zxy
                moving(count, balls_count, 1);//zxy
                cur_x=balls[count].get_x();
                cur_y=balls[count].get_y();
                cur_z=balls[count].get_z();
        	}
        	if (calculate_volume(count) < minimum_volume+eps) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            balls[count].set_x(init_x);
            balls[count].set_y(init_y);
            balls[count].set_z(init_z);
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in yzx directions until position remain unchanged
                pre_x=balls[count].get_x();
                pre_y=balls[count].get_y();
                pre_z=balls[count].get_z();
                moving(count, balls_count, 1);//yzx
                moving(count, balls_count, 2);//yzx
                moving(count, balls_count, 0);//yzx
                cur_x=balls[count].get_x();
                cur_y=balls[count].get_y();
                cur_z=balls[count].get_z();
        	}
        	if (calculate_volume(count) < minimum_volume+eps) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            balls[count].set_x(init_x);
            balls[count].set_y(init_y);
            balls[count].set_z(init_z);
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in yxz directions until position remain unchanged
                pre_x=balls[count].get_x();
                pre_y=balls[count].get_y();
                pre_z=balls[count].get_z();
                moving(count, balls_count, 1);//yxz
                moving(count, balls_count, 0);//yxz
                moving(count, balls_count, 2);//yxz
                cur_x=balls[count].get_x();
                cur_y=balls[count].get_y();
                cur_z=balls[count].get_z();
        	}
        	if (calculate_volume(count) < minimum_volume+eps) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            balls[count].set_x(init_x);
            balls[count].set_y(init_y);
            balls[count].set_z(init_z);
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in xzy directions until position remain unchanged
                pre_x=balls[count].get_x();
                pre_y=balls[count].get_y();
                pre_z=balls[count].get_z();
                moving(count, balls_count, 0);//xzy
                moving(count, balls_count, 2);//xzy
                moving(count, balls_count, 1);//xzy
                cur_x=balls[count].get_x();
                cur_y=balls[count].get_y();
                cur_z=balls[count].get_z();
        	}
        	if (calculate_volume(count) < minimum_volume+eps) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            balls[count].set_x(init_x);
            balls[count].set_y(init_y);
            balls[count].set_z(init_z);
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in xyz directions until position remain unchanged
                pre_x=balls[count].get_x();
                pre_y=balls[count].get_y();
                pre_z=balls[count].get_z();
                moving(count, balls_count, 0);//xyz
                moving(count, balls_count, 1);//xyz
                moving(count, balls_count, 2);//xyz
                cur_x=balls[count].get_x();
                cur_y=balls[count].get_y();
                cur_z=balls[count].get_z();
        	}
        	if (calculate_volume(count) < minimum_volume+eps) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
			balls[count].set_x(best_x);//best
			balls[count].set_y(best_y);//best
			balls[count].set_z(best_z);//best
			
            indexToBox.push_back(box_count);
            count++;
        } else {
            box_count++;
            balls_count=count;//if the box is full then the previous balls should not take into concern in the next box
        }
    }
}

double MovingMgr::get_cost() {
    return box_count-1 + (calculate_volume(get_number()-1) / pow(box_dim, 3));
}

void MovingMgr::reset() {
    box_count = 1;
    balls_count = 0;
    indexToBox.clear();
}

void MovingMgr::swap(int first_index, int second_index) {
    Sphere temp = Sphere(balls[first_index].get_r());
    balls[first_index] = balls[second_index];
    balls[second_index] = temp;
}

void MovingMgr::reorder(int* order) {
	Sphere temp[get_number()];
	for(int i=0;i<get_number();i++) {
		temp[i] = Sphere(balls[i].get_r());
	}
	for(int i=0;i<get_number();i++) {
		balls[i] = temp[order[i]]; 	
	}
}

void MovingMgr::reorder_back(int* order) {
	Sphere temp[get_number()];
	for(int i=0;i<get_number();i++) {
		temp[i] = Sphere(balls[i].get_r());
	}
	for(int i=0;i<get_number();i++) {
		balls[order[i]] = temp[i]; 	
	}
}

void MovingMgr::write_result(fstream& output) {
    output << box_dim << endl;
    output << box_count << endl;
    for (int i = 0; i < get_number(); ++i) {
        output << indexToBox[i] << " " << balls[i].get_r() << " " << balls[i].get_x() << " "
            << balls[i].get_y() <<
            " " << balls[i].get_z() << endl;
    }
    output.close();
}

void MovingMgr::print_result() {
    cout << "==========================RESULT==========================" << endl;
    cout << "Number of Boxes: " << box_count << endl;
    int index = 0;
    for (int i = 0; i < box_count; i++) {
        cout << "Box number " << i+1 << ": " << endl;
        while (indexToBox[index] == i+1) {
            cout << "  Ball " << index << ": Radius = " << balls[index].get_r() << " Position = (" 
                << balls[index].get_x() << ", " << balls[index].get_y() << ", " << balls[index].get_z() << ")" << endl;
            index++;
        }
    }
    cout << "==========================================================" << endl;
}
