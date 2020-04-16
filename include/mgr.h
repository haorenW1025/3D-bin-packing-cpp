#ifndef MGR_H
#define MGR_H

#include <math.h>
#include <vector>
#include <fstream>
#include "sphere.h"

class Mgr
{
public:
    Mgr():box_count(1), balls_count(0){};
    ~Mgr(){};

    /* access method */
    int get_number() {return balls.size();}
    double get_boxDim() {return box_dim;}

    /* modified method */
    void add_sphere(double radius){balls.push_back(Sphere(radius));};
    void set_boxDim(double dim) {box_dim = dim;}
    void moving_algorithm();

    /* utility method */
    bool init_moving(int, int);
    void moving(int, int, int);
    double calculate_volume(int);
    void write_result(std::fstream&);
    void print_result();

private:
    std::vector<Sphere> balls;
    std::vector<int> indexToBox;
    int box_count;
    double box_dim;
    int balls_count;
};

#endif /* MGR_H */
