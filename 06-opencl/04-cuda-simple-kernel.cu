#include <cuda_runtime.h>

#include <iostream>

__global__ void simple_kernel(int* buffer) {
    *buffer = 8601;
}

int main() {
    size_t buf_size = sizeof(int);

    int* buffer;
    cudaMalloc(&buffer, buf_size);

    simple_kernel<<<1, 1>>>(buffer);

    cudaDeviceSynchronize();

    int host_int;
    cudaMemcpy(&host_int, buffer, buf_size, cudaMemcpyDeviceToHost);

    std::cout << "Result is : " << host_int << '\n';
}
