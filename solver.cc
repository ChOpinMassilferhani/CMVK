#include "solver.hh"
#include "board.hh"

Solver::Solver(Board &b)
{
    curr_b = b;
}


bool Solver::good_piece(int i, int j)
{
    if(i == 1 && this->curr_b.pieces[i-1][j].sud != this->curr_b.pieces[i][j].nord)
        return false;

    if(i == this->curr_b.size - 2 && this->curr_b.pieces[i+1][j].nord != this->curr_b.pieces[i][j].sud)
        return false;

    if(j == 1 && this->curr_b.pieces[i][j-1].est != this->curr_b.pieces[i][j].ouest)
        return false;
    
    if(j == this->curr_b.size - 2 && this->curr_b.pieces[i][j+1].ouest != this->curr_b.pieces[i][j].est)
        return false;
    
    return true;
}

bool Solver::is_solved()
{
    for (int i = 0; i < this->curr_b.size; i++)
        for (int j = 0; j < this->curr_b.size; j++)
            if (!good_piece(i,j))
                return false;

    return true;
    
}