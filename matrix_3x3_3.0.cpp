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

Matrix readFileToMatrix(char* fileName, int xSize, int ySize)
{
	Matrix A;
	A.xSize = xSize;
	A.ySize = ySize;
	FILE* fp;
	fopen_s(&fp, fileName, "ab+");
	if (fp != NULL)
	{
		for (int row_num = 0; row_num < A.ySize; row_num++)
		{
			for (int col_num = 0; col_num < A.xSize; col_num++)
			{
				fscanf_s(fp, "%f", &A.data[row_num][col_num]);
			}
		}
	}
	else
	{
		printf("File error");
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
		fprintf(targetFile, "\n");
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
				rowReduction = - res.data[row_num][diag_el] / res.data[diag_el][diag_el];
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
	for (int row_num = 0; row_num < A->ySize; row_num++)
	{
		for (int col_num = 0; col_num < A->xSize; col_num++)
		{
			res.data[row_num][col_num] = A->data[row_num][col_num];
		}
	}
	//create identity matrix
	for (int row_num = 0; row_num < res.ySize; row_num++)
	{
		for (int col_num = 0; col_num < res.xSize; col_num++)
		{
			res.data[row_num][col_num] = 0.0;
			if (row_num == col_num)
				res.data[row_num][col_num] = 1.0;
		}
	}
	//solving the equation A * invertible(A) = E
	for (int diag_el = 0; diag_el < res.xSize; diag_el++)
	{
		temp = A->data[diag_el][diag_el];

		for (int col_num = 0; col_num < res.xSize; col_num++)
		{
			A->data[diag_el][col_num] /= temp;
			res.data[diag_el][col_num] /= temp;
		}

		for (int row_num = diag_el + 1; row_num < res.ySize; row_num++)
		{
			temp = A->data[row_num][diag_el];

			for (int col_num = 0; col_num < res.xSize; col_num++)
			{
				A->data[row_num][col_num] -= A->data[diag_el][col_num] * temp;
				res.data[row_num][col_num] -= res.data[diag_el][col_num] * temp;
			}
		}
	}

	for (int diag_el = res.xSize - 1; diag_el > 0; diag_el--)
	{
		for (int row_num = diag_el - 1; row_num >= 0; row_num--)
		{
			temp = A->data[row_num][diag_el];

			for (int col_num = 0; col_num < res.xSize; col_num++)
			{
				A->data[row_num][col_num] -= A->data[diag_el][col_num] * temp;
				res.data[row_num][col_num] -= res.data[diag_el][col_num] * temp;
			}
		}
	}

	for (int row_num = 0; row_num < res.ySize; row_num++)
	{
		for (int col_num = 0; col_num < res.xSize; col_num++)
		{
			A->data[row_num][col_num] = res.data[row_num][col_num];
		}
	}
	return res;
}

int main()
{
	Matrix A, B;
	int xSize = 3;
	int ySize = 3;

	//initialize mat A
	char fileName[] = "mat_A.txt";
	A = readFileToMatrix(fileName, xSize, ySize);
	A.xSize = xSize;
	A.ySize = ySize;

	//initialize mat B
	time_t t;
	srand((unsigned)time(&t));
	for (int row_num = 0; row_num < ySize; row_num++)
	{
		for (int col_num = 0; col_num < xSize; col_num++)
		{
			B.data[row_num][col_num] = rand() % 10;
		}
	}
	B.xSize = xSize;
	B.ySize = ySize;

	//results
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
	printf("\n");

	printf("Inversion A: \n");
	printMatrix(&resInsversion);

	//stdin
	FILE* fp;
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

		fprintf(fp, "%s\n", "Invertible A:");
		writeTextToFile(fp, &resInsversion);
	}
	else
	{
		printf("File error");
	}
	fclose(fp);
}
