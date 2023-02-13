#include <stdio.h>
#include <math.h>

/*
int main() {
	int a = 0;
	int b = 0;
	printf("Enter a: ");
	scanf_s("%d", & a, sizeof(int));
	printf("Enter b: ");
	scanf_s("%d", & b, sizeof(int));
	printf("a+b= %d\n", a + b);
}
*/


/*
int main() {
	int a = 0;
	float b = 0;
	printf("enter a: ");
	scanf_s("%d", &a);
	printf("enter b: ");
	scanf_s("%f", &b);
	printf("a=%d, b=%f\n", a, b);
}
*/

/*
int main() {
	int a = 0;
	printf("Enter a: ");
	scanf_s("%d", &a);
	printf("%d", a*a);
}
*/

/* Zadacha 1
int main() {
	int a = 0;
	int b = 0;
	int c = 0;
	double disc;
	double x_1;
	double x_2;
	printf("Enter a: ");
	scanf_s("%d", &a);
	printf("Enter b: ");
	scanf_s("%d", &b);
	printf("Enter c: ");
	scanf_s("%d", &c);

	if (a == 0) {
		x_1 =  - double(c) / double(b);
		printf("Linear equation, x = %f\n", x_1);
	}

	else {
		disc = b * b - 4 * a * c;
		if (disc < 0)
		{
			printf("disc = %f\n", disc);
			printf("No solutions");
		}
		else if (disc == 0){
			x_1 = -b / (2 * a);
			printf("x1 = %f", x_1);
		}

		if (disc > 0){
			printf("disc = %f\n", disc);
			x_1 = (-b + sqrt(disc)) / (2 * a);
			x_2 = (-b - sqrt(disc)) / (2 * a);
			printf("x1 = %f, x2 = %f\n", x_1, x_2);
		}
	}

}
*/


/*
int isPrime(int a)	//возвращает 1 - число простое, 0 - не простое
{
	for (int i = 2; i <= sqrt(a); i++)
	{
		if (a % i == 0) {
			return 0;
		}
	}
	return 1;
}

void main() {
	int N = 0;
	printf("Enter N: ");
	scanf_s("%d", &N);

	for (int num = 2; num <= N; num++)
	{
		if (isPrime(num) == 1)
			printf("%d\n", num);
	}
}
*/

/*К счастью, данный конкретный ряд позволяет найти очень простое правило, позволяющее определить момент,
когда следует прекратить суммирование. Дело в том, что ряд Грегори является знакопеременным и сходится 
равномерно (хотя и медленнее, чем хотелось бы). Это означает, что для любого нечетного n, сумма первых 
n членов ряда всегда дает верхнюю оценку для PI, а сумма n+1 первых членов ряда - нижнюю.*/



/*
void main()
{
	double s_up = 0; //верхняя сумма
	double s_down = 0; //нижняя сумма
	int i = 0;
	int prec = 0; //точность
	printf("Enter precision: ");
	scanf_s("%d", &prec);

	do
	{
		if (i % 2 == 0)
		{
			s_up = s_down + (double)4 / (2 * i + 1);
		}
		else
		{
			s_down = s_up - (double)4 / (2 * i + 1);
		}
		i++;
	}
	while (fabs(s_up - s_down) > pow(10, -(prec)));
	printf(" % .*f\n", prec, (s_up + s_down) / 2);

}
*/


double func(double x) //задаем функцию
{
	return x*x - sin(10*x);
}

double deriv(double x, double h) //считаем производную
{
	return (func(x + h) - func(x - h)) / (2 * h);
}

void main()
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
		amendment = (-1) * (func(x0) / deriv(x0, h));
		x1 = x0 + amendment;
		if (func(x1) == 0)
			break;
		x0 = x1;

	} while (fabs(func(x1)) > pow(10, -(prec)));
	printf("%f", x1);
}