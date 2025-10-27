#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define RA 62
#define CA 15
#define CB 7
#define ROOT 0
#define ROOT_A_FEUILLE 1
#define FEUILLE_A_ROOT 2

int main(int argc, char* argv[]) {
    int size, rank, src, dest, mtype;
    int rangees, moyenne, extra, offset, i, j, k, rc;
    double a[RA][CA], b[CA][CB], c[RA][CB];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == ROOT) {

        moyenne = RA / (size - 1);
        extra = RA % (size - 1);

        offset = 0;
        mtype = ROOT_A_FEUILLE;

        for (dest = 1; dest <= (size - 1); dest++) {
            rangees = (dest <= extra) ? moyenne + 1 : moyenne;

            MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
            MPI_Send(&rangees, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
            MPI_Send(&a[offset][0], rangees * CA, MPI_DOUBLE, dest, mtype,
                     MPI_COMM_WORLD);
            MPI_Send(&b, CA * CB, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);

            offset = offset + rangees;
        }

        mtype = FEUILLE_A_ROOT;

        for (i = 1; i <= (size - 1); i++) {
            src = i;
            MPI_Recv(&offset, 1, MPI_INT, src, mtype, MPI_COMM_WORLD, &status);
            MPI_Recv(&rangees, 1, MPI_INT, src, mtype, MPI_COMM_WORLD, &status);
            MPI_Recv(&c[offset][0], rangees * CB, MPI_DOUBLE, src, mtype,
                     MPI_COMM_WORLD, &status);
        }
    } else if (rank > ROOT) {
        mtype = ROOT_A_FEUILLE;

        MPI_Recv(&offset, 1, MPI_INT, ROOT, mtype, MPI_COMM_WORLD, &status);
        MPI_Recv(&rangees, 1, MPI_INT, ROOT, mtype, MPI_COMM_WORLD, &status);
        MPI_Recv(&a, rangees * CA, MPI_DOUBLE, ROOT, mtype, MPI_COMM_WORLD,
                 &status);
        MPI_Recv(&b, CA * CB, MPI_DOUBLE, ROOT, mtype, MPI_COMM_WORLD, &status);

        for (k = 0; k < CB; k++) {
            for (i = 0; i < rangees; i++) {
                c[i][k] = 0.0;
                for (j = 0; j < CA; j++)
                    c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }
        }

        mtype = FEUILLE_A_ROOT;
        MPI_Send(&offset, 1, MPI_INT, ROOT, mtype, MPI_COMM_WORLD);
        MPI_Send(&rangees, 1, MPI_INT, ROOT, mtype, MPI_COMM_WORLD);
        MPI_Send(&c, rangees * CB, MPI_DOUBLE, ROOT, mtype, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
