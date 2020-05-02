#ifndef GAMGR_H
#define GAMGR_H

#include "MovingMgr.h"
#include <iostream>

class GAMgr
{
public:
    GAMgr(MovingMgr* m, int p, int n): mgr(m), population(p), balls_number(n){
        order = new int*[p];
        for (int i = 0; i < population; ++i) {
            order[i] = new int[balls_number];
        }
        best_order = new int[balls_number];
        cost = new double[p];
    };
    virtual ~GAMgr(){
        for (int i = 0; i < population; ++i) {
            delete [] order[i];
        }
        delete [] order;
        delete [] best_order;
        delete [] cost;
    };
    void random_initiailize();
    void selection();
    void mutation();
    void rtr(int **);
    int node_distance(int*, int*);
    int** node();
    double moving(int*);
    void update_cost();
    // node crossover
    void crossover();
    void start();
private:
	MovingMgr* mgr;
    int population;
    int balls_number;
    int** order;
    double best_cost=99999999;
    int* best_order;
    double* cost;
    double cur_cost;
};

#endif /* GAMGR_H */
