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


int Prime(int a)	//возвращает 1 - число простое, 0 - не простое
{
	int k = 0;
	int i;
	for (i = 2; i <= int(sqrt(double(a))); i++)
	{
		if (a % i == 0) {
			k = k + 1;
		}
	}
	if (k >= 1)
		return 0;
	else
		return 1;
}

void main() {
	int N = 0;
	int P;
	int j;
	printf("Enter N: ");
	scanf_s("%d", &N);

	for (j = 2; j <= N; j++)
	{
		P = Prime(j);
		if (P == 1)
			printf("%d\n", j);
	}
}
