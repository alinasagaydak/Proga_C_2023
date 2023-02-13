#include <stdio.h>
#include <math.h>

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
