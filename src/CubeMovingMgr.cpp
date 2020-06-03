#include <iostream>
#include <cmath>
#include "CubeMovingMgr.h"

using namespace std;

bool CubeMovingMgr::init_moving(int index, int cubes_count, int rot){
    cubes[index].set_x(box_dim-cubes[index].get_rx(rot)/2.0);
    cubes[index].set_y(box_dim-cubes[index].get_ry(rot)/2.0);
    cubes[index].set_z(box_dim-cubes[index].get_rz(rot)/2.0);
    for(int i = cubes_count; i < index; i++) {
        double length_x=cubes[i].get_rx(cubes[i].rotation)/2.0+cubes[index].get_rx(rot)/2.0;
        double length_y=cubes[i].get_ry(cubes[i].rotation)/2.0+cubes[index].get_ry(rot)/2.0;
        double length_z=cubes[i].get_rz(cubes[i].rotation)/2.0+cubes[index].get_rz(rot)/2.0;
        
        double distance_x=abs(cubes[index].get_x()-cubes[i].get_x());
        double distance_y=abs(cubes[index].get_y()-cubes[i].get_y());
        double distance_z=abs(cubes[index].get_z()-cubes[i].get_z());
        if (distance_x+eps < length_x && distance_y+eps < length_y && distance_z+eps < length_z) {
            return false;
        }
    }
    return true;
}

void CubeMovingMgr::moving(int index, int cubes_count, int axis, int rot) {
    switch(axis) {
        case 0: {
                double cur_x=cubes[index].get_x();
                double max_x=cubes[index].get_rx(rot)/2.0;
                cubes[index].set_x(max_x);
                for(int i=cubes_count;i<index;i++) {
                	double length_y=cubes[i].get_ry(cubes[i].rotation)/2.0+cubes[index].get_ry(rot)/2.0;
        			double length_z=cubes[i].get_rz(cubes[i].rotation)/2.0+cubes[index].get_rz(rot)/2.0;

                    double distance_y=abs(cubes[index].get_y()-cubes[i].get_y());
                    double distance_z=abs(cubes[index].get_z()-cubes[i].get_z());
                    if (distance_y+eps < length_y && distance_z+eps < length_z) {
                        double x=cubes[i].get_x()+cubes[i].get_rx(cubes[i].rotation)/2.0+cubes[index].get_rx(rot)/2.0;
                        if (x>max_x && x<=cur_x+eps) {
                            cubes[index].set_x(x);
                            max_x=x;
                        }
                    }
                }
            }
            break;
        case 1: {
        		double cur_y=cubes[index].get_y();
                double max_y=cubes[index].get_ry(rot)/2.0;
                cubes[index].set_y(max_y);
                for(int i=cubes_count;i<index;i++) {
                	double length_x=cubes[i].get_rx(cubes[i].rotation)/2.0+cubes[index].get_rx(rot)/2.0;
        			double length_z=cubes[i].get_rz(cubes[i].rotation)/2.0+cubes[index].get_rz(rot)/2.0;

                    double distance_x=abs(cubes[index].get_x()-cubes[i].get_x());
                    double distance_z=abs(cubes[index].get_z()-cubes[i].get_z());
                    if (distance_x+eps < length_x && distance_z+eps < length_z) {
                        double y=cubes[i].get_y()+cubes[i].get_ry(cubes[i].rotation)/2.0+cubes[index].get_ry(rot)/2.0;
                        if (y>max_y && y<=cur_y+eps) {
                            cubes[index].set_y(y);
                            max_y=y;
                        }
                    }
                }
            }
            break;
        case 2: {
        		double cur_z=cubes[index].get_z();
                double max_z=cubes[index].get_rz(rot)/2.0;
                cubes[index].set_z(max_z);
                for(int i=cubes_count;i<index;i++) {
                	double length_x=cubes[i].get_rx(cubes[i].rotation)/2.0+cubes[index].get_rx(rot)/2.0;
        			double length_y=cubes[i].get_ry(cubes[i].rotation)/2.0+cubes[index].get_ry(rot)/2.0;

                    double distance_x=abs(cubes[index].get_x()-cubes[i].get_x());
                    double distance_y=abs(cubes[index].get_y()-cubes[i].get_y());
                    if (distance_x+eps < length_x && distance_y+eps < length_y) {
                        double z=cubes[i].get_z()+cubes[i].get_rz(cubes[i].rotation)/2.0+cubes[index].get_rz(rot)/2.0;
                        if (z>max_z && z<=cur_z+eps) {
                            cubes[index].set_z(z);
                            max_z=z;
                        }
                    }
                }
            }
            break;
    }
}

double CubeMovingMgr::calculate_volume(int index){
	double max_x=0;
	double max_y=0;
	double max_z=0;
	for(int i=cubes_count;i<index+1;i++) {
		if (cubes[i].get_x()+cubes[i].get_rx(cubes[i].rotation)/2.0>max_x) {
			max_x=cubes[i].get_x()+cubes[i].get_rx(cubes[i].rotation)/2.0;
		}
		if (cubes[i].get_y()+cubes[i].get_ry(cubes[i].rotation)/2.0>max_y) {
			max_y=cubes[i].get_y()+cubes[i].get_ry(cubes[i].rotation)/2.0;
		}
		if (cubes[i].get_z()+cubes[i].get_rz(cubes[i].rotation)/2.0>max_z) {
			max_z=cubes[i].get_z()+cubes[i].get_rz(cubes[i].rotation)/2.0;
		}
	}
	return max_x*max_y*max_z;
}

/* Main Moving function */
void CubeMovingMgr::moving_algorithm(){
    int count = 0;
    while (count < get_number()) {
    	double minimum_volume=pow(box_dim, 3);
    	double best_x=cubes[count].get_x();
        double best_y=cubes[count].get_y();
        double best_z=cubes[count].get_z();
        int best_rot=0;
        bool enough_space=false;
    	for (int i=0;i<6;i++) {//rotation
    		if (init_moving(count, cubes_count, i)) {
    			cubes[count].rotation=i;
    			enough_space=true;
	            double init_x=cubes[count].get_x();
	            double init_y=cubes[count].get_y();
	            double init_z=cubes[count].get_z();
	            double pre_x=0.0;
	            double pre_y=0.0;
	            double pre_z=0.0;
	            double cur_x=init_x;
	            double cur_y=init_y;
	            double cur_z=init_z;
	        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in zyx directions until position remain unchanged
	                pre_x=cubes[count].get_x();
	                pre_y=cubes[count].get_y();
	                pre_z=cubes[count].get_z();
	                moving(count, cubes_count, 2, i);//zyx
	                moving(count, cubes_count, 1, i);//zyx
	                moving(count, cubes_count, 0, i);//zyx
	                cur_x=cubes[count].get_x();
	                cur_y=cubes[count].get_y();
	                cur_z=cubes[count].get_z();
	        	}
	        	if (calculate_volume(count) < minimum_volume+eps) {
	        		best_x=cubes[count].get_x();
	            	best_y=cubes[count].get_y();
	            	best_z=cubes[count].get_z();
	            	best_rot=i;
	            	minimum_volume=calculate_volume(count);
				}
	        	pre_x=0.0;
	            pre_y=0.0;
	            pre_z=0.0;
	            cubes[count].set_x(init_x);
	            cubes[count].set_y(init_y);
	            cubes[count].set_z(init_z);
	            cur_x=init_x;
	            cur_y=init_y;
	            cur_z=init_z;
	        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in zxy directions until position remain unchanged
	                pre_x=cubes[count].get_x();
	                pre_y=cubes[count].get_y();
	                pre_z=cubes[count].get_z();
	                moving(count, cubes_count, 2, i);//zxy
	                moving(count, cubes_count, 0, i);//zxy
	                moving(count, cubes_count, 1, i);//zxy
	                cur_x=cubes[count].get_x();
	                cur_y=cubes[count].get_y();
	                cur_z=cubes[count].get_z();
	        	}
	        	if (calculate_volume(count) < minimum_volume+eps) {
	        		best_x=cubes[count].get_x();
	            	best_y=cubes[count].get_y();
	            	best_z=cubes[count].get_z();
	            	best_rot=i;
	            	minimum_volume=calculate_volume(count);
				}
	        	pre_x=0.0;
	            pre_y=0.0;
	            pre_z=0.0;
	            cubes[count].set_x(init_x);
	            cubes[count].set_y(init_y);
	            cubes[count].set_z(init_z);
	            cur_x=init_x;
	            cur_y=init_y;
	            cur_z=init_z;
	        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in yzx directions until position remain unchanged
	                pre_x=cubes[count].get_x();
	                pre_y=cubes[count].get_y();
	                pre_z=cubes[count].get_z();
	                moving(count, cubes_count, 1, i);//yzx
	                moving(count, cubes_count, 2, i);//yzx
	                moving(count, cubes_count, 0, i);//yzx
	                cur_x=cubes[count].get_x();
	                cur_y=cubes[count].get_y();
	                cur_z=cubes[count].get_z();
	        	}
	        	if (calculate_volume(count) < minimum_volume+eps) {
	        		best_x=cubes[count].get_x();
	            	best_y=cubes[count].get_y();
	            	best_z=cubes[count].get_z();
	            	best_rot=i;
	            	minimum_volume=calculate_volume(count);
				}
	        	pre_x=0.0;
	            pre_y=0.0;
	            pre_z=0.0;
	            cubes[count].set_x(init_x);
	            cubes[count].set_y(init_y);
	            cubes[count].set_z(init_z);
	            cur_x=init_x;
	            cur_y=init_y;
	            cur_z=init_z;
	        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in yxz directions until position remain unchanged
	                pre_x=cubes[count].get_x();
	                pre_y=cubes[count].get_y();
	                pre_z=cubes[count].get_z();
	                moving(count, cubes_count, 1, i);//yxz
	                moving(count, cubes_count, 0, i);//yxz
	                moving(count, cubes_count, 2, i);//yxz
	                cur_x=cubes[count].get_x();
	                cur_y=cubes[count].get_y();
	                cur_z=cubes[count].get_z();
	        	}
	        	if (calculate_volume(count) < minimum_volume+eps) {
	        		best_x=cubes[count].get_x();
	            	best_y=cubes[count].get_y();
	            	best_z=cubes[count].get_z();
	            	best_rot=i;
	            	minimum_volume=calculate_volume(count);
				}
	        	pre_x=0.0;
	            pre_y=0.0;
	            pre_z=0.0;
	            cubes[count].set_x(init_x);
	            cubes[count].set_y(init_y);
	            cubes[count].set_z(init_z);
	            cur_x=init_x;
	            cur_y=init_y;
	            cur_z=init_z;
	        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in xzy directions until position remain unchanged
	                pre_x=cubes[count].get_x();
	                pre_y=cubes[count].get_y();
	                pre_z=cubes[count].get_z();
	                moving(count, cubes_count, 0, i);//xzy
	                moving(count, cubes_count, 2, i);//xzy
	                moving(count, cubes_count, 1, i);//xzy
	                cur_x=cubes[count].get_x();
	                cur_y=cubes[count].get_y();
	                cur_z=cubes[count].get_z();
	        	}
	        	if (calculate_volume(count) < minimum_volume+eps) {
	        		best_x=cubes[count].get_x();
	            	best_y=cubes[count].get_y();
	            	best_z=cubes[count].get_z();
	            	best_rot=i;
	            	minimum_volume=calculate_volume(count);
				}
	        	pre_x=0.0;
	            pre_y=0.0;
	            pre_z=0.0;
	            cubes[count].set_x(init_x);
	            cubes[count].set_y(init_y);
	            cubes[count].set_z(init_z);
	            cur_x=init_x;
	            cur_y=init_y;
	            cur_z=init_z;
	        	while (abs(pre_x-cur_x)>eps && abs(pre_y-cur_y)>eps && abs(pre_z-cur_z)>eps) {//move in xyz directions until position remain unchanged
	                pre_x=cubes[count].get_x();
	                pre_y=cubes[count].get_y();
	                pre_z=cubes[count].get_z();
	                moving(count, cubes_count, 0, i);//xyz
	                moving(count, cubes_count, 1, i);//xyz
	                moving(count, cubes_count, 2, i);//xyz
	                cur_x=cubes[count].get_x();
	                cur_y=cubes[count].get_y();
	                cur_z=cubes[count].get_z();
	        	}
	        	if (calculate_volume(count) < minimum_volume+eps) {
	        		best_x=cubes[count].get_x();
	            	best_y=cubes[count].get_y();
	            	best_z=cubes[count].get_z();
	            	best_rot=i;
	            	minimum_volume=calculate_volume(count);
				}
	        }
		}
		if (enough_space==true) {
			cubes[count].set_x(best_x);//best
			cubes[count].set_y(best_y);//best
			cubes[count].set_z(best_z);//best
			cubes[count].rotation = best_rot;
            indexToBox.push_back(box_count);
            count++;
		} else {
            box_count++;
            cubes_count=count;//if the box is full then the previous cubes should not take into concern in the next box
        }
    }
}

double CubeMovingMgr::get_cost() {
    return box_count-1 + (calculate_volume(get_number()-1) / pow(box_dim, 3));
}

void CubeMovingMgr::reset() {
    box_count = 1;
    cubes_count = 0;
    indexToBox.clear();
}

void CubeMovingMgr::swap(int first_index, int second_index) {
    Cube temp = Cube(cubes[first_index].get_rx(0), cubes[first_index].get_ry(0), cubes[first_index].get_rz(0));
    cubes[first_index] = cubes[second_index];
    cubes[second_index] = temp;
}

void CubeMovingMgr::reorder(int* order) {
	Cube temp[get_number()];
	for(int i=0;i<get_number();i++) {
		temp[i] = Cube(cubes[i].get_rx(0), cubes[i].get_ry(0), cubes[i].get_rz(0));
	}
	for(int i=0;i<get_number();i++) {
		cubes[i] = temp[order[i]]; 	
	}
}

void CubeMovingMgr::reorder_back(int* order) {
	Cube temp[get_number()];
	for(int i=0;i<get_number();i++) {
		temp[i] = Cube(cubes[i].get_rx(0), cubes[i].get_ry(0), cubes[i].get_rz(0));
	}
	for(int i=0;i<get_number();i++) {
		cubes[order[i]] = temp[i]; 	
	}
}

