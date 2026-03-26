#include <iostream>
#include <mpi.h>
#include <cmath>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_size; // liczba procesow
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank; // numer procesu
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int n; // n = 50, p = 4, n/p = 12, reszta = 2
    if (world_rank == 0) {
        std::cout << "Podaj liczbe elementow (n): ";
        std::cin >> n;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int start = world_rank * (n / (world_size));
    int end = (world_rank + 1) * (n / (world_size));
    int remainder = n % world_size;
    if (world_rank < remainder) {
        start += world_rank;
        end += world_rank + 1;
    } else {
        start += remainder;
        end += remainder;
    }
    double part_sum = 0;
    for (int i = start; i < end; i++) {
        part_sum += 1.0 / (i + 1);
    }
    double sum = 0;
    MPI_Reduce(&part_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) { // tylko "serwer" oblicza wynik i go wyswietla
        double result = sum - log(n);
        std::cout << "Gamma: " << result << std::endl; // stała Eulera-Mascheroniego = 0,57721566
    }

    MPI_Finalize();
    return 0;
}