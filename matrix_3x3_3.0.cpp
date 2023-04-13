#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	float data[3][3];
	int xSize;
	int ySize;
} Matrix;

void printMatrix(Matrix* M)
{
	for (int row_num = 0; row_num < M->ySize; row_num++)
	{
		for (int col_num = 0; col_num < M->xSize; col_num++)
		{
			printf("%f\t", M->data[row_num][col_num]);
		}
		printf("\n");
	}
	printf("\n");
}

Matrix readFileToMatrix(char* name, int xSize, int ySize)
{
	Matrix A;
	A.xSize = xSize;
	A.ySize = ySize;
	FILE* fp;
	fopen_s(&fp, name, "r");
	for (int row_num = 0; row_num < A.ySize; row_num++)
	{
		for (int col_num = 0; col_num < A.xSize; col_num++)
		{
			fscanf_s(fp, "%f", &A.data[row_num][col_num]);
		}
	}
	fclose(fp);
	return A;
}

void writeTextToFile(FILE* targetFile, Matrix* A)
{
	for (int row_num = 0; row_num < A->ySize; row_num++)
	{
		for (int col_num = 0; col_num < A->xSize; col_num++)
		{
			fprintf(targetFile, "%f\t", A->data[row_num][col_num]);
		}
		fprintf(targetFile, "%c", "\n");
	}
}

Matrix matrixSumm(Matrix* A, Matrix* B)
{
	Matrix res;
	res.xSize = A->xSize;
	res.ySize = A->ySize;
	
	for (int row_num = 0; row_num < A->ySize; row_num++)
	{
		for (int col_num = 0; col_num < A->xSize; col_num++)
		{
			res.data[row_num][col_num] = A->data[row_num][col_num] + B->data[row_num][col_num];
		}
	}
	return res;
}

Matrix matrixMulti(Matrix* A, Matrix* B)
{
	Matrix res;
	res.xSize = B->xSize;
	res.ySize = A->ySize;
	for (int row_num = 0; row_num < res.ySize; row_num++)
	{
		for (int col_num = 0; col_num < res.xSize; col_num++)
		{
			res.data[row_num][col_num] = 0;
		}
	}

	for (int row_num = 0; row_num < A->ySize; row_num++)
	{
		for (int col_num = 0; col_num < A->xSize; col_num++)
		{
			for (int k = 0; k < A->xSize; k++)
			{
				res.data[row_num][col_num] += A->data[row_num][k] * B->data[k][col_num];
			}
		}
	}
	return res;
}

Matrix matrixTranspose(Matrix* A)
{
	Matrix res;
	res.xSize = A->xSize;
	res.ySize = A->ySize;

	for (int col_num = 0; col_num < res.xSize; col_num++) //фиксируем столбец и печатаем элементы этого столбца в строчку
	{
		for (int row_num = 0; row_num < res.ySize; row_num++)
		{
			res.data[row_num][col_num] = A->data[col_num][row_num];
			//fprintf(fp, "%f", res.data[row_num][col_num]); ///вопрос: почему в файл записывает НЕ транспонированную матрицу, а исходную
		}
		//fprintf(fp, "%c", '\n');
	}
	//fprintf(fp, "%c", '\n');
	return res;
}

