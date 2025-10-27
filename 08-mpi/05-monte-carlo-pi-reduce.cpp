#include "mpi.h"
#include <cstdlib>
#include <iostream>

#include "04-monte-carlo-pi.hpp"

#define DARTS 50000
#define ROUNDS 10
#define ROOT 0

int main(int argc, char* argv[]) {
    double homepi, pi, avepi, pirecv, pisum;
    int rank, size, src, mtype, ret, i, n;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::random_device rd;

    avepi = 0;
    for (i = 0; i < ROUNDS; i++) {
        homepi = dboard(DARTS, rd);

        ret = MPI_Reduce(&homepi, &pisum, 1, MPI_DOUBLE, MPI_SUM, ROOT,
                         MPI_COMM_WORLD);

        if (rank == ROOT) {
            pi = pisum / size;

            avepi = ((avepi * i) + pi) / (i + 1);

            std::cout << "Pi ~= " << avepi << '\n';
        }
    }
    MPI_Finalize();
    return 0;
}
