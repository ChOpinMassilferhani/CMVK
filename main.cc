#include <iostream>

#include "board.hh"
#include "solver.hh"

using namespace std;





int main(int argc, char **argv)
{
    
    Board toto(argv[1]);
    toto.printer();
    Solver test(toto);

    test.solve(10000);
    test.curr_b.pieces[1][0].rotate();
    test.curr_b.printer();
    int U = test.get_U();
    if(U)
        cout << "board is not solved " << U << endl;
    else
        cout << "board is solved " << U << endl;
}
