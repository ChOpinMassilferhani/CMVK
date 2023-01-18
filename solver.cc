#include "solver.hh"
#include "board.hh"

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

bool Solver::sample(double delta_U, double T) {
    double p = exp(-delta_U / T);
    double tmp = this->dist(this->gen);
    if (tmp < p)
        return true;
    return false;
}

int Solver::solve(int max_iterations) {

    size_t n = curr_b.size * curr_b.size;

    int iterations = 0;
    double U1 = get_U();
    //cout << U1 << endl;
    while (U1 != 0 && iterations < max_iterations) {
        if (iterations % 1000000 == 0)
            cout << "iteration " << iterations << " U = " << U1 << endl;
        // 1- Choose two different random axes

        int i1, i2 = 0;
        i1 = rand() % n;
        while (this->curr_b.pieces[i1 / curr_b.size][i1 % curr_b.size].fixed)
            i1 = rand() % n;

        i2 = rand() % n;
        while (i2 == i1 || this->curr_b.pieces[i2 / curr_b.size][i2 % curr_b.size].fixed)
            i2 = rand() % n;

        this->swap(i1, i2);
        // 3- delta_u
        double U2 = get_U();

        if (U2 > U1) // 4- choose candidate
        {
            float ratio = exp(U1 - U2);
            float tmp = dist(this->gen);
            if (ratio < tmp) {
                //revient avant
                this->swap(i1, i2);
            }
        }

        U1 = get_U();
        iterations++;

    }
    return iterations;
}

void Solver::swap(size_t p1, size_t p2) {
    size_t i1 = p1 / this->curr_b.size;
    size_t j1 = p1 % this->curr_b.size;
    size_t i2 = p2 / this->curr_b.size;
    size_t j2 = p2 % this->curr_b.size;

    int tmp = this->curr_b.pieces[i1][j1].nord;
    this->curr_b.pieces[i1][j1].nord = this->curr_b.pieces[i2][j2].nord;
    this->curr_b.pieces[i2][j2].nord = tmp;

    tmp = this->curr_b.pieces[i1][j1].sud;
    this->curr_b.pieces[i1][j1].sud = this->curr_b.pieces[i2][j2].sud;
    this->curr_b.pieces[i2][j2].sud = tmp;

    tmp = this->curr_b.pieces[i1][j1].est;
    this->curr_b.pieces[i1][j1].est = this->curr_b.pieces[i2][j2].est;
    this->curr_b.pieces[i2][j2].est = tmp;

    tmp = this->curr_b.pieces[i1][j1].ouest;
    this->curr_b.pieces[i1][j1].ouest = this->curr_b.pieces[i2][j2].ouest;
    this->curr_b.pieces[i2][j2].ouest = tmp;


}
