#ifndef GAMGR_H
#define GAMGR_H

#include "CubeMovingMgr.h"
#include <iostream>

class GAMgr
{
public:
    GAMgr(CubeMovingMgr* m, int p, int n): mgr(m), population(p), balls_number(n){
        temperature = 200;
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
    void rtr(int **, int*);
    int node_distance(int*, int*);
    int edge_distance(int*, int*);
    double** edge_probability();
    double** node_probability();
    int* edge(double**, double*);
    int* node(double**);
    double moving(int*);
    double get_avg_cost(int**);
    void update_cost();
    // node crossover
    void crossover(int);
    void start();
private:
	CubeMovingMgr* mgr;
    double temperature;
    int population;
    int balls_number;
    int** order;
    double best_cost=99999999;
    int* best_order;
    double* cost;
    double cur_cost;
    double total_node_cost=0;
    double total_edge_cost=0;
    int take_node=0;
    int take_edge=0;
    double node_p;
    double edge_p;
    
};

#endif /* GAMGR_H */
