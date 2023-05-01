#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

typedef struct
{
	float* data;
	int xSize;
	int ySize;
} Matrix;

void readMatrixFromFile(FILE* fp, Matrix* matA)
{
	if (fp != NULL)
	{
		for (int rowNum = 0; rowNum < matA->ySize; rowNum++)
		{
			for (int colNum = 0; colNum < matA->xSize; colNum++)
			{
				fscanf_s(fp, "%f", (matA->data + rowNum * matA->xSize + colNum));
			}
		}
	}
	else printf("File error");
}

void fillRandomMatrix(Matrix* matA)
{
	time_t t;
	srand((unsigned)time(&t));

	for (int rowNum = 0; rowNum < matA->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matA->xSize; colNum++)
		{
			*(matA->data + rowNum * matA->xSize + colNum) = rand() % 10;
		}
	}
}

void fillMatrixFromFile(Matrix* matA)
{
	FILE* fp;
	char fileName[] = "matB.txt";

	fopen_s(&fp, fileName, "ab+");
	{
		if (fp != NULL) readMatrixFromFile(fp, matA);
		else
		{
			printf("File error");
			exit(1);
		}
	}
	fclose(fp);
}

void printMatrix(FILE* stream, Matrix* matA)
{
	for (int rowNum = 0; rowNum < matA->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matA->xSize; colNum++)
		{
			fprintf(stream, "%f\t", *(matA->data + rowNum * matA->xSize + colNum));
		}
		fprintf(stream, "\n");
	}
	fprintf(stream, "\n");
}

void createIdenticalMatrix(Matrix* matA, Matrix* matRes)
{
	for (int rowNum = 0; rowNum < matRes->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes->xSize; colNum++)
		{
			*(matRes->data + rowNum * matRes->xSize + colNum) = *(matA->data + rowNum * matA->xSize + colNum);
		}
	}
}

void createZeroMatrix(Matrix* matRes)
{
	for (int rowNum = 0; rowNum < matRes->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes->xSize; colNum++)
		{
			*(matRes->data + rowNum * matRes->xSize + colNum) = 0;
		}
	}
}

void createIdentityMatrix(Matrix* matRes)
{
	for (int rowNum = 0; rowNum < matRes->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes->xSize; colNum++)
		{
			*(matRes->data + rowNum * matRes->xSize + colNum) = 0.0;
			if (rowNum == colNum)
				*(matRes->data + rowNum * matRes->xSize + colNum) = 1.0;
		}
	}
}

void matrixSumm(Matrix* matA, Matrix* matB, Matrix* matRes)
{
	createIdenticalMatrix(matA, matRes);

	for (int rowNum = 0; rowNum < matRes->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes->xSize; colNum++)
		{
			*(matRes->data + rowNum * matRes->xSize + colNum) += *(matB->data + rowNum * matB->xSize + colNum);
		}
	}
}

void matrixMultiplication(Matrix* matA, Matrix* matB, Matrix* matRes)
{
	createZeroMatrix(matRes);

	for (int rowNum = 0; rowNum < matRes->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes->xSize; colNum++)
		{
			for (int k = 0; k < matA->xSize; k++)
			{
				*(matRes->data + rowNum * matRes->xSize + colNum) += *(matA->data + rowNum * matA->xSize + k) * *(matB->data + k * matB->xSize + colNum);
			}
		}
	}
}

void matrixTranspose(Matrix* matA, Matrix* matRes)
{
	createZeroMatrix(matRes);

	for (int rowNum = 0; rowNum < matRes->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes->xSize; colNum++)
		{
			*(matRes->data + rowNum * matRes->xSize + colNum) = *(matA->data + colNum * matA->xSize + rowNum);
		}
	}
}

float matrixDeterminant(Matrix* matA, Matrix* matRes)
{
	createIdenticalMatrix(matA, matRes);
	float rowReduction = 0;
	float det = 1;

	for (int diagEl = 0; diagEl < matRes->xSize; diagEl++)
	{
		for (int rowNum = diagEl + 1; rowNum < matRes->ySize; rowNum++)
		{
			if (*(matRes->data + diagEl * matRes->xSize + diagEl) != 0)
			{
				rowReduction = -*(matRes->data + rowNum * matRes->xSize + diagEl) / *(matRes->data + diagEl * matRes->xSize + diagEl);
				for (int colNum = 0; colNum < matRes->xSize; colNum++)
				{
					*(matRes->data + rowNum * matRes->xSize + colNum) += *(matRes->data + diagEl * matRes->xSize + colNum) * rowReduction;
				}
			}
		}
	}

	for (int diagEl = 0; diagEl < matRes->ySize; diagEl++)
	{
		det *= *(matRes->data + diagEl * matRes->xSize + diagEl);
	}
	return det;
}