float matrixDeterminant(Matrix* A)
{
	double reduction;
	float det = 1;

	Matrix res;
	res.xSize = A->xSize;
	res.ySize = A->ySize;
	for (int row_num = 0; row_num < A->ySize; row_num++)
	{
		for (int col_num = 0; col_num < A->xSize; col_num++)
		{
			res.data[row_num][col_num] = A->data[row_num][col_num];
		}
	}

	//приведение матрицы к ступенчатому виду методом гаусса
	for (int diag_el = 0; diag_el < A->xSize - 1; diag_el++)
	{
		for (int row_num = diag_el + 1; row_num < A->xSize; row_num++) // i row_num	j col_num	k diag_el
		{
			if (res.data[diag_el][diag_el] != 0)
			{
				//reduction is ...
				reduction = - res.data[row_num][diag_el] / res.data[diag_el][diag_el];
				for (int col_num = 0; col_num < A->xSize; col_num++)
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

Matrix matrixInversion(Matrix* A) //A N
{
	double temp;
	Matrix res;
	res.xSize = A->xSize;
	res.ySize = A->ySize;
	for (int row_num = 0; row_num < A->ySize; row_num++)
	{
		for (int col_num = 0; col_num < A->xSize; col_num++)
		{
			res.data[row_num][col_num] = A->data[row_num][col_num];
		}
	}

	for (int i = 0; i < res.ySize; i++)
	{
		for (int j = 0; j < res.xSize; j++)
		{
			res.data[i][j] = 0.0;
			if (i == j)
				res.data[i][j] = 1.0;
		}
	}
		
	for (int k = 0; k < res.xSize; k++)
	{
		temp = A->data[k][k];

		for (int j = 0; j < res.xSize; j++)
		{
			A->data[k][j] /= temp;
			res.data[k][j] /= temp;
		}

		for (int i = k + 1; i < res.xSize; i++)
		{
			temp = A->data[i][k];

			for (int j = 0; j < res.xSize; j++)
			{
				A->data[i][j] -= A->data[k][j] * temp;
				res.data[i][j] -= res.data[k][j] * temp;
			}
		}
	}

	for (int k = res.xSize - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A->data[i][k];

			for (int j = 0; j < res.xSize; j++)
			{
				A->data[i][j] -= A->data[k][j] * temp;
				res.data[i][j] -= res.data[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < res.xSize; i++)
	{
		for (int j = 0; j < res.xSize; j++)
		{
			A->data[i][j] = res.data[i][j];
		}
	}

	//fprintf(fp, "%s\n", "inverse A:");
	for (int row_num = 0; row_num < res.ySize; row_num++)
	{
		for (int col_num = 0; col_num < res.xSize; col_num++)
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
	int xSize = 3;
	int ySize = 3;

	//initialize mat A
	char f_name_A[] = "mat_A.txt";
	A = readFileToMatrix(f_name_A, xSize, ySize);
	A.xSize = xSize;
	A.ySize = ySize;

	//initialize mat B
	time_t t;
	srand((unsigned)time(&t));
	for (int row_num = 0; row_num < ySize; row_num++)
	{
		for (int col_num = 0; col_num < xSize; col_num++)
		{
			B.data[row_num][col_num] = rand() % 10;	//(201) + (-100);
		}
	}
	B.xSize = xSize;
	B.ySize = ySize;

	//results of code
	Matrix resSumm = matrixSumm(&A, &B);
	Matrix resMulti = matrixMulti(&A, &B);
	Matrix resTranspose = matrixTranspose(&A);
	float resDeterminant = matrixDeterminant(&A);
	Matrix resInsversion = matrixInversion(&A);

	//stdout
	printf("Matrix A: \n");
	printMatrix(&A);
	printf("Matrix B: \n");
	printMatrix(&B);
	
	printf("A + B: \n");
	printMatrix(&resSumm);

	printf("A x B: \n");
	printMatrix(&resMulti);

	printf("Transposed matrix A: \n");
	printMatrix(&resTranspose);

	printf("Determinant A: %f\n", resDeterminant);

	printf("Inversion A: \n");
	printMatrix(&resInsversion);

	//stdin
	FILE* fp;
	fopen_s(&fp, "mat_res.txt", "a+");
	{
		fprintf(fp, "%s\n", "A + B:");
		writeTextToFile(fp, &resSumm);
		//fprintf(fp, "%c", "\n");

		fprintf(fp, "%s\n", "A x B:");
		writeTextToFile(fp, &resMulti);
		//fprintf(fp, "%c", "\n");

		fprintf(fp, "%s\n", "Transposed A:");
		writeTextToFile(fp, &resTranspose);
		//fprintf(fp, "%c", "\n");

		fprintf(fp, "%f\n", resDeterminant);

		fprintf(fp, "%s\n", "Inverse A:");
		writeTextToFile(fp, &resInsversion);
		//fprintf(fp, "%c", "\n");
	}
	fclose(fp);
}
