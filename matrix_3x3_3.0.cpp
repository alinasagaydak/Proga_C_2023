#include <stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct
{
	float data[3][3];
	int width;
	int height;
} Matrix;

void print_matrix(Matrix* M)
{
	for (int row_num = 0; row_num < M->height; row_num++)
	{
		for (int col_num = 0; col_num < M->width; col_num++)
		{
			printf("%f\t", M->data[row_num][col_num]);
		}
		printf("\n");
	}
	printf("\n");
}

Matrix READ_mat(char* name, int width, int height)
{
	Matrix A;
	A.width = width;
	A.height = height;
	FILE* fp;
	fopen_s(&fp, name, "r");
	for (int row_num = 0; row_num < A.height; row_num++)
	{
		for (int col_num = 0; col_num < A.width; col_num++)
		{
			fscanf_s(fp, "%f", &A.data[row_num][col_num]);
		}
	}
	fclose(fp);
	return A;
}

void WRITE_to_file(void* A, int operation)
{
	FILE* fp;

	if (sizeof(A) == 4)
	{
		fopen_s(&fp, "mat_res.txt", "a+");
		{
			fprintf(fp, "%c", "\n");
			fprintf(fp, "%s", "Det A:");
			fprintf(fp, "%f", *(float*)A);
		}
		fclose(fp);
	}

	else
	{
		switch (operation)
		{
		case 1:
			fopen_s(&fp, "mat_res.txt", "a+");
			fprintf(fp, "%c", "\n");
			fprintf(fp, "%s", "A + B");
			fclose(fp);
			break;
		case 2:
			fopen_s(&fp, "mat_res.txt", "a+");
			fprintf(fp, "%c", "\n");
			fprintf(fp, "%s", "A x B");
			fclose(fp);
			break;
		case 3:
			fopen_s(&fp, "mat_res.txt", "a+");
			fprintf(fp, "%c", "\n");
			fprintf(fp, "%s", "transposed A");
			fclose(fp);
			break;
		case 4:
			fopen_s(&fp, "mat_res.txt", "a+");
			fprintf(fp, "%c", "\n");
			fprintf(fp, "%s", "inverse A");
			fclose(fp);
			break;
		}

		fopen_s(&fp, "mat_res.txt", "a+");
		fprintf(fp, "%c", "\n");
		for (int row_num = 0; row_num < ((Matrix*)A)->height; row_num++)
		{
			for (int col_num = 0; col_num < ((Matrix*)A)->width; col_num++)
			{
				fprintf(fp, "%f\t", ((Matrix*)A)->data[row_num][col_num]);
			}
			fprintf(fp, "%c", "\n");
		}
		//fprintf(fp, "%c", "\n");
		fclose(fp);
	}
}

Matrix summ(Matrix* A, Matrix* B)
{
	Matrix res;
	res.width = A->width;
	res.height = A->height;
	
	for (int row_num = 0; row_num < A->height; row_num++)
	{
		for (int col_num = 0; col_num < A->width; col_num++)
		{
			res.data[row_num][col_num] = A->data[row_num][col_num] + B->data[row_num][col_num];
		}
	}
	return res;
}

Matrix multiplication(Matrix* A, Matrix* B)
{
	Matrix res;
	res.width = B->width;
	res.height = A->height;
	for (int row_num = 0; row_num < res.height; row_num++)
	{
		for (int col_num = 0; col_num < res.width; col_num++)
		{
			res.data[row_num][col_num] = 0;
		}
	}

	for (int row_num = 0; row_num < A->height; row_num++)
	{
		for (int col_num = 0; col_num < A->width; col_num++)
		{
			for (int k = 0; k < A->width; k++)
			{
				res.data[row_num][col_num] += A->data[row_num][k] * B->data[k][col_num];
			}
		}
	}
	return res;
}

Matrix transpose(Matrix* A)
{
	Matrix res;
	res.width = A->width;
	res.height = A->height;

	for (int col_num = 0; col_num < res.width; col_num++) //фиксируем столбец и печатаем элементы этого столбца в строчку
	{
		for (int row_num = 0; row_num < res.height; row_num++)
		{
			res.data[row_num][col_num] = A->data[col_num][row_num];
			//fprintf(fp, "%f", res.data[row_num][col_num]); ///вопрос: почему в файл записывает НЕ транспонированную матрицу, а исходную
		}
		//fprintf(fp, "%c", '\n');
	}
	//fprintf(fp, "%c", '\n');
	return res;
}