void matrixInversion(Matrix* matA, Matrix* matRes)
{
	float rowReduction = 0;
	createIdentityMatrix(matRes);
	Matrix matTmp;
	matTmp.xSize = matA->xSize;
	matTmp.ySize = matA->ySize;
	matTmp.data = (float*)malloc(matTmp.xSize * matTmp.ySize * sizeof(float));
	createIdenticalMatrix(matA, &matTmp);

	for (int diagEl = 0; diagEl < matTmp.xSize; diagEl++)
	{
		for (int rowNum = diagEl + 1; rowNum < matTmp.ySize; rowNum++)
		{
			if (*(matTmp.data + diagEl * matTmp.xSize + diagEl) != 0)
			{
				rowReduction = -*(matTmp.data + rowNum * matTmp.xSize + diagEl) / *(matTmp.data + diagEl * matTmp.xSize + diagEl);
				for (int colNum = 0; colNum < matTmp.xSize; colNum++)
				{
					*(matTmp.data + rowNum * matTmp.xSize + colNum) += *(matTmp.data + diagEl * matTmp.xSize + colNum) * rowReduction;
					*(matRes->data + rowNum * matRes->xSize + colNum) += *(matRes->data + diagEl * matRes->xSize + colNum) * rowReduction;
				}
			}
		}
	}

	for (int diagEl = matTmp.xSize - 1; diagEl > 0; diagEl--)
	{
		for (int rowNum = diagEl - 1; rowNum >= 0; rowNum--)
		{
			if (*(matTmp.data + diagEl * matTmp.xSize + diagEl) != 0)
			{
				rowReduction = -*(matTmp.data + rowNum * matTmp.xSize + diagEl) / *(matTmp.data + diagEl * matTmp.xSize + diagEl);
				for (int colNum = matTmp.xSize - 1; colNum >= 0; colNum--)
				{
					*(matTmp.data + rowNum * matTmp.xSize + colNum) += *(matTmp.data + diagEl * matTmp.xSize + colNum) * rowReduction;
					*(matRes->data + rowNum * matRes->xSize + colNum) += *(matRes->data + diagEl * matRes->xSize + colNum) * rowReduction;
				}
			}
		}
	}

	for (int rowNum = 0; rowNum < matRes->ySize; rowNum++)
	{
		float temp = *(matTmp.data + rowNum * matTmp.xSize + rowNum);
		for (int colNum = 0; colNum < matRes->xSize; colNum++)
		{
			*(matRes->data + rowNum * matRes->xSize + colNum) /= temp;
		}
	}

	free(matTmp.data);
}

void test_summ()
{
	Matrix matA;
	Matrix matB;
	Matrix matRes;

	matA.xSize = 3;
	matA.ySize = 3;
	matA.data = (float*)malloc(matA.xSize * matA.ySize * sizeof(float));
	for (int rowNum = 0; rowNum < matA.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matA.xSize; colNum++)
		{
			*(matA.data + rowNum * matA.xSize + colNum) = 1;
		}
	}

	matB.xSize = 3;
	matB.ySize = 3;
	matB.data = (float*)malloc(matB.xSize * matB.ySize * sizeof(float));
	for (int rowNum = 0; rowNum < matB.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matB.xSize; colNum++)
		{
			*(matB.data + rowNum * matB.xSize + colNum) = 2;
		}
	}

	matRes.xSize = 3;
	matRes.ySize = 3;
	matRes.data = (float*)malloc(matRes.xSize * matRes.ySize * sizeof(float));

	matrixSumm(&matA, &matB, &matRes);

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			if (*(matRes.data + rowNum * matRes.xSize + colNum) != 3)
			{
				printf("Error. matrixSumm doesn't work correct\n");
				exit(1);
			}
		}
	}

	free(matA.data);
	free(matB.data);
	free(matRes.data);
}

void test_multiplication()
{
	Matrix matA;
	Matrix matB;
	Matrix matRes;

	matA.xSize = 3;
	matA.ySize = 3;
	matA.data = (float*)malloc(matA.xSize * matA.ySize * sizeof(float));
	for (int rowNum = 0; rowNum < matA.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matA.xSize; colNum++)
		{
			*(matA.data + rowNum * matA.xSize + colNum) = 1;
		}
	}

	matB.xSize = 3;
	matB.ySize = 3;
	matB.data = (float*)malloc(matB.xSize * matB.ySize * sizeof(float));
	for (int rowNum = 0; rowNum < matB.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matB.xSize; colNum++)
		{
			*(matB.data + rowNum * matB.xSize + colNum) = 2;
		}
	}

	matRes.xSize = 3;
	matRes.ySize = 3;
	matRes.data = (float*)malloc(matRes.xSize * matRes.ySize * sizeof(float));

	matrixMultiplication(&matA, &matB, &matRes);

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			if (*(matRes.data + rowNum * matRes.xSize + colNum) != 6)
			{
				printf("Error. matrixMultiplication doesn't work correct\n");
				exit(1);
			}
		}
	}

	free(matA.data);
	free(matB.data);
	free(matRes.data);
}

