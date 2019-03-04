// cuda2dtest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "cuda_part.cuh"

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

float **arr_alloc() {

	float *big_arr = (float *)malloc(5 * 5 * sizeof(float));
	float ** arr = (float**) malloc(5 * sizeof(float *));

	for (size_t i = 0; i < 5; i++)
	{
		arr[i] = big_arr +(5*i);
	}

	return arr;
}


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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
