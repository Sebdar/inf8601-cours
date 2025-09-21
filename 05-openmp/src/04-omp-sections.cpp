#include <iostream>
#include <omp.h>

#include "parallel_deque.h"

int main() {
    std::cout << "This is a serial section\n";

    parallel_deque<int> deque;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for(auto i = 0; i < 10; ++i) {
                deque.push(i);
            }
            deque.push(-1);
        }

        #pragma omp section
        {   
            int i;
            while((i = deque.pop()) != -1) {
                std::cout << "Received " << i << '\n';
            }
        }
    }
    return 0;
}
