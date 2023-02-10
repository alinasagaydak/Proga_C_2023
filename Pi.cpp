#include <stdio.h>
#include <math.h>

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
