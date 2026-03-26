#include <iostream>
#include <mpi.h>
#include <ncurses.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    long long n;
    if (world_rank == 0) {
        std::cout << "Podaj liczbe elementow (n): ";
        std::cin >> n;
    }
    MPI_Bcast(&n, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    std::cout << "Process " << world_rank << " received broadcast message " << n << std::endl;

    long long sum = 0;
    MPI_Reduce(&n, &sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        std::cout << "Sum of all elements: " << sum << std::endl;
    }

    MPI_Finalize();
    return 0;
}