#include <iostream>

#include "board.hh"
#include "solver.hh"
#include <ctime>
using namespace std;


int main(int argc, char **argv)
{

    if(argc < 3)
    {
        cout << "Usage: " << argv[0] << " <board file>" << " <output file>" << endl;
        return 1;
    } //loop argv

    clock_t begin = clock();
	//clock_t start_local = clock();
	Board b(argv[1]);
	Solver s(b);
	bool acheived = s.solve(600000000);
	s.write(argv[2]);
	//s.curr_b.printer();

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    //cout << "Time elapsed: " << elapsed_secs << "s" <<endl;
	return acheived ? 0 : 1;
}
