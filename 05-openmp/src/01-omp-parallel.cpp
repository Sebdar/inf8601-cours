#include <iostream>
#include <omp.h>

int main() {
    std::cout << "This is a serial section\n";

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        std::cout << "This is a parallel section, thread : " << thread_id << '\n';
    }
    return 0;
}
