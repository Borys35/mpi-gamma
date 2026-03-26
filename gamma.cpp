#include <iostream>
#include <mpi.h>
#include <ncurses.h>
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

    // std::cout << "Proces " << world_rank << " odebral wiadomosc " << n << std::endl;
    int start = world_rank * (n / (world_size));
    int end = (world_rank + 1) * (n / (world_size));
    int part_sum = 0;
    for (int i = start; i < end; i++) {
        // part_sum += 1.0 / i;
        std::cout << "Proces " << world_rank << ", i=" << i << std::endl;
        part_sum += i;
    }
    int sum = 0;
    MPI_Reduce(&part_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        std::cout << "Suma wszystkich elementow: " << sum << std::endl;
    }

    MPI_Finalize();
    return 0;
}