#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	float data[3][3];
	int xSize;
	int ySize;
} Matrix;

void printMatrix(Matrix* M, const char* nameOperation)
{
	printf("%s\n", nameOperation);
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

Matrix readFileToMatrix(FILE* fp, Matrix* A)
{
	if (fp != NULL)
	{
		for (int row_num = 0; row_num < A->ySize; row_num++)
		{
			for (int col_num = 0; col_num < A->xSize; col_num++)
			{
				fscanf_s(fp, "%f", &A->data[row_num][col_num]);
			}
		}
	}
	else
	{
		printf("File error");
	}
	return *A;
}

void writeTextToFile(FILE* fp, Matrix* A)
{
	for (int row_num = 0; row_num < A->ySize; row_num++)
	{
		for (int col_num = 0; col_num < A->xSize; col_num++)
		{
			fprintf(fp, "%f%c", A->data[row_num][col_num], ' ');
		}
		fprintf(fp, "\n");
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

	//fixed the col and print elements of this col in the row
	for (int col_num = 0; col_num < res.xSize; col_num++)
	{
		for (int row_num = 0; row_num < res.ySize; row_num++)
		{
			res.data[row_num][col_num] = A->data[col_num][row_num];
		}
	}
	return res;
}

float matrixDeterminant(Matrix* A)
{
	float rowReduction;
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

	//Gaussian elimination
	for (int diag_el = 0; diag_el < A->xSize - 1; diag_el++)
	{
		for (int row_num = diag_el + 1; row_num < A->xSize; row_num++)
		{
			if (res.data[diag_el][diag_el] != 0)
			{
				rowReduction = -res.data[row_num][diag_el] / res.data[diag_el][diag_el];
				for (int col_num = 0; col_num < A->xSize; col_num++)
				{
					res.data[row_num][col_num] += res.data[diag_el][col_num] * rowReduction;
				}
			}
		}
	}

	//det of triangular matrix
	for (int i = 0; i < 3; i++)
	{
		det *= res.data[i][i];
	}
	return det;
}

Matrix matrixInversion(Matrix* A)
{
	double temp;

	Matrix res;
	res.xSize = A->xSize;
	res.ySize = A->ySize;
	for (int row_num = 0; row_num < res.ySize; row_num++)
	{
		for (int col_num = 0; col_num < res.xSize; col_num++)
		{
			res.data[row_num][col_num] = 0.0;
			if (row_num == col_num)
				res.data[row_num][col_num] = 1.0;
		}
	}

	Matrix tmp_mat;
	tmp_mat.xSize = A->xSize;
	tmp_mat.ySize = A->ySize;
	for (int row_num = 0; row_num < A->ySize; row_num++)
	{
		for (int col_num = 0; col_num < A->xSize; col_num++)
		{
			tmp_mat.data[row_num][col_num] = A->data[row_num][col_num];
		}
	}

	//solving the equation A * invertible(A) = E
	for (int diag_el = 0; diag_el < res.xSize; diag_el++)
	{
		temp = tmp_mat.data[diag_el][diag_el];

		for (int col_num = 0; col_num < res.xSize; col_num++)
		{
			tmp_mat.data[diag_el][col_num] /= temp;
			res.data[diag_el][col_num] /= temp;
		}

		for (int row_num = diag_el + 1; row_num < res.ySize; row_num++)
		{
			temp = tmp_mat.data[row_num][diag_el];

			for (int col_num = 0; col_num < res.xSize; col_num++)
			{
				tmp_mat.data[row_num][col_num] -= tmp_mat.data[diag_el][col_num] * temp;
				res.data[row_num][col_num] -= res.data[diag_el][col_num] * temp;
			}
		}
	}

	for (int diag_el = res.xSize - 1; diag_el > 0; diag_el--)
	{
		for (int row_num = diag_el - 1; row_num >= 0; row_num--)
		{
			temp = tmp_mat.data[row_num][diag_el];

			for (int col_num = 0; col_num < res.xSize; col_num++)
			{
				tmp_mat.data[row_num][col_num] -= tmp_mat.data[diag_el][col_num] * temp;
				res.data[row_num][col_num] -= res.data[diag_el][col_num] * temp;
			}
		}
	}

	for (int row_num = 0; row_num < res.ySize; row_num++)
	{
		for (int col_num = 0; col_num < res.xSize; col_num++)
		{
			tmp_mat.data[row_num][col_num] = res.data[row_num][col_num];
		}
	}
	return res;
}

Matrix initRandomMatrix(int xSize, int ySize)
{
	Matrix randomMatrix;
	randomMatrix.xSize = xSize;
	randomMatrix.ySize = ySize;

	time_t t;
	srand((unsigned)time(&t));
	for (int row_num = 0; row_num < ySize; row_num++)
	{
		for (int col_num = 0; col_num < xSize; col_num++)
		{
			randomMatrix.data[row_num][col_num] = rand() % 10;
		}
	}
	return randomMatrix;
}

int main()
{
	FILE* fp;
	Matrix A, B;
	int xSize = 3;
	int ySize = 3;
	char fileName[] = "mat_A.txt";

	//initialize mat A
	fopen_s(&fp, fileName, "ab+");
	A.xSize = xSize;
	A.ySize = ySize;
	A = readFileToMatrix(fp, &A);
	fclose(fp);

	//initialize mat B
	B = initRandomMatrix(xSize, ySize);

	//results
	Matrix resSumm = matrixSumm(&A, &B);
	Matrix resMulti = matrixMulti(&A, &B);
	Matrix resTranspose = matrixTranspose(&A);
	float resDeterminant = matrixDeterminant(&A);
	Matrix resInsversion = matrixInversion(&A);
	
	//stdout
	printMatrix(&A, "Matrix A:");
	printMatrix(&B, "Matrix B:");
	printMatrix(&resSumm, "A + B:");
	printMatrix(&resMulti, "A x B:");
	printMatrix(&resTranspose, "Transposed A:");

	printf("Determinant A: %f\n", resDeterminant);
	printf("\n");

	printMatrix(&resInsversion, "Inversion A:");

	//stdin
	fopen_s(&fp, "mat_res.txt", "ab");
	if (fp != NULL)
	{
		fprintf(fp, "%s\n", "A + B:");
		writeTextToFile(fp, &resSumm);

		fprintf(fp, "%s\n", "A x B:");
		writeTextToFile(fp, &resMulti);

		fprintf(fp, "%s\n", "Transposed A:");
		writeTextToFile(fp, &resTranspose);

		fprintf(fp, "Determinant A: %f\n", resDeterminant);

		fprintf(fp, "%s\n", "Inversion A:");
		writeTextToFile(fp, &resInsversion);
	}
	else
	{
		printf("File error");
	}
	fclose(fp);
}
