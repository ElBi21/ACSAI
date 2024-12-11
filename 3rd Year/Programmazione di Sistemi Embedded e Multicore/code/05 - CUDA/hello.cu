#include <stdio.h>
#include <cuda.h>

__global__ void hello_world() {
    printf("Hello world!\n");
}

int main() {
    hello_world<<<10, 2>>>();
    cudaDeviceSynchronize();
    return 0;
}