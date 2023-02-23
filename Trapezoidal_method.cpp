#include <stdio.h>
#include <math.h>

double function(double x)
{
	return x * x ;
}

double CalcIntegral(double (*func)(double), int steps, int lower_lim, double amendment)
{
	double sum = 0;
	for (int i = 0; i < steps - 1; i++)
	{
		sum += ((func(lower_lim + amendment * i) + func(lower_lim + amendment * (i + 1))) / 2) * amendment;
	}
	return sum;
}

int main()
{
	int steps = 0;
	int lower_lim = 0;
	int upper_lim = 0;
	printf("Enter steps: ");
	scanf_s("%d", &steps);
	printf("Enter limits of integration");
	printf("\nlower_lim: ");
	scanf_s("%d", &lower_lim);
	printf("upper_lim: ");
	scanf_s("%d", &upper_lim);
	double amendment = (upper_lim - lower_lim) / (double)steps;
	printf("amendment: %f\n", amendment);
	printf("%f\n", CalcIntegral(function, steps, lower_lim, amendment));
}