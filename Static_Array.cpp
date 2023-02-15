#include <stdio.h>
#include <math.h>
#define MaxSize 20

int arr[MaxSize];
int size;
int* psize = &size;

int Max(int arr[])
{
	int max = arr[0];
	for (int i = 0; i < 10; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
	return max;
}

int Min(int arr[])
{
	int min = arr[0];
	for (int i = 0; i < *psize; i++)
	{
		if (min > arr[i])
			min = arr[i];
	}
	return min;
}


double Mean(int arr[])
{
	double sum = 0;
	for (int i = 0; i < *psize; i++)
		sum += arr[i];
	return sum / *psize;
}

double RMS(int arr[])
{
	double sum = 0;
	for (int i = 0; i < *psize; i++)
		sum += pow(arr[i] - Mean(arr), 2);
	return sqrt(sum / *psize);
}

//Я подумала, что первый способ поиска среднеквадратичного скучноват + в заданиях что-то про массивы написано
//Но по итогу второй способ выглядит как-то не очень
/*
double RMS(int arr[])
{
	double sum = 0;
	double sum_arr[MaxSize] = {};
	for (int i = 0; i < *psize; i++)
		sum_arr[i] = pow(arr[i] - Mean(arr), 2);
	for (int i = 0; i < *psize; i++)
		sum += sum_arr[i];
	return sqrt(sum / *psize);
}
*/

int main()
{
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

	printf("Maximum: %d\n", Max(arr));
	printf("Minimum: %d\n", Min(arr));
	printf("Mean: %.4f\n", Mean(arr));
	printf("RMS: %.4f", RMS(arr));

}



