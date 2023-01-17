#pragma once

#include "board.hh"
#include <random>

class Solver
{
    public:
        Solver(Board &b);

        Board curr_b;

        int get_U();

        int good_piece(int i, int j);

        int solve(int max_iterations);

        bool sample(double delta_U, double T);

        random_device rd;  
	    mt19937 gen; 
	    uniform_real_distribution<double>  dist;
};