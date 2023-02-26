#include <stdio.h>
#include <math.h>
#define MaxSize 20

int arr[MaxSize];

int Max(int arr[], int size)
{
	int max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
	return max;
}

int Min(int arr[], int size)
{
	int min = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (min > arr[i])
			min = arr[i];
	}
	return min;
}


double Mean(int arr[], int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum += arr[i];
	return sum / size;
}

double RMS(int arr[], int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum += pow(arr[i] - Mean(arr, size), 2);
	return sqrt(sum / size);
}

int main()
{
	int size;
	while (1)
	{
		printf("Enter size of array: ");
		scanf_s("%d", &size);
		if (size < MaxSize)
			break;
		else
			printf("Size can't be more than MaxSize\n");
	}
	
	for (int i = 0; i < size; i++) //инициализируем элементы массива
	{
		scanf_s("%d", &arr[i]);
	}
	
	printf("Our array: ");
	for (int i = 0; i < size; i++) //печатаем массив
	{
		printf("%d\t", arr[i]);
	}

	printf("\r\n");

	printf("Maximum: %d\n", Max(arr, size));
	printf("Minimum: %d\n", Min(arr, size));
	printf("Mean: %.4f\n", Mean(arr, size));
	printf("RMS: %.4f", RMS(arr, size));

}
