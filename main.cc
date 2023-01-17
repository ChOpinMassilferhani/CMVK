#include <iostream>

#include "board.hh"
#include "solver.hh"

using namespace std;





int main(int argc, char **argv)
{
    
    Board toto(argv[1]);
    toto.printer();
    Solver test(toto);
    if(test.is_solved())
        cout << "board is solved" << endl;
    else
        cout << "board is not solved" << endl;
}
