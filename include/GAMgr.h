#ifndef GAMGR_H
#define GAMGR_H

#include "MovingMgr.h"

class GAMgr
{
public:
    GAMgr(MovingMgr* m, int p, int n): mgr(m), population(p), balls_number(n){
        int** order = new int*[p];
        for (int i = 0; i < population; ++i) {
            order[i] = new int[balls_number];
        }
    };
    virtual ~GAMgr(){
        for (int i = 0; i < population; ++i) {
            delete [] order[i];
        }
        delete [] order;
    };
    void random_initiailize();
    void selection();
    // node crossover
    void crossover();
    void start();
private:
	MovingMgr* mgr;
    int population;
    int balls_number;
    int** order;
};

#endif /* GAMGR_H */
