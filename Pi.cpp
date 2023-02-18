#include <stdio.h>
#include <math.h>

double function(double x) //задаем функцию
{
	return x * x - 1;
}

double deriv(double (*func)(double), double x, double dx) //считаем производную
{
	return (func(x + dx) - func(x - dx)) / (2 * dx);
}

double solve_eq(double (*func)(double), double x0, double dx)
{
	double x1;
	do
	{
		x1 = x0 - (func(x0) / deriv(func, x0, dx));
		x0 = x1;

	} while (fabs(func(x1)) > pow(10, -6));
	return x1;
}


int main()
{
	double x0 = 1;
	double dx = 0.1;

	//printf("Enter approximate root: ");
	//scanf_s("%f", &x0);
	printf("%.10f", solve_eq(function, x0, dx));
}
