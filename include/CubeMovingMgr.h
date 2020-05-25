#ifndef CubeMovingMgr_H
#define CubeMovingMgr_H

#include <math.h>
#include <vector>
#include <fstream>
#include "cube.h"

class CubeMovingMgr
{
public:
    CubeMovingMgr():box_count(1), cubes_count(0){};
    ~CubeMovingMgr(){};

    /* access method */
    int get_number() {return cubes.size();}
    double get_boxDim() {return box_dim;}

    /* modified method */
    void add_cube(double x, double y, double z){cubes.push_back(Cube(x, y, z));};
    void set_boxDim(double dim) {box_dim = dim;}
    void moving_algorithm();

    /* utility method */
	bool init_moving(int, int ,int);
    void moving(int, int, int, int);
    double calculate_volume(int);
    void write_result(std::fstream&);
    void print_result();

    /* SA integration*/
    double get_cost();
    void reset();
    void swap(int, int);
    void reorder(int*);
    void reorder_back(int*);

private:
    std::vector<Cube> cubes;
    std::vector<int> indexToBox;
    int box_count;
    double box_dim;
    int cubes_count;
    double eps=1e-6;
};

#endif /* CubeMovingMgr_H */
