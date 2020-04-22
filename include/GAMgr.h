#ifndef GAMGR_H
#define GAMGR_H

class GAMgr
{
public:
    GAMgr(MovingMgr* m, int p, int n): mgr(m), population(p){}, balls_number(n){};
    virtual ~GAMgr();
    void random_initiailize();
    void selection();
    // node crossover
    void crossover();
    void start();
private:
	MovingMgr* mgr;
    int population;
    int balls_number;
    int order[population][balls_number];
};

#endif /* GAMGR_H */
