#include <iostream>
#include <fstream>
#include <cmath>
#include "mgr.h"

using namespace std;

void parse_input(fstream& input_file, Mgr* mgr) {
    string line;
    /* get box dimension */
    getline(input_file, line);
    mgr->set_boxDim(stod(line));

    /* get number of balls */
    getline(input_file, line);
    int number = stoi(line);

    for (int i = 0; i < number; ++i) {
        getline(input_file, line);
        mgr->add_sphere(stod(line));

    }
    input_file.close();
}

int main(int argc, char** argv)
{
    fstream input_file, output_file;
    if (argc == 3) {
        input_file.open(argv[1], ios::in);
        output_file.open(argv[2], ios::out);
        if (!input_file) {
            cerr << "Cannot open the input file \"" << argv[1]
                 << "\". The program will be terminated..." << endl;
            exit(1);
        }
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

	const int num_of_ball=10;
    Mgr* mgr = new Mgr();

    parse_input(input_file, mgr);

    mgr->moving_algorithm();
    mgr->print_result();
    mgr->write_result(output_file);

    delete mgr;
	return 0;
}
