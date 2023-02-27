#include <stdio.h>
#include <math.h>

double function(double x)
{
	return x * x ;
}

double CalcIntegral(double (*func)(double), double lower_lim, double upper_lim, int steps_number)
{
	double sum = 0;
	double dx = (upper_lim - lower_lim) / steps_number;
	for (int i = 0; i <= steps_number - 1; i++)
	{
		sum += ((func(lower_lim + dx * i) + func(lower_lim + dx * (i + 1))) / 2) * dx;
	}
	return sum;
}

int main()
{
	int steps_number = 0;
	double lower_lim = 0;
	double upper_lim = 0;
	printf("Enter steps: ");
	scanf_s("%d", &steps_number);
	printf("Enter limits of integration");
	printf("\nlower_lim: ");
	scanf_s("%lf", &lower_lim);
	printf("upper_lim: ");
	scanf_s("%lf", &upper_lim);
	printf("%f\n", CalcIntegral(function, lower_lim, upper_lim, steps_number));
}
