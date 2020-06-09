#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>
#include <vector>
#include "CubeMovingMgr.h"
#include "SAMgr.h"
#include "GAMgr.h"

using namespace std;

//void parse_balls(fstream& input_file, MovingMgr* mgr) {
//    string line;
//    /* get box dimension */
//    getline(input_file, line);
//    mgr->set_boxDim(stod(line));
//
//    /* get number of balls */
//    getline(input_file, line);
//    int number = stoi(line);
//
//    for (int i = 0; i < number; ++i) {
//        getline(input_file, line);
//        mgr->add_sphere(stod(line));
//
//    }
//    input_file.close();
//}

void parse_cubes(fstream& input_file, CubeMovingMgr* mgr) {
    string line;
    getline(input_file, line);
    mgr->set_boxDim(stod(line));

    getline(input_file, line);
    int number = stoi(line);

    for (int i = 0; i < number; ++i) {
        getline(input_file, line);
        int start = line.find_first_of(" ");
        string temp;
        temp = line.substr(0, start);
        // cout << start << endl;
        double x = stod(temp);
        start = start + 1;
        int end = line.find_first_of(" ", start);
        temp = line.substr(start, end-start);
        double y = stod(temp);
        start = end + 1;
        end = line.length();
        temp = line.substr(start, end-start);
        double z = stod(temp);
        mgr->add_cube(x, y, z);
    }
}

int main(int argc, char** argv)
{
    fstream input_file, output_file;
    if (argc == 3) {
        output_file.open(argv[2], ios::out);
        if (!output_file) {
            cerr << "Cannot open the output file \"" << argv[2]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
    }
    else {
        cerr << "Usage: ./bin_packing <input file> <output file>" << endl;
        exit(1);
    }
    /* set random seed */
    srand( time(NULL) );

    vector<vector<double>> result;
    result.resize(10);
    for (unsigned i = 0; i < 10; ++i) {
        input_file.open(argv[1], ios::in);
        CubeMovingMgr* moving_mgr = new CubeMovingMgr();
        parse_cubes(input_file, moving_mgr);
        input_file.close();
        //    parse_balls(input_file, moving_mgr);

        /* SAMgr* SAmgr = new SAMgr(moving_mgr, 100, 1, 0.95); */
        /* SAmgr->start(result[i]); */
        GAMgr* GAmgr = new GAMgr(moving_mgr, 300, moving_mgr->get_number());
        GAmgr->start(result[i]);


        delete(moving_mgr);
        delete(GAmgr);
        /* delete(SAmgr); */
    }
    for (unsigned i = 0; i < 10; ++i) {
        for (unsigned j = 0; j < result[i].size(); ++j) {
            output_file << result[i][j] << " ";
        }
        output_file << "\n";
    }
//    delete(SAmgr);
	return 0;
}
