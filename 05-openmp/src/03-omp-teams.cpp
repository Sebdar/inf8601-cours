#include <iostream>
#include <omp.h>

int main() {
    std::cout << "This is a serial section\n";

    #pragma omp teams num_teams(2)
    {
        int team_id = omp_get_team_num();

        #pragma omp parallel
        {
            int thread_count = omp_get_num_threads();
            int thread_id = omp_get_thread_num();
            #pragma omp critical
            std::cout << "This is a parallel section, thread : " << thread_id << " / " << thread_count << ", team " << team_id << '\n';
        }

    }
    return 0;
}
