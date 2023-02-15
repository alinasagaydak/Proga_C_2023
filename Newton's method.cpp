#include <stdio.h>
#include <math.h>

double function(double x) //задаем функцию
{
	return x * x - sin(10 * x);
}

double deriv(double (*func)(double), double x, double h) //считаем производную
{
	return (func(x + h) - func(x - h)) / (2 * h);
}

int main()
{
	double h = 0.1;
	double x0 = 3;
	double x1;
	int prec = 0;
	double amendment; //поправка

	printf("Enter precision: ");
	scanf_s("%d", &prec);

	do
	{
		amendment = (-1) * (function(x0) / deriv(function, x0, h));
		x1 = x0 + amendment;
		if (function(x1) == 0)
			break;
		x0 = x1;

	} while (fabs(function(x1)) > pow(10, -(prec)));
	printf("%f", x1);
}
