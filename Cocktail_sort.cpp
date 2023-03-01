#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

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

void sortIncrease(int* arr, int size)
{
	int left = 0;
	int right = size - 1;

	do
	{
		for (int i = left; i < right; i++)
		{
			if (*(arr + i) > *(arr + (i + 1)))
				Replace(&arr[i], &arr[i + 1]);
		}

		right--;

		for (int i = right; i > left; i--)
		{
			if (*(arr + (i - 1)) > *(arr + i))
				Replace(&arr[i], &arr[i - 1]);
		}

		left++;
	} while (left <= right);
}

void sortDecrease(int* arr, int size)
{
	int left = 0;
	int right = size - 1;
	do
	{
		for (int i = left; i < right; i++)
		{
			if (*(arr + i) < *(arr + (i + 1)))
				Replace(&arr[i], &arr[i + 1]);
		}

		right--;

		for (int i = right; i > left; i--)
		{
			if (*(arr + (i - 1)) < *(arr + i))
				Replace(&arr[i], &arr[i - 1]);
		}

		left++;
	} while (left <= right);
}

void sortAbs(int* arr, int size)
{
	int left = 0;
	int right = size - 1;
	do
	{
		for (int i = left; i < right; i++)
		{
			if (abs(* (arr + i)) > abs(* (arr + (i + 1))))
				Replace(&arr[i], &arr[i + 1]);
		}

		right--;

		for (int i = right; i > left; i--)
		{
			if (abs(* (arr + (i - 1))) > abs(* (arr + i)))
				Replace(&arr[i], &arr[i - 1]);
		}

		left++;
	} while (left <= right);

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
	srand((unsigned) time(&t)); ///* Intializes random number generator */

	printf("Array: ");
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % (201) + (-100);	
		printf("%d ", arr[i]);
	}
	printf("\n");

	sort_func(arr, size, choose_sort());
	printf("Sorting array: ");
	PrintArray(arr, size);
	free(arr);
}

