#pragma once

#include "board.hh"

class Solver
{
    public:
        Solver(Board &b);

        Board curr_b;

        bool is_solved();

        bool good_piece(int i, int j);
};