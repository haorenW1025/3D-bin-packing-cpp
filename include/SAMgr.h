#ifndef SAMGR_H
#define SAMGR_H

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <vector>
#include "CubeMovingMgr.h"

class SAMgr
{
public:
    SAMgr(CubeMovingMgr* m, int temp, int min_temp, double s):
        mgr(m),currentTemperature(temp), minTemperature(min_temp), scalingParameter(s){};
    virtual ~SAMgr(){};

    void start(std::vector<double> &);
    bool perform_uphill(double cost);
    void print_result();

private:
    CubeMovingMgr* mgr;
    int iteration = 0;
    int maxIterationPerTemp = 1000;
    double scalingParameter;
    double currentTemperature;
    double minTemperature;
};

#endif /* SAMGR_H */
