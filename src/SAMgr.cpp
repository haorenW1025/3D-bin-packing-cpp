#include <cstdlib>
#include <math.h>
#include <iostream>
#include <random>
#include "SAMgr.h"

void SAMgr::start() {
    /* get initial solution */
    mgr->moving_algorithm();
    double cost = mgr->get_cost();
    std::cout << "initial solution" << std::endl;
    mgr->print_result();

    /* preform SA */
    while (currentTemperature > minTemperature) {
        for (int i = 0; i < maxIterationPerTemp; ++i) {
            std::cout << "\r" << "iteration: " << iteration;
            std::cout.flush();

            /* determine swapping index */
            int first_index = rand() % ((mgr->get_number()-1) - 0 + 1);
            int second_index;
            second_index = rand() % ((mgr->get_number()-1) - 0 + 1);
            /* avoid selecting same index */
            do {
                second_index = rand() % ((mgr->get_number()-1) - 0 + 1);
            } while (first_index == second_index);
            mgr->swap(first_index, second_index);

            mgr->reset();
            mgr->moving_algorithm();

            double new_cost = mgr->get_cost();
            if (new_cost <= cost) {
                cost = new_cost;
            } else {
                if (!perform_uphill(new_cost-cost)) {
                    /* swap back */
                    mgr->swap(first_index, second_index);
                }
                else cost = new_cost;
            }
            iteration++;
        }
        currentTemperature *= scalingParameter;
        std::cout << "\r" << "iteration: " << iteration << " tempeature: " << currentTemperature << " cost: " << cost << std::endl;
    }
    mgr->reset();
    mgr->moving_algorithm();
    cost = mgr->get_cost();
    std::cout << cost << std::endl;
    print_result();
}

bool SAMgr::perform_uphill(double cost) {
    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_real_distribution<double> dis(0,100);
    double param = exp(-(cost*100)/currentTemperature);
    double random = dis(gen);
    // std::cout << " " << random << std::endl;
    return param * 100 > random;
}

void SAMgr::print_result() {
    std::cout << std::endl;
    std::cout << "final result" << std::endl;
    mgr->print_result();
}