void test_determinant()
{
	Matrix matA;
	Matrix matRes;

	matA.xSize = 3;
	matA.ySize = 3;
	matA.data = (float*)malloc(matA.xSize * matA.ySize * sizeof(float));
	{
		*(matA.data + 0 * matA.xSize + 0) = 2;
		*(matA.data + 0 * matA.xSize + 1) = 0;
		*(matA.data + 0 * matA.xSize + 2) = 1;
		*(matA.data + 1 * matA.xSize + 0) = 4;
		*(matA.data + 1 * matA.xSize + 1) = 5;
		*(matA.data + 1 * matA.xSize + 2) = 0;
		*(matA.data + 2 * matA.xSize + 0) = 1;
		*(matA.data + 2 * matA.xSize + 1) = 0;
		*(matA.data + 2 * matA.xSize + 2) = 1;
	}

	matRes.xSize = 3;
	matRes.ySize = 3;
	matRes.data = (float*)malloc(matRes.xSize * matRes.ySize * sizeof(float));

	if (matrixDeterminant(&matA, &matRes) != 5.0)
	{
		printf("Error. matrixDeterminant doesn't work correct\n");
		exit(1);
	}

	free(matA.data);
	free(matRes.data);
}

void test_inversion()
{
	Matrix matA;
	Matrix matRes;

	matA.xSize = 3;
	matA.ySize = 3;
	matA.data = (float*)malloc(matA.xSize * matA.ySize * sizeof(float));
	{
		*(matA.data + 0 * matA.xSize + 0) = 2;
		*(matA.data + 0 * matA.xSize + 1) = 0;
		*(matA.data + 0 * matA.xSize + 2) = 1;
		*(matA.data + 1 * matA.xSize + 0) = 4;
		*(matA.data + 1 * matA.xSize + 1) = 5;
		*(matA.data + 1 * matA.xSize + 2) = 0;
		*(matA.data + 2 * matA.xSize + 0) = 1;
		*(matA.data + 2 * matA.xSize + 1) = 0;
		*(matA.data + 2 * matA.xSize + 2) = 1;
	}
	
	matRes.xSize = 3;
	matRes.ySize = 3;
	matRes.data = (float*)malloc(matRes.xSize * matRes.ySize * sizeof(float));

	float expectedResult[3][3] = { {1, 0, -1}, {-0.8, 0.2, 0.8}, {-1, 0, 2} };

	matrixInversion(&matA, &matRes);

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			if (*(matRes.data + rowNum * matRes.xSize + colNum) != expectedResult[rowNum][colNum])
			{
				printf("Error. matrixInversion doesn't work correct\n");
				exit(1);
			}
		}
	}

	free(matA.data);
	free(matRes.data);
}

int main()
{
	test_summ();
	test_multiplication();
	test_determinant();
	test_inversion();

	Matrix matA;
	Matrix matB;
	Matrix matRes;
	int xSize = 3;
	int ySize = 3;

	matA.xSize = xSize;
	matA.ySize = ySize;
	matA.data = (float*)malloc(matA.xSize * matA.ySize * sizeof(float));
	fillRandomMatrix(&matA);

	matB.xSize = xSize;
	matB.ySize = ySize;
	matB.data = (float*)malloc(matB.xSize * matB.ySize * sizeof(float));
	fillMatrixFromFile(&matB);

	matRes.xSize = xSize;
	matRes.ySize = ySize;
	matRes.data = (float*)malloc(matRes.xSize * matRes.ySize * sizeof(float));

	printf("Matrix A:\n");
	printMatrix(stdout, &matA);
	printf("Matrix B:\n");
	printMatrix(stdout, &matB);

	matrixSumm(&matA, &matB, &matRes);
	printf("A + B:\n");
	printMatrix(stdout, &matRes);

	matrixMultiplication(&matA, &matB, &matRes);
	printf("A x B:\n");
	printMatrix(stdout, &matRes);

	matrixTranspose(&matA, &matRes);
	printf("Transposed A:\n");
	printMatrix(stdout, &matRes);

	fprintf(stdout, "Determinant B: %f\n\n", matrixDeterminant(&matB, &matRes));

	matrixInversion(&matB, &matRes);
	printf("Inversion A:\n");
	printMatrix(stdout, &matRes);

	free(matRes.data);
	free(matA.data);
	free(matB.data);
}
