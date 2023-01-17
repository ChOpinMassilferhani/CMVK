#include "solver.hh"
#include "board.hh"

Solver::Solver(Board &b)
{
    curr_b = b;
    std::random_device rd;  
	this->gen = std::mt19937(rd()); 
	this->dist = std::uniform_real_distribution<double>(0.0, 1.0);
}


int Solver::good_piece(int i, int j)
{
    int U = 0;
    if (i != 0)
    { 
		if (this->curr_b.pieces[i-1][j].sud != this->curr_b.pieces[i][j].nord)
					U += 1;
    }
    if (j != 0)
    {
		if (this->curr_b.pieces[i][j-1].est != this->curr_b.pieces[i][j].ouest)
					U += 1;
    }
    return U;
}

int Solver::get_U()
{
    int U = 0;
    for (int i = 0; i < this->curr_b.size; i++)
        for (int j = 0; j < this->curr_b.size; j++)
            U += good_piece(i,j);

    return U;
    
}

bool Solver::sample(double delta_U, double T)
{
	double p = exp(- delta_U / T);
	double tmp = this->dist(this->gen); 
	if (tmp < p)
		return true;
	return false;
}

int Solver::solve(int max_iterations)
{

	int n = curr_b.size * curr_b.size;

	int iterations = 0;
	double U1 = get_U();
    cout << U1 << endl;
	while (U1 != 0)
	{
        cout << U1 << endl;
		// 1- Choose two different random axes
        
        int i1,i2,swap, a1, ia1, a2, ia2, rot = 0;
        swap = rand() % 2;
        
		i1 = rand() % n;
        while (this->curr_b.pieces[i1/n][i1 % n].fixed)
            i1 = rand() % n;
        
		i2 = rand() % n;
		while (i2 == i1 || this->curr_b.pieces[i2/n][i2 % n].fixed)
			i2 = rand() % n;

		// 2- swap axis
        if(swap)
		    std::iter_swap(this->curr_b.pieces[i1/n].begin() + (i1 % n), this->curr_b.pieces[i2/n].begin() + (i2 % n));
        else
        {
            rot = rand() % 2;
            if (rot)
            {
                a1 = rand() % 4;
                ia1 = 4 - a1;
                while (a1)
                {
                    this->curr_b.pieces[i1/n][i1%n].rotate();
                    a1--;
                }
            }
            else
            {
                a2 = rand() % 4;
                ia2 = 4 - a2;
                while (a2)
                {
                    this->curr_b.pieces[i2/n][i2%n].rotate();
                    a2--;
                }
            }
        }
        

		// 3- delta_u
		double U2 = get_U();
		double delta_U = U2 - U1;

		if (U2 <= U1) // 4- choose candidate
		{
            //fait rien
		}	
		else // choose candidate based on transition proba
		{
            float ratio = exp(U2 - U1);
            if (ratio <= dist(gen))
            {
                //fait rien
            }
            else
            {
                
                //revient avant
                if(swap)
                    std::iter_swap(this->curr_b.pieces[i1/n].begin() + (i1 % n), this->curr_b.pieces[i2/n].begin() + (i2 % n));
                else
                {
                    //cout << "in" << endl;
                    if(rot)
                    {
                        while (ia1)
                        {
                            this->curr_b.pieces[i1/n][i1%n].rotate();
                            ia1--;
                        }
                    }
                    else
                    {
                        while (ia2)
                        {
                            this->curr_b.pieces[i2/n][i2%n].rotate();
                            ia2--;
                        }
                    }
                }
            }
		}
	
		if (max_iterations == iterations)
			break;
		
		U1 = get_U();
		iterations++;

	}
	return iterations;
}