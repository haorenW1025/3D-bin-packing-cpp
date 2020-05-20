#include <random>
#include "GAMgr.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <random>
#include <algorithm> 
#include <vector>
#include <chrono>
#include <random>

void GAMgr::random_initiailize(){
	std::vector<int> foo;
	for(int i=0;i<balls_number;i++) {
        foo.push_back(i);
	}
	for(int i=0;i<population;i++) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
		for(int j=0;j<balls_number;j++) {
			order[i][j] = foo[j];
		}
	}
	for(int i=0;i<population;i++) {
        cost[i] = moving(order[i]);
	}
}

void GAMgr::update_cost() {
	for(int i=0;i<population;i++) {
		mgr->reorder(order[i]);
    	mgr->reset();
    	mgr->moving_algorithm();
    	cost[i] = mgr->get_cost();
    	mgr->reorder_back(order[i]);
	}
}

void GAMgr::mutation() {
    std::vector<std::pair<int, int>> possible_pair;
    for (int i = 0; i < balls_number-1; ++i) {
        for (int j = i+1; j < balls_number; ++j) {
            possible_pair.push_back(std::make_pair(i, j));
        }
    }
    // assert(possible_pair.size() == (population*(population-1)/2));
    for (int i = 0; i < population; ++i){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (possible_pair.begin(), possible_pair.end(), std::default_random_engine(seed));
        for (int j = 0; j < balls_number; ++j) {
            int first_index = possible_pair[j].first;
            int second_index = possible_pair[j].second;
            int temp = order[i][first_index];
            order[i][first_index] = order[i][second_index];
            order[i][second_index] = temp;
            double mut_cost = moving(order[i]);
            if (mut_cost < cost[i]) {
                cost[i] = mut_cost;
            } else {//swap back
                temp = order[i][first_index];
                order[i][first_index] = order[i][second_index];
                order[i][second_index] = temp;
            }
    	}
    }
}

double GAMgr::moving(int* order) {
    mgr->reorder(order);
    mgr->reset();
    mgr->moving_algorithm();
    double _cost = mgr->get_cost();
    mgr->reorder_back(order);
    return _cost;
}

