#include <stdio.h>
#include <malloc.h>
#include <math.h>

void CreateArray(int* arr, int size)
{
	printf("Enter the array elements: ");
	for (int i = 0; i < size; i++)
	{
		scanf_s("%d", &arr[i]);
	}
}

void PrintArray(int* arr, int size)
{
	printf("\r\nArray: ");
	for (int i = 0; i < size; i++)
	{
		printf("%d\t", *(arr+i));
	}
}

int Max(int* arr, int size)
{
	int max = *arr;
	for (int i = 0; i < size; i++)
	{
		if (max < *(arr + i))
			max = *(arr + i);
	}
	return max;
}

int Min(int* arr, int size)
{
	int min = *arr;
	for (int i = 0; i < size; i++)
	{
		if (min > *(arr + i))
			min = *(arr + i);
	}
	return min;
}

double Mean(int* arr, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum += *(arr + i);
	return sum / size;
}

double RMS(int* arr, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum += pow(*(arr + i) - Mean(arr, size), 2);
	return sqrt(sum / size);
}


int main()
{
	int size;
	printf("Size of array: ");
	scanf_s("%d", &size);
	int* arr;
	arr = (int*)malloc(size * sizeof(int));

	CreateArray(arr, size);
	PrintArray(arr, size);

	printf("\r\nMax of array: %d", Max(arr, size));
	printf("\r\nMin of array: %d", Min(arr, size));
	printf("\r\nMean of array: %lf", Mean(arr, size));
	printf("\r\nRMS of array: %lf\n", RMS(arr, size));

	free(arr);
}