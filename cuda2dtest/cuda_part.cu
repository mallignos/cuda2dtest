#include "cuda_part.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>

#ifdef __CUDACC__
#define KERNEL_ARGS2(grid,block) <<< grid , block >>>
#else
#define KERNEL_ARGS2(grid, block)
#endif


__global__
void cuda_run(void *arr, size_t pitch) {
	int id = ((int)blockIdx.x) * ((int)blockDim.x) + (int)(threadIdx.x);
	int x = id / 5;
	int y = id % 5;
	float a, b;

	if (id < 25) {
		float *row_a = (float *)((char *)arr + y * pitch);
		a = row_a[x];
		
		row_a[x] += 1;
		b = row_a[x];
		
		printf("bye %d %f %f\n", id, a, b);
	}
	
}


void setup(float **h_arr) {

	

	void *d_arr;
	size_t pitch;
	cudaError_t e;
	e = cudaMallocPitch(&d_arr, &pitch, 5 * sizeof(float), 5 );
	if (e != cudaSuccess) {
		std::cout << "Memalloc fail\n";
	}
	std::cout << pitch << "\n";

	e = cudaMemcpy2D(d_arr, pitch, *h_arr, 5 * sizeof(float), 5 * sizeof(float) , 5 , cudaMemcpyHostToDevice);
	//e = cudaMemset2D(d_arr, pitch, 1, 5 * sizeof(float), 5);
	if (e != cudaSuccess) {
		std::cout << "Memcpy fail\n";
	}

	cuda_run KERNEL_ARGS2(1, 64) (d_arr,pitch);

	e = cudaMemcpy2D(*h_arr, 5 * sizeof(float), d_arr, pitch, 5 * sizeof(float), 5 , cudaMemcpyDeviceToHost);
	if (e != cudaSuccess) {
		std::cout << "2nd Memcpy fail\n";
	}
	cudaFree(d_arr);

}