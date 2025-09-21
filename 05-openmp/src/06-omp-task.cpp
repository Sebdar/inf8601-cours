#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

using namespace std::chrono_literals;

void task(int i) {
    #pragma omp critical
    std::cout << omp_get_thread_num() << " : " << i << '\n';
    std::this_thread::sleep_for(50ms);
}

int main() {
    std::cout << "This is a serial section\n";

    #pragma omp parallel
    {
        #pragma omp single
        {
            for(auto i = 0; i < 100; ++i) {
                #pragma omp task
                task(i);
            }
            
        }
    }
    return 0;
}