float findDet(Matrix* A)
{
	double reduction;
	float det = 1;

	Matrix res;
	res.width = A->width;
	res.height = A->height;
	for (int row_num = 0; row_num < A->height; row_num++)
	{
		for (int col_num = 0; col_num < A->width; col_num++)
		{
			res.data[row_num][col_num] = A->data[row_num][col_num];
		}
	}

	//приведение матрицы к ступенчатому виду методом гаусса
	for (int diag_el = 0; diag_el < A->width - 1; diag_el++)
	{
		for (int row_num = diag_el + 1; row_num < A->width; row_num++) // i row_num	j col_num	k diag_el
		{
			if (res.data[diag_el][diag_el] != 0)
			{
				//reduction is ...
				reduction = - res.data[row_num][diag_el] / res.data[diag_el][diag_el];
				for (int col_num = 0; col_num < A->width; col_num++)
				{
					res.data[row_num][col_num] += res.data[diag_el][col_num] * reduction;
				}
			}

		}
	}
	//fprintf(fp, "%s\n", "det A:");
	//det верхнетреугольной матрицы
	for (int i = 0; i < 3; i++) 
	{
		det *= res.data[i][i];
	}
	//fprintf(fp, "%f\n", det);
	//fprintf(fp, "%c", '\n');
	return det;
}

Matrix inversion(Matrix* A) //A N
{
	double temp;
	Matrix res;
	res.width = A->width;
	res.height = A->height;
	for (int row_num = 0; row_num < A->height; row_num++)
	{
		for (int col_num = 0; col_num < A->width; col_num++)
		{
			res.data[row_num][col_num] = A->data[row_num][col_num];
		}
	}

	for (int i = 0; i < res.height; i++)
	{
		for (int j = 0; j < res.width; j++)
		{
			res.data[i][j] = 0.0;
			if (i == j)
				res.data[i][j] = 1.0;
		}
	}
		
	for (int k = 0; k < res.width; k++)
	{
		temp = A->data[k][k];

		for (int j = 0; j < res.width; j++)
		{
			A->data[k][j] /= temp;
			res.data[k][j] /= temp;
		}

		for (int i = k + 1; i < res.width; i++)
		{
			temp = A->data[i][k];

			for (int j = 0; j < res.width; j++)
			{
				A->data[i][j] -= A->data[k][j] * temp;
				res.data[i][j] -= res.data[k][j] * temp;
			}
		}
	}

	for (int k = res.width - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A->data[i][k];

			for (int j = 0; j < res.width; j++)
			{
				A->data[i][j] -= A->data[k][j] * temp;
				res.data[i][j] -= res.data[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < res.width; i++)
	{
		for (int j = 0; j < res.width; j++)
		{
			A->data[i][j] = res.data[i][j];
		}
	}

	//fprintf(fp, "%s\n", "inverse A:");
	for (int row_num = 0; row_num < res.height; row_num++)
	{
		for (int col_num = 0; col_num < res.width; col_num++)
		{
			//fprintf(fp, "%f\t", res.data[row_num][col_num]);
		}
		//fprintf(fp, "%c", "\n");
	}
	//fprintf(fp, "%c", "\n");
	return res;
}

int main()
{
	Matrix A, B;
	int width = 3;
	int height = 3;

	//initialize mat A
	char f_name_A[] = "mat_A.txt";
	A = READ_mat(f_name_A, width, height);
	A.width = width;
	A.height = height;

	//initialize mat B
	time_t t;
	srand((unsigned)time(&t));
	for (int row_num = 0; row_num < height; row_num++)
	{
		for (int col_num = 0; col_num < width; col_num++)
		{
			B.data[row_num][col_num] = rand() % 10;	//(201) + (-100);
		}
	}
	B.width = width;
	B.height = height;

	printf("Matrix A: \n");
	print_matrix(&A);
	printf("Matrix B: \n");
	print_matrix(&B);
	
	printf("A + B: \n");
	Matrix Sum = summ(&A, &B);
	print_matrix(&Sum);
	WRITE_to_file(&Sum, 1);

	printf("A x B: \n");
	Matrix multi = multiplication(&A, &B);
	print_matrix(&multi);
	WRITE_to_file(&multi, 2);

	printf("Transpose matrix A: \n");
	Matrix trans = transpose(&A);
	print_matrix(&trans);
	WRITE_to_file(&trans, 3);

	float det = findDet(&A);
	printf("Determinant A: %f\n", det);
	printf("\n");
	WRITE_to_file(&det, 0);

	printf("Inversion A: \n");
	Matrix ins = inversion(&A);
	print_matrix(&ins);
	WRITE_to_file(&ins, 4);
}
