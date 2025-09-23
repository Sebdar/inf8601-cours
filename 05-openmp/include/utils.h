#pragma once

#include <random>
#include <chrono>

auto now() {
    return std::chrono::steady_clock::now();
}

void random_fill(std::vector<float>& vec, float max=100.f) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.f, max);
    for(auto& i : vec) {
        i = dist(gen);
    }
}

void random_fill(float* vec, size_t n, float max=100.f) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.f, max);
    for(auto i = 0; i < n; ++i) {
        vec[i] = dist(gen);
    }
}


template <typename T>
long count_ms(T duration) {
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}
