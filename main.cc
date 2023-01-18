#include <iostream>

#include "board.hh"
#include "solver.hh"
#include <ctime>
using namespace std;


int main(int argc, char **argv)
{

    if(argc < 2)
    {
        cout << "Usage: " << argv[0] << " <board file>" << endl;
        return 1;
    }
    clock_t stop = clock();
    Board toto(argv[1]);
    toto.printer();
    Solver test(toto);

    test.solve(600000000);
    test.curr_b.printer();
    int U = test.get_U();
    if(U)
        cout << "board is not solved " << U << endl;
    else
        cout << "board is solved " << U << endl;
    cout << "time : " << (clock() - stop) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
}
