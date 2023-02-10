#include <stdio.h>
#include <math.h>

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
