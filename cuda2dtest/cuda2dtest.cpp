// cuda2dtest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "cuda_part.cuh"

//some nice printing
void arr_print(float **arr) {
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t q = 0; q < 5; q++)
		{
			std::cout << arr[i][q] << " , ";
		}
		std::cout << "\n";
	}
}

// allocates the array on the heap
float **arr_alloc() {

	float *big_arr = (float *)malloc(5 * 5 * sizeof(float));
	float ** arr = (float**) malloc(5 * sizeof(float *));

	for (size_t i = 0; i < 5; i++)
	{
		arr[i] = big_arr +(5*i);
	}

	return arr;
}

// puts some nice numbers into the array
void arr_populate(float **arr) {
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t q = 0; q < 5; q++)
		{
			arr[i][q] = (i + 1) * (q + 1);
		}
	}
}

int main()
{
	float **arr = arr_alloc();
	arr_populate(arr);
	arr_print(arr);
	setup(arr);
	arr_print(arr);
	system("pause");
}

