#include <random>
#include "GAMgr.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <random>
#include <algorithm> 
#include <vector>
#include <chrono>
#include <random>

void GAMgr::random_initiailize(){
	std::vector<int> foo;
	for(int i=0;i<balls_number;i++) {
        foo.push_back(i);
	}
	for(int i=0;i<population;i++) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
		for(int j=0;j<balls_number;j++) {
			order[i][j] = foo[j];
		}
	}
	for(int i=0;i<population;i++) {
        cost[i] = moving(order[i]);
	}
}

void GAMgr::mutation() {
    int first_index;
    int second_index;
    for(int i=0;i<population;i++) {
    	first_index = rand() % (mgr->get_number());
        second_index = rand() % (mgr->get_number());
        /* avoid selecting same index */
        do {
            second_index = rand() % (mgr->get_number());
        } while (first_index == second_index);
        
        int temp = order[i][first_index];
        order[i][first_index] = order[i][second_index];
        order[i][second_index] = temp;
        double mut_cost = moving(order[i]);
        if (mut_cost < cost[i]) {
        	cost[i] = mut_cost;
		} else {//swap back
			temp = order[i][first_index];
        	order[i][first_index] = order[i][second_index];
        	order[i][second_index] = temp;
		}
	}
}

double GAMgr::moving(int* order) {
    mgr->reorder(order);
    mgr->reset();
    mgr->moving_algorithm();
    double _cost = mgr->get_cost();
    mgr->reorder_back(order);
    return _cost;
}

void GAMgr::update_cost() {
	for(int i=0;i<population;i++) {
		mgr->reorder(order[i]);
    	mgr->reset();
    	mgr->moving_algorithm();
    	cost[i] = mgr->get_cost();
    	mgr->reorder_back(order[i]);
	}
}
void GAMgr::selection(){
	int temp[population][balls_number];
	cur_cost=999999;
	for(int i=0;i<population;i++) {//best result
		if(cost[i]<best_cost) {
			best_cost=cost[i];
			for(int j=0;j<balls_number;j++) {
				best_order[j]=order[i][j];
			}
		}
		if(cost[i]<cur_cost) {
			cur_cost=cost[i];
		}
	}
	for(int i=0;i<population/2;i++) {
		if(cost[2*i] < cost[2*i+1]) {
			for(int j=0;j<balls_number;j++) {
				temp[i][j]=order[2*i][j];
			}
		} else {
			for(int j=0;j<balls_number;j++) {
				temp[i][j]=order[2*i+1][j];
			}
		}
	}
	
	std::vector<int> foo;
	for(int i=0;i<population;i++) {
		foo.push_back(i);
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
	for(int i=0;i<population/2;i++) {
		if(cost[foo[2*i]] < cost[foo[2*i+1]]) {
			for(int j=0;j<balls_number;j++) {
				temp[i+population/2][j]=order[foo[2*i]][j];
			}
		} else {
			for(int j=0;j<balls_number;j++) {
				temp[i+population/2][j]=order[foo[2*i+1]][j];
			}
		}
	}
	
	for(int i=0;i<population;i++) {
		for(int j=0;j<balls_number;j++) {
			order[i][j]=temp[i][j];
		}
	}
}

void normalization() {
}

void GAMgr::crossover(){
    double possibility[balls_number][balls_number];
    // initialize
    for (int i = 0; i < balls_number; ++i) {
        for (int j = 0; j < balls_number; ++j) {
            possibility[i][j] = 0;
        }
    }
    // accumulate
    for (int i = 0; i < population; ++i) {
        for (int j = 0; j < balls_number; ++j) {
            possibility[j][order[i][j]]++;
        }
    }
    // normalize
    for (int i = 0; i < balls_number; ++i) {
        for (int j = 0; j < balls_number; ++j) {
            possibility[i][j] /= population;
        }
    }
//    for (int i = 0; i < balls_number; ++i) {
//        for (int j = 0; j < balls_number; ++j) {
//             std::cout << possibility[i][j];
//        }
//        std::cout << std::endl;
//    }
    // generate
    bool selected[balls_number];
    double temp[balls_number][balls_number];
    for (int i = 0; i < population; ++i) {
        for (int l = 0; l < balls_number; ++l){
            selected[l] = false;
        }
        for (int l = 0; l < balls_number; ++l){
            for(int m=0;m<balls_number;++m){
            	temp[l][m]=possibility[l][m];
			}
        }
        for (int j = 0; j < balls_number; ++j) {
//            if (j == balls_number-1) {
//                for (int k = 0; k < balls_number; ++k) {
//                    if (!selected[k]) order[i][j] = k;
//                    break;
//                }
//                continue;
//            }
            std::random_device rd;
            std::default_random_engine gen = std::default_random_engine(rd());
            std::uniform_real_distribution<double> dis(0,1);
            double random = dis(gen);
            double possible = 0;
            for (int k = 0; k < balls_number; ++k) {
                if (!selected[k]) continue;
                possible += temp[j][k];
                if (possible > random-1e-6) {
                    double normalize = 0;
                    selected[k] = true;
                    order[i][j] = k;

                    // normalize
                    for (int l = 0; l < balls_number; ++l){
                        if (selected[l] == false)
                            normalize += temp[j+1][l];
                    }
                    for (int l = 0; l < balls_number; ++l) {
                        if (selected[l] == false)
                            temp[j+1][l] /= normalize;
                    }
//                    for (int l = 0; l < balls_number; ++l) {
//                    	if (selected[l] == false)
//                        std::cout << temp[j][l] << std::endl;
//                    }
//                    break;
                }
            }
        }
    }
//    std::cout << "population" << std::endl;
//    for (int i = 0; i < population; ++i) {
//        for (int j = 0; j < balls_number; ++j) {
//             std::cout << order[i][j];
//        }
//        std::cout << std::endl;
//    }
}

void GAMgr::start(){
    random_initiailize();
    for (int i = 0; i < 10; ++i) {
        selection();
        crossover();
        update_cost();
        mutation();
        std::cout << i << ": " << best_cost << " " << cur_cost << std::endl;
        
    }
	mgr->reorder(best_order);
    mgr->reset();
    mgr->moving_algorithm();
    mgr->print_result();
}