double GAMgr::get_avg_cost(int ** new_order) {
	double total_cost = 0;
	for(int i=0;i<population;i++) {
		mgr->reorder(new_order[i]);
    	mgr->reset();
    	mgr->moving_algorithm();
    	total_cost += mgr->get_cost();
    	mgr->reorder_back(new_order[i]);
	}
	return total_cost / population;
}
void GAMgr::selection(){
	int **temp;
    temp = new int*[population];
    for (int i = 0; i < population; ++i) {
        temp[i] = new int[balls_number];
    }
	cur_cost=999999;
	for(int i=0;i<population;i++) {//best result
		if(cost[i]<best_cost) {
			best_cost=cost[i];
			for(int j=0;j<balls_number;j++) {
				best_order[j]=order[i][j];
			}
		}
		if(cost[i]<cur_cost) {
			cur_cost=cost[i];
		}
	}
	for(int i=0;i<population/2;i++) {
		if(cost[2*i] < cost[2*i+1]) {
			for(int j=0;j<balls_number;j++) {
				temp[i][j]=order[2*i][j];
			}
		} else {
			for(int j=0;j<balls_number;j++) {
				temp[i][j]=order[2*i+1][j];
			}
		}
	}
	
	std::vector<int> foo;
	for(int i=0;i<population;i++) {
		foo.push_back(i);
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
	for(int i=0;i<population/2;i++) {
		if(cost[foo[2*i]] < cost[foo[2*i+1]]) {
			for(int j=0;j<balls_number;j++) {
				temp[i+population/2][j]=order[foo[2*i]][j];
			}
		} else {
			for(int j=0;j<balls_number;j++) {
				temp[i+population/2][j]=order[foo[2*i+1]][j];
			}
		}
	}
	
	for(int i=0;i<population;i++) {
		for(int j=0;j<balls_number;j++) {
			order[i][j]=temp[i][j];
		}
	}
	
	for (int i=0;i<population;i++) {
		delete [] temp[i];
	}
	delete [] temp;
}

void normalization() {
}

double** GAMgr::node_probability() {
	double** prob;
	prob = new double*[balls_number];
	for (int i=0;i<balls_number;i++) {
		prob[i] = new double[balls_number];
	}

    // initialize
    for (int i = 0; i < balls_number; ++i) {
        for (int j = 0; j < balls_number; ++j) {
            prob[i][j] = 0;
        }
    }
    // accumulate
    for (int i = 0; i < population; ++i) {
        for (int j = 0; j < balls_number; ++j) {
            prob[j][order[i][j]]++;
        }
    }
    //add radom
    double normalize;
    for (int i=0;i<balls_number;i++) {
    	normalize = 0;
    	for (int j=0;j<balls_number;j++) {
    		normalize += prob[i][j];
		}
		for (int j=0;j<balls_number;j++) {
			prob[i][j] /= normalize;
		}
		for (int j=0;j<balls_number;j++) {
			prob[i][j] = 0.1 * 1.0/balls_number + 0.9 * prob[i][j];
		}
	}
    return prob;
}

double** GAMgr::edge_probability() {
	double** prob;
	prob = new double*[balls_number];
	for (int i=0;i<balls_number;i++) {
		prob[i] = new double[balls_number];
	}
	for (int i = 0; i < balls_number; ++i) {
        for (int j = 0; j < balls_number; ++j) {
            prob[i][j] = 0;
        }
    }
	for (int i=0;i<population;i++) {
        for (int j=0;j<balls_number-1;j++) {
            prob[order[i][j]][order[i][j+1]]++;
        }
    }
    //add radom
    double normalize;
    for (int i=0;i<balls_number;i++) {
    	normalize = 0;
    	for (int j=0;j<balls_number;j++) {
    		normalize += prob[i][j];
		}
		for (int j=0;j<balls_number;j++) {
			prob[i][j] /= normalize;
		}
		for (int j=0;j<balls_number;j++) {
			prob[i][j] = 0.1 * 1.0/balls_number + 0.9 * prob[i][j];
		}
	}
    return prob;
}
int* GAMgr::node(double** prob) {
	int* new_order;
	new_order = new int[balls_number];
	for (int i=0;i<balls_number;i++) {
		new_order[i] = -1;
	}
    
    
    bool selected[balls_number];
    double temp[balls_number][balls_number];
    
    for (int l = 0; l < balls_number; ++l){
        selected[l] = false;
    }
    for (int l = 0; l < balls_number; ++l){
        for(int m=0;m<balls_number;++m){
        	temp[l][m]=prob[l][m];
		}
    }
    
    for (int j = 0; j < balls_number; ++j) {
        std::random_device rd;
        std::default_random_engine gen = std::default_random_engine(rd());
        std::uniform_real_distribution<double> dis(0,1);
        double random = dis(gen);
        // normalize
        double normalize = 0;
        for (int l = 0; l < balls_number; ++l){
            if (selected[l] == false)
                normalize += temp[j][l];
        }
        for (int l = 0; l < balls_number; ++l) {
            if (selected[l] == false)
                temp[j][l] /= normalize;
        }
        double possible = 0;
        for (int k = 0; k < balls_number; ++k) {
            if (selected[k]) continue;
            possible += temp[j][k];
            if (possible > random-1e-3) {
                selected[k] = true;
                new_order[j] = k;
                break;
            }
        }
        if (new_order[j] == -1) {
        	for (int k=0;k<balls_number;k++) {
            	if (selected[k]==false) {
            		selected[k] = true;
                    new_order[j] = k;
                    break;
				}
			}
		}
    }

//	for (int j=0;j<balls_number;j++) {
//		std::cout << new_order[j] << ",";
//	}
//	std::cout << std::endl;
    return new_order;
}

int* GAMgr::edge(double** prob, double* node_prob) {
	int* new_order;
	new_order = new int[balls_number];
	for (int i=0;i<balls_number;i++) {
		new_order[i] = -1;
	}
	
	
    bool selected[balls_number];
    double temp[balls_number][balls_number];
    double node_temp[balls_number];
    
	for (int j=0;j<balls_number;j++) {
        selected[j] = false;
    }
    for (int j= 0;j<balls_number;j++ ){
        for(int k=0;k<balls_number;k++) {
        	temp[j][k]=prob[j][k];
		}
    }
    for (int i=0;i<balls_number;i++) {
    	node_temp[i] = node_prob[i];
	}
    
    for (int j=0;j<balls_number;j++) {
    	std::random_device rd;
        std::default_random_engine gen = std::default_random_engine(rd());
        std::uniform_real_distribution<double> dis(0,1);
        double random = dis(gen);
        if (j==0) {
        	double node_normalize = 0;
	        for (int l = 0; l < balls_number; ++l){
	            node_normalize += node_temp[l];
	        }
	        for (int l = 0; l < balls_number; ++l) {
	            node_temp[l] /= node_normalize;
	        }
			double node_probability = 0;
        	for (int k=0;k<balls_number;k++) {
        		if (selected[k]) continue;
        		node_probability += node_temp[k];
        		if (node_probability > random-1e-3) {
        			selected[k] = true;
                	new_order[0] = k;
                	break;
				}
			}
			if (new_order[0] == -1) {
            	for (int k=0;k<balls_number;k++) {
	            	if (selected[k]==false) {
	            		selected[k] = true;
	                    new_order[0] = k;
	                    break;
					}
				}
			}
		} else {
			//normalize
			double normalize = 0;
    		for (int l=0;l<balls_number;l++){
                if (selected[l] == false) {
                	normalize += temp[new_order[j-1]][l];
				} else {
					temp[new_order[j-1]][l] = 0;
				}
            }
            for (int l=0;l<balls_number;l++) {
                if (selected[l] == false)
                    temp[new_order[j-1]][l] /= normalize;
            }
			double probability = 0;
        	for (int k=0;k<balls_number;k++) {
        		if (selected[k]) continue;
        		probability += temp[new_order[j-1]][k];
        		if (probability > random-1e-3) {
        			selected[k] = true;
                	new_order[j] = k;
                	break;
				}
			}
			if (new_order[j] == -1) {
            	for (int k=0;k<balls_number;k++) {
	            	if (selected[k]==false) {
	            		selected[k] = true;
	                    new_order[j] = k;
	                    break;
					}
				}
			}
		}
	}
//    for (int j=0;j<balls_number;j++) {
//		std::cout << new_order[j] << ",";
//	}
//	std::cout << std::endl;
	return new_order;
}

void GAMgr::crossover(int iteration){
	int **new_order;
    new_order = new int*[population];
//    for (int i = 0; i < population; ++i) {
//        new_order[i] = new int[balls_number];
//    }

    
    double** node_prob;
    double** edge_prob;
    node_prob = node_probability();
    edge_prob = edge_probability();
    

    if (iteration == 1) {
    	node_p = 0.5;
    	edge_p = 0.5;
	} else {
		node_p = 1.0 - exp(total_node_cost/take_node/temperature) /
            (exp(total_node_cost/take_node/temperature) + exp(total_edge_cost/take_edge/temperature));
		edge_p = 1.0 - node_p;
	}
	
//	total_node_cost = 0;
//	total_edge_cost = 0;
//	take_node = 0;
//	take_edge = 0;
	
	int* edge_or_node;
	edge_or_node = new int[population];
	for (int i=0;i<population;i++) {
		if (i < 10) {
			new_order[i] = node(node_prob);
	    	total_node_cost += moving(new_order[i]);
	    	take_node++;
	    	edge_or_node[i] = 0;
	    } else if (i < 20) {
	    	new_order[i] = edge(edge_prob, node_prob[0]);
			total_edge_cost += moving(new_order[i]);
	    	take_edge++;
	    	edge_or_node[i] = 1;
		} else {
			std::random_device rd;
		    std::default_random_engine gen = std::default_random_engine(rd());
		    std::uniform_real_distribution<double> dis(0,1);
		    double random = dis(gen);
		    if (random > node_p-1e-6) {
		    	new_order[i] = node(node_prob);
		    	total_node_cost += moving(new_order[i]);
		    	take_node++;
		    	edge_or_node[i] = 0;
			} else {
				new_order[i] = edge(edge_prob, node_prob[0]);
				total_edge_cost += moving(new_order[i]);
		    	take_edge++;
		    	edge_or_node[i] = 1;
			}
		}
	}


	rtr(new_order, edge_or_node);

	for (int i=0;i<balls_number;i++) {
		delete [] node_prob[i];
	}
	delete [] node_prob;
	
	for (int i=0;i<balls_number;i++) {
		delete [] edge_prob[i];
	}
	delete [] edge_prob;

    for (int i = 0; i < population; ++i) {
        delete [] new_order[i];
    }
	delete [] new_order;
	
	delete [] edge_or_node;
}

int GAMgr::node_distance(int* order_1, int* order_2) {
    int distance = 0;
    for (int i = 0; i < balls_number; ++i) {
        if (order_1[i] != order_2[i]) {
            distance++;
        }
    }
    return distance;
}

int GAMgr::edge_distance(int* order_1, int* order_2) {
	int same = 0;
	for (int i=0;i<balls_number-1;i++) {
		for (int j=0;j<balls_number-1;j++) {
			if (order_1[i] == order_2[j] && order_1[i+1] == order_2[j+1]) {
				same++;
				break;
			}
		}
		
	}
	return balls_number-1 - same;
}

void GAMgr::rtr(int** new_order, int* edge_or_node) {
    int distance = population;
    std::vector <int> index;
    int window_size = 200;
    std::vector<int> random_index;
    for (int i = 0; i < population; ++i) {
        random_index.push_back(i);
    }
    for (int i = 0; i < population; ++i) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (random_index.begin(), random_index.end(), std::default_random_engine(seed));
        int count = 0;
        // std::cout << count << std::endl;
        int best_index = 0;
        for (int j = 0; j < window_size; ++j) {
            int temp_index = random_index[j];
            int temp;
            if (edge_or_node[i] == 0) {
                temp = node_distance(new_order[i], order[temp_index]);
            } else {
                temp = edge_distance(new_order[i], order[temp_index]);
            }
            if (temp < distance) {
                best_index = temp_index;
            }
        }

        double new_cost = moving(new_order[i]);

        if (new_cost < cost[best_index]) {
            index.push_back(best_index);
        }
    }
    for (int i = 0, n = index.size(); i < n; ++i) {
        for (int j = 0; j < balls_number; ++j) {
            order[index[i]][j] = new_order[index[i]][j];
        }
    }
}

void GAMgr::start(){
    random_initiailize();
    for (int i = 0; i < 200; ++i) {
        selection();
        update_cost();
        crossover(i+1);
        update_cost();
        mutation();
        temperature *= 0.95;

		std::cout << i << ": " << best_cost << " " << cur_cost << " " << "edge: " << edge_p << " node: " << node_p << std::endl;
        
        
    }
	mgr->reorder(best_order);
    mgr->reset();
    mgr->moving_algorithm();
    mgr->print_result();
}
