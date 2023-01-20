#include "solver.hh"
#include "board.hh"

#define DEBUG 0


Solver::Solver(Board &b) {
	curr_b = b;
	std::random_device rd;
	this->gen = std::mt19937(rd());
	this->dist = std::uniform_real_distribution<double>(0.0, 1.0);
}

int Solver::good_piece(int i, int j) {
	int U = 0;
	if (i != 0) {
		if (this->curr_b.pieces[i - 1][j].sud != this->curr_b.pieces[i][j].nord)
			U += 1;
	}
	if (j != 0) {
		if (this->curr_b.pieces[i][j - 1].est != this->curr_b.pieces[i][j].ouest)
			U += 1;
	}
	return U;
}

int Solver::get_U() {
	int U = 0;
	for (int i = 0; i < this->curr_b.size; i++)
		for (int j = 0; j < this->curr_b.size; j++)
			U += good_piece(i, j);

	return U;

}

bool Solver::candidate(double delta_U, double T) {
	double p = exp(-delta_U / T);
	double tmp = this->dist(this->gen);
	return  p < tmp;
}


double Solver::init_T()
{
	double T1 = 0;
	double T2 = 1000000;
	double T = T2;

	size_t n = curr_b.size * curr_b.size;

	double eps_T = 1;

	while ((T2 - T1) > eps_T)
	{
		T = T1 + (T2 - T1) / 2;

		int uniform = 0;
		int nb_samples = 100;

		for (int i = 0; i < nb_samples; ++i)
		{
			double eps_prob = 0.01;

			int U1 = this->get_U();
			int i1, i2 = 0;
			i1 = rand() % n;
			while (this->curr_b.pieces[i1 / curr_b.size][i1 % curr_b.size].fixed)
				i1 = rand() % n;

			i2 = rand() % n;
			while (i2 == i1 || this->curr_b.pieces[i2 / curr_b.size][i2 % curr_b.size].fixed)
				i2 = rand() % n;

			this->swap(i1, i2);
			int U2 = get_U();
			if (exp( abs(U2 - U1) / T) > 1 - eps_prob)
				uniform += 1;
		}

		if (uniform >= 0.98 * nb_samples)
			T2 = T;
		else
			T1 = T;
	}

	return T;

}

bool Solver::solve(int max_iterations) {

	size_t n = curr_b.size * curr_b.size;

	double min_T = 0.4;
	double lambda = 0.999;
	int iterations = 0;
	double T = init_T();

	double U1 = get_U();

	while (U1 != 0 && iterations < max_iterations) {

#if DEBUG
		if (iterations % 1000000 == 0)
		   cout << "iteration " << iterations << " U = " << U1 << " T = "<< T << endl;
#endif

		int i1, i2 = 0;
		i1 = rand() % n;
		while (this->curr_b.pieces[i1 / curr_b.size][i1 % curr_b.size].fixed)
			i1 = rand() % n;

		i2 = rand() % n;
		while (i2 == i1 || this->curr_b.pieces[i2 / curr_b.size][i2 % curr_b.size].fixed)
			i2 = rand() % n;

		this->swap(i1, i2);

		double U2 = get_U();

		if (U2 > U1 && candidate(U2 - U1, T))
				this->swap(i1, i2);

		if (T > min_T)
			T *= lambda;
		else
			T = min_T;

		U1 = get_U();
		iterations++;

	}
	return U1 == 0;
}

void Solver::swap(size_t p1, size_t p2) {
	size_t i1 = p1 / this->curr_b.size;
	size_t j1 = p1 % this->curr_b.size;
	size_t i2 = p2 / this->curr_b.size;
	size_t j2 = p2 % this->curr_b.size;
	std::iter_swap(this->curr_b.pieces[i1].begin() + j1, this->curr_b.pieces[i2].begin() + j2);
}

void Solver::write(char *path) {
	this->curr_b.write(path);
}
