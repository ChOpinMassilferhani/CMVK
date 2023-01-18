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
    } //loop argv

    clock_t begin = clock();
    for (int i = 1; i < argc; i++)
    {
        Board b(argv[i]);
        Solver s(b);
        s.solve(10000000);
        //b.printer();

    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Time elapsed: " << elapsed_secs << "s for "<< argc -1  << " board" <<endl;

}