void CubeMovingMgr::write_result(fstream& output) {
    output << box_dim << endl;
    output << box_count << endl;
    for (int i = 0; i < get_number(); ++i) {
        output << indexToBox[i] << " " << cubes[i].get_rx(cubes[i].rotation) << " " << cubes[i].get_ry(cubes[i].rotation)
		<< " " << cubes[i].get_rz(cubes[i].rotation) << " " << cubes[i].get_x() << " " << cubes[i].get_y() << " " << cubes[i].get_z() << endl;
    }
    output.close();
}

void CubeMovingMgr::print_result() {
    cout << "==========================RESULT==========================" << endl;
    cout << "Number of Boxes: " << box_count << endl;
    int index = 0;
    for (int i = 0; i < box_count; i++) {
        cout << "Box number " << i+1 << ": " << endl;
        while (indexToBox[index] == i+1) {
            cout << "  Cube " << index << ": length = (" << cubes[index].get_rx(cubes[index].rotation) << ", " << cubes[index].get_ry(cubes[index].rotation)
		<< ", " << cubes[index].get_rz(cubes[index].rotation) << ")" << " Position = (" 
                << cubes[index].get_x() << ", " << cubes[index].get_y() << ", " << cubes[index].get_z() << ")" << endl;
            index++;
        }
    }
    cout << "==========================================================" << endl;
}
