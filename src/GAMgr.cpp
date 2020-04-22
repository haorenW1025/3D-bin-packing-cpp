#include "GAMgr.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <random>
#include <algorithm> 
#include <chrono>

void GAMgr::random_initiailize(){
	std::array<int,balls_number> foo {0};
	for(int i=0;i<balls_number;i++) {
		foo[i]=i;
	}
	for(int i=0;i<population;i++) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
		for(int j=0;j<balls_number;j++) {
			order[i][j] = foo[j];
		}
	}
}

void GAMgr::selection(){
	int temp[population][balls_number];
	double cost[population];
	for(int i=0;i<population;i++) {
		mgr->reorder(order[i]);
		mgr->reset();
		mgr->moving_algorithm();
		cost[i]=mgr->get_cost();
		mgr->reorder_back(order[i]);
	}
	for(int i=0;i<population;i++) {//best result
		if(cost[i]<best_cost) {
			best_cost=cost[i];
			for(int j=0;j<balls_number;j++) {
				best_order[j]=order[i][j];
			}
		}
	}
	for(int i=0;i<population/2;i++) {
		if(cost[2*i] > cost[2*i+1]) {
			for(int j=0;j<balls_number;j++) {
				temp[i][j]=order[2*i][j];
			}
		} else {
			for(int j=0;j<balls_number;j++) {
				temp[i][j]=order[2*i+1][j];
			}
		}
	}
	
	std::array<int,population> foo {0};
	for(int i=0;i<population;i++) {
		foo[i]=i;
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
	for(int i=0;i<population/2;i++) {
		if(cost[foo[2*i]] > cost[foo[2*i+1]]) {
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

void GAMgr::crossover(){

}

void GAMgr::start(){

}
