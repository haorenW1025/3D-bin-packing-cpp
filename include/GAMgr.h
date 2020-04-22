#ifndef GAMGR_H
#define GAMGR_H

class GAMgr
{
public:
    GAMgr(int p): population(p){};
    virtual ~GAMgr();
    void random_initiailize();
    void selection();
    // node crossover
    void crossover();
    void start();
private:
    int population;
};

#endif /* GAMGR_H */
