#include <stdio.h>
#include <math.h>
#include <malloc.h>

int choose_sort()
{
	int sort_type = 0;
	printf("1 - sortIncrease\n2 - sortDecrease\n3 - sortAbs\n");
	printf("Choose the sorting method: ");
	scanf_s("%d", &sort_type);
	printf("\n");
	return sort_type;
}

void initArray(int* arr, int size)
{
	printf("Enter the array elements: ");
	for (int i = 0; i < size; i++)
	{
		scanf_s("%d", &arr[i]);
	}
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

void sortIncrease(int* arr, int size)
{
	bool noSwap;

	for (int i = size - 1; i >= 0; i--)
	{
		noSwap = 1;

		for (int j = 0; j < i; j++)
		{
			if (*(arr + j) > *(arr + (j + 1)))
			{
				Replace(&arr[j], &arr[j + 1]);
				noSwap = 0;
			}

		}

		if (noSwap == 1)
			break;
	}
}

void sortDecrease(int* arr, int size)
{
	bool noSwap;

	for (int i = size - 1; i >= 0; i--)
	{
		noSwap = 1;

		for (int j = 0; j < i; j++)
		{
			if (*(arr + j) < *(arr + (j + 1)))
			{
				Replace(&arr[j], &arr[j + 1]);
				noSwap = 0;
			}

		}

		if (noSwap == 1)
			break;
	}
}

void sortAbs(int* arr, int size)
{
	bool noSwap;

	for (int i = size - 1; i >= 0; i--)
	{
		noSwap = 1;

		for (int j = 0; j < i; j++)
		{
			if (abs(*(arr + j)) > abs(*(arr + (j + 1))))
			{
				Replace(&arr[j], &arr[j + 1]);
				noSwap = 0;
			}

		}

		if (noSwap == 1)
			break;
	}
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
	int size = 0;
	printf("Enter size of array: ");
	scanf_s("%d", &size);
	int* arr;
	arr = (int*)malloc(size * sizeof(int));

	initArray(arr, size);
	printf("\n");
	sort_func(arr, size, choose_sort());
	printf("Sorting array: ");
	PrintArray(arr, size);

	free(arr);
}
