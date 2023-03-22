#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<time.h>
#include <math.h>

void PrintArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d\t", *(arr + i));
	}
	printf("\n");
}

void Replace(int* x1, int* x2)
{
	int temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}

int compare_inс(int* a, int* b)  /////Написать сравнение для указателей
{
	int a_int = *a;
	int b_int = *b;
	return a_int > b_int;
}

int compare_dec(int* a, int* b)
{
	int a_int = *a;
	int b_int = *b;
	return a_int < b_int;
}

int compare_abs(int* a, int* b)
{
	int a_int = *a;
	int b_int = *b;
	return abs(a_int) > abs(b_int);
}

void bsort(int* arr, int len, int (*compar)(int*, int*))
{
	bool noSwap;

	for (int i = len - 1; i >= 0; i--)
	{
		noSwap = 1;

		for (int j = 0; j < i; j++)
		{
			if (compar((arr + j), (arr + j + 1)))
			{
				Replace(&arr[j], &arr[j + 1]);
				noSwap = 0;
			}

		}

		if (noSwap == 1)
			break;
	}
}

int main()
{
	int size = 10;
	int* arr;
	arr = (int*)malloc(size * sizeof(int));

	time_t t;
	srand((unsigned)time(&t));

	printf("Array: ");
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % (201) + (-100);
		printf("%d ", arr[i]);
	}
	printf("\n");


	printf("\n");
	bsort(arr, size, compare_inс);
	printf("Sorting increase array: ");
	PrintArray(arr, size);

	bsort(arr, size, compare_dec);
	printf("Sorting decrease array: ");
	PrintArray(arr, size);

	bsort(arr, size, compare_abs);
	printf("Sorting abs array: ");
	PrintArray(arr, size);

	free(arr);
}