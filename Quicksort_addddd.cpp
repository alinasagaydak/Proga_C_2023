#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<time.h>
#include <math.h>

int choose_sort()
{
	int sort_type = 0;
	printf("-1 - sortIncrease\n1 - sortDecrease\n");
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

int Compare(int a, int b)
{
	if (a < b) return -1;
	if (a == b) return 0;
	if (a > b) return 1;
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

void qsort(int* arr, int size, int sort_type)
{
	int left = 0;
	int right = size - 1;
	int pivot = define_pivot(arr, size);

	do
	{
		while (Compare(arr[left], pivot) == sort_type) //////
			left++;
		while (Compare(arr[right], pivot) == -sort_type) /////
			right--;
		if (left <= right)
		{
			Replace(&arr[left], &arr[right]);
			left++;
			right--;
		}
	} while (left <= right);
	if (right > 0)
		qsort(arr, right + 1, sort_type);

	if (left < size)
		qsort(&arr[left], size - left, sort_type);
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

	
	printf("\n");
	qsort(arr, size, choose_sort());
	printf("\n");
	printf("Sorting array: ");
	PrintArray(arr, size);

	free(arr);
}