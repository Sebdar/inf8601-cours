#pragma once

#include <deque>
#include "omp.h"

template <typename T>
class parallel_deque {
  public:
    void push(const T& elem) {
        #pragma omp critical (deque)
        {
            storage.emplace_back(elem);
        }
    }

    T pop() {
        T t;

        #pragma omp critical (deque)
        {   
            if(storage.size() != 0) {
                t = storage.front();
                storage.pop_front();
            }
        }
        
        return t;
    }

  private:
    std::deque<T> storage;
};
