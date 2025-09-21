#include <iostream>
#include <omp.h>

int main() {
    std::cout << "This is a serial section\n";

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
        #pragma omp critical
        std::cout << "This is a parallel section, thread : " << thread_id << " / " << thread_count << '\n';
    }
    return 0;
}
