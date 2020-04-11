#include <iostream>
#include <cmath>
#include "mgr.h"

using namespace std;

bool Mgr::init_moving(int index, int balls_count){
    balls[index].set_x(box_dim-balls[index].get_r());
    balls[index].set_y(box_dim-balls[index].get_r());
    balls[index].set_z(box_dim-balls[index].get_r());
    for(int i = balls_count; i < index; i++) {
        float distance=balls[i].get_r()+balls[index].get_r();
        float distance_x=balls[index].get_x()-balls[i].get_x();
        float distance_y=balls[index].get_y()-balls[i].get_y();
        float distance_z=balls[index].get_z()-balls[i].get_z();
        if (pow(distance_x, 2)+pow(distance_y, 2)+pow(distance_z, 2)<pow(distance, 2)) {
            return false;
        }	
    }
    return true;
}

void Mgr::moving(int index, int balls_count, int axis) {
    switch(axis) {
        case 0: {
        		float cur_x=balls[index].get_x();
                float max_x=balls[index].get_r();
                balls[index].set_x(max_x);
                for(int i=balls_count;i<index;i++) {
                    float distance=balls[i].get_r()+balls[index].get_r();
                    float distance_y=balls[index].get_y()-balls[i].get_y();
                    float distance_z=balls[index].get_z()-balls[i].get_z();
                    float a=1.0;
                    float b=-2.0*balls[i].get_x();
                    float c=pow(balls[i].get_x(), 2)+pow(distance_y, 2)+pow(distance_z, 2)-pow(distance, 2);
                    if (pow(b, 2)-4*a*c>=0) {
                        float x= (-b+sqrt(pow(b, 2)-4*a*c))/(2*a);
                        if (x>max_x && x<=cur_x) {
                            balls[index].set_x(x);
                            max_x=x;
                        }
                    }
                }
            }
            break;
        case 1: {
        		float cur_y=balls[index].get_y();
                float max_y=balls[index].get_r();
                balls[index].set_y(max_y);
                for(int i=balls_count;i<index;i++) {
                    float distance=balls[i].get_r()+balls[index].get_r();
                    float distance_x=balls[index].get_x()-balls[i].get_x();
                    float distance_z=balls[index].get_z()-balls[i].get_z();
                    float a=1.0;
                    float b=-2.0*balls[i].get_y();
                    float c=pow(balls[i].get_y(), 2)+pow(distance_x, 2)+pow(distance_z, 2)-pow(distance, 2);
                    if (pow(b, 2)-4*a*c>=0) {
                        float y= (-b+sqrt(pow(b, 2)-4*a*c))/(2*a);
                        if (y>max_y && y<=cur_y) {
                            balls[index].set_y(y);
                            max_y=y;
                        }
                    }
                }
            }
            break;
        case 2: {
        		float cur_z=balls[index].get_z();
                float max_z=balls[index].get_r();
                balls[index].set_z(max_z);
                for(int i=balls_count;i<index;i++) {
                    float distance=balls[i].get_r()+balls[index].get_r();
                    float distance_x=balls[index].get_x()-balls[i].get_x();
                    float distance_y=balls[index].get_y()-balls[i].get_y();
                    float a=1.0;
                    float b=-2.0*balls[i].get_z();
                    float c=pow(balls[i].get_z(), 2)+pow(distance_x, 2)+pow(distance_y, 2)-pow(distance, 2);
                    if (pow(b, 2)-4*a*c>=0) {
                        float z= (-b+sqrt(pow(b, 2)-4*a*c))/(2*a);
                        if (z>max_z && z<=cur_z) {
                            balls[index].set_z(z);
                            max_z=z;
                        }
                    }
                }
            }
            break;
    }
}

float Mgr::calculate_volume(int index){
	float max_x=0;
	float max_y=0;
	float max_z=0;
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
void Mgr::moving_algorithm(){
    int count = 0;
    while (count < get_number()) {
        cout << count << endl;
        if (init_moving(count, balls_count)) {
        	float minimum_volume=pow(box_dim, 3);
        	float best_x=balls[count].get_x();
            float best_y=balls[count].get_y();
            float best_z=balls[count].get_z();
            float init_x=balls[count].get_x();
            float init_y=balls[count].get_y();
            float init_z=balls[count].get_z();
            float pre_x=0.0;
            float pre_y=0.0;
            float pre_z=0.0;
            float cur_x=balls[count].get_x();
            float cur_y=balls[count].get_y();
            float cur_z=balls[count].get_z();
        	while (pre_x!=cur_x && pre_y!=cur_y && pre_z!=cur_z) {//move in xyz directions until position remain unchanged
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
        	if (calculate_volume(count) < minimum_volume) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (pre_x!=cur_x && pre_y!=cur_y && pre_z!=cur_z) {//move in xzy directions until position remain unchanged
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
        	if (calculate_volume(count) < minimum_volume) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (pre_x!=cur_x && pre_y!=cur_y && pre_z!=cur_z) {//move in yxz directions until position remain unchanged
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
        	if (calculate_volume(count) < minimum_volume) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (pre_x!=cur_x && pre_y!=cur_y && pre_z!=cur_z) {//move in yzx directions until position remain unchanged
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
        	if (calculate_volume(count) < minimum_volume) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (pre_x!=cur_x && pre_y!=cur_y && pre_z!=cur_z) {//move in zxy directions until position remain unchanged
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
        	if (calculate_volume(count) < minimum_volume) {
        		best_x=balls[count].get_x();
            	best_y=balls[count].get_y();
            	best_z=balls[count].get_z();
            	minimum_volume=calculate_volume(count);
			}
        	pre_x=0.0;
            pre_y=0.0;
            pre_z=0.0;
            cur_x=init_x;
            cur_y=init_y;
            cur_z=init_z;
        	while (pre_x!=cur_x && pre_y!=cur_y && pre_z!=cur_z) {//move in zyx directions until position remain unchanged
                pre_x=balls[count].get_x();
                pre_y=balls[count].get_y();
                pre_z=balls[count].get_z();
                moving(count, balls_count, 2);//zyx
                moving(count, balls_count, 0);//zyx
                moving(count, balls_count, 1);//zyx
                cur_x=balls[count].get_x();
                cur_y=balls[count].get_y();
                cur_z=balls[count].get_z();
        	}
        	if (calculate_volume(count) < minimum_volume) {
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
            cout << "box" << box_count << ": " << endl;//print if box is full
            for(int i=balls_count;i<count;i++) {
                cout << "(" << balls[i].get_x() << ", " << balls[i].get_y() << ", " << balls[i].get_z() << ") " << balls[i].get_r() << endl;	
            }
            box_count++;
            balls_count=count;//if the box is full then the previous balls should not take into concern in the next box
        }
    }
}

void Mgr::write_result(fstream& output) {
    output << box_dim << endl;
    output << box_count << endl;
    for (int i = 0; i < get_number(); ++i) {
        output << indexToBox[i] << " " << balls[i].get_r() << " " << balls[i].get_x() << " "
            << balls[i].get_y() <<
            " " << balls[i].get_z() << endl;
    }
    output.close();
}

void Mgr::print_result() {
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
