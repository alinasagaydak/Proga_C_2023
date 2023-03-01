#include <stdio.h>
#include <math.h>
#include <malloc.h>

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
	printf("\n");
	printf("Array: ");
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

void sort_func(int* arr, int size, int sort_type)
{
	bool noSwap;

	for (int i = size - 1; i >= 0; i--)
	{
		noSwap = 1;

		if (sort_type == 1) //increase
		{
			for (int j = 0; j < i; j++)
			{
				if (*(arr + j) > *(arr + (j + 1)))
				{
					Replace(&arr[j], &arr[j + 1]);
					noSwap = 0;
				}

			}
		}

		else if(sort_type == 2) //decrease
		{
			for (int j = 0; j < i; j++)
			{
				if (*(arr + j) < *(arr + (j + 1)))
				{
					Replace(&arr[j], &arr[j + 1]);
					noSwap = 0;
				}
			}
		}

		else //abs
		{
			for (int j = 0; j < i; j++)
			{
				if (abs(*(arr + j)) > abs(*(arr + (j + 1))))
				{
					Replace(&arr[j], &arr[j + 1]);
					noSwap = 0;
				}
			}
		}

		if (noSwap == 1)
			break;
	}

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
	printf("1 - sortIncrease\n2 - sortDecrease\n3 - sortAbs\n");
	int sort_type = 0;
	printf("Choose the sorting method: ");
	scanf_s("%d", &sort_type);

	sort_func(arr, size, sort_type);
	PrintArray(arr, size);

	free(arr);
}
