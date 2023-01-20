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
    }

	Board b(argv[1]);
	Solver s(b);
	bool acheived = s.solve(600000000);
	s.write(argv[2]);
    
	return acheived ? 0 : 1;
}
