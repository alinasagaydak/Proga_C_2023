#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<time.h>
#include <math.h>

int choose_sort()
{
	int sort_type = 0;
	printf("1 - sortIncrease\n2 - sortDecrease\n3 - sortAbs\n");
	printf("Choose the sorting method: ");
	scanf_s("%d", &sort_type);
	return sort_type;
}

void PrintArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d\t", *(arr + i));
	}
}

void Replace(int* x1, int* x2)
{
	int temp = *x1;

	*x1 = *x2;

	*x2 = temp;
}

int define_pivot(int* arr, int size)
{
	int mid = (size - 1) / 2;

	if (arr[mid] < arr[0])
		Replace(&arr[0], &arr[mid]);
	if (arr[size - 1] < arr[0])
		Replace(&arr[0], &arr[size - 1]);
	if (arr[size - 1] < arr[mid])
		Replace(&arr[size - 1], &arr[mid]);

	return arr[mid];
}


void sortIncrease(int* arr, int size)
{
	int start = 0; //указатель на начало массива
	int end = size - 1; //указатель на конец массива
	int pivot = define_pivot(arr, size);

	do
	{
		while (arr[start] < pivot)
			start++;
		while (arr[end] > pivot)
			end--;
		if (start <= end)
		{
			Replace(&arr[start], &arr[end]);
			start++;
			end--;
		}
	} while (start <= end);
	if (end > 0)
		sortIncrease(arr, end + 1);

	if (start < size)
		sortIncrease(&arr[start], size - start);
}


void sortDecrease(int* arr, int size)
{
	int start = 0; //указатель на начало массива
	int end = size - 1; //указатель на конец массива
	int pivot = define_pivot(arr, size);

	do
	{
		while (arr[start] > pivot)
			start++;
		while (arr[end] < pivot)
			end--;
		if (start <= end)
		{
			Replace(&arr[start], &arr[end]);
			start++;
			end--;
		}
	} while (start <= end);
	if (end > 0)
		sortDecrease(arr, end + 1);

	if (start < size)
		sortDecrease(&arr[start], size - start);
}

void sortAbs(int* arr, int size)
{
	int start = 0; //указатель на начало массива
	int end = size - 1; //указатель на конец массива
	int pivot = define_pivot(arr, size);

	do
	{
		while (abs(arr[start]) < abs(pivot))
			start++;
		while (abs(arr[end]) > abs(pivot))
			end--;
		if (start <= end)
		{
			Replace(&arr[start], &arr[end]);
			start++;
			end--;
		}
	} while (start <= end);
	if (end > 0)
		sortAbs(arr, end + 1);

	if (start < size)
		sortAbs(&arr[start], size - start);
}

void sort_func(int* arr, int size, int sort_type)
{
	if (sort_type == 1)
		sortIncrease(arr, size);
	else if (sort_type == 2)
		sortDecrease(arr, size);
	else
		sortAbs(arr, size);
}

int main()
{
	int size = 10;
	int* arr;
	arr = (int*)malloc(size * sizeof(int));

	time_t t;
	srand((unsigned)time(&t)); ///* Intializes random number generator */

	printf("Array: ");
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % (201) + (-100);
		printf("%d ", arr[i]);
	}
	printf("\n");

	sort_func(arr, size, choose_sort());
	printf("\n");
	printf("Sorting array: ");
	PrintArray(arr, size);
	
	free(arr);
}
