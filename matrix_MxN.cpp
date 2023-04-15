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

Matrix readMatrixFromFile(FILE* fp, Matrix* matA)
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
	
	return *matA;
}

void writeMatrixToFile(FILE* fp, Matrix* matA, const char* nameFunction)
{
	fprintf(fp, "%s\n", nameFunction);
	for (int rowNum = 0; rowNum < matA->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matA->xSize; colNum++)
		{
			fprintf(fp, "%f%c", *(matA->data + rowNum * matA->xSize + colNum), ' ');
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
}

Matrix createZeroMatrix(int xSize, int ySize)
{
	Matrix matRes;
	matRes.xSize = xSize;
	matRes.ySize = ySize;
	matRes.data = (float*)malloc(matRes.xSize * matRes.ySize * sizeof(int));

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			*(matRes.data + rowNum * matRes.xSize + colNum) = 0;
		}
	}
	return matRes;
}

Matrix createIdentityMatrix(int xSize, int ySize)
{
	Matrix matRes;
	matRes.xSize = xSize;
	matRes.ySize = ySize;
	matRes.data = (float*)malloc(matRes.xSize * matRes.ySize * sizeof(int));

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			*(matRes.data + rowNum * matRes.xSize + colNum) = 0.0;
			if (rowNum == colNum)
				*(matRes.data + rowNum * matRes.xSize + colNum) = 1.0;
		}
	}
	return matRes;
}

Matrix createIdenticalMatrix(Matrix* matA)
{
	Matrix matRes;
	matRes.xSize = matA->xSize;
	matRes.ySize = matA->ySize;
	matRes.data = (float*)malloc(matRes.xSize * matRes.ySize * sizeof(int));

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			*(matRes.data + rowNum * matRes.xSize + colNum) = *(matA->data + rowNum * matA->xSize + colNum);
		}
	}
	return matRes;
}

Matrix initRandomMatrix(Matrix* matA)
{
	matA->xSize = 3; //добавить ввод с клавы
	matA->ySize = 3;
	matA->data = (float*)malloc(matA->xSize * matA->ySize * sizeof(int));

	time_t t;
	srand((unsigned)time(&t));

	for (int rowNum = 0; rowNum < matA->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matA->xSize; colNum++)
		{
			*(matA->data + rowNum * matA->xSize + colNum) = rand() %10;
		}
	}
	return *matA;
}

Matrix initMatrixFromFile(Matrix* matA)
{
	FILE* fp;
	char fileName[] = "matB.txt";

	matA->xSize = 3; //добавить ввод с клавы
	matA->ySize = 3;
	matA->data = (float*)malloc(matA->xSize * matA->ySize * sizeof(int));

	fopen_s(&fp, fileName, "ab+");
	{
		if (fp != NULL) readMatrixFromFile(fp, matA);
		else printf("File error");
	}
	fclose(fp);

	return *matA;
}

void printMatrix(Matrix* matA, const char* nameFunction)
{
	printf("%s\n", nameFunction);
	for (int rowNum = 0; rowNum < matA->ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matA->xSize; colNum++)
		{
			printf("%f\t", *(matA->data + rowNum * matA->xSize + colNum));
		}
		printf("\n");
	}
	printf("\n");
}

Matrix* matrixSumm(Matrix* matA, Matrix* matB)
{
	Matrix matRes = createIdenticalMatrix(matA);
	
	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			*(matRes.data + rowNum * matRes.xSize + colNum) += *(matB->data + rowNum * matB->xSize + colNum);
		}
	}
	return &matRes;
}

Matrix* matrixMultiplication(Matrix* matA, Matrix* matB)
{
	Matrix matRes = createZeroMatrix(matB->xSize, matA->ySize);

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			for (int k = 0; k < matA->xSize; k++)
			{
				*(matRes.data + rowNum * matRes.xSize + colNum) += *(matA->data + rowNum * matA->xSize + k) * *(matB->data + k * matB->xSize + colNum);
			}
		}
	}
	return &matRes;
}

Matrix* matrixTranspose(Matrix* matA)
{
	Matrix matRes = createZeroMatrix(matA->xSize, matA->ySize);

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			*(matRes.data + rowNum * matRes.xSize + colNum) = *(matA->data + colNum * matA->xSize + rowNum);
		}
	}
	return &matRes;
}

float matrixDeterminant(Matrix* matA)
{
	Matrix matRes = createIdenticalMatrix(matA);
	float rowReduction = 0;
	float det = 1;	

	for (int diagEl = 0; diagEl < matRes.xSize; diagEl++)
	{
		for (int rowNum = diagEl + 1; rowNum < matRes.ySize; rowNum++)
		{
			if (*(matRes.data + diagEl * matRes.xSize + diagEl) != 0)
			{
				rowReduction = -*(matRes.data + rowNum * matRes.xSize + diagEl) / *(matRes.data + diagEl * matRes.xSize + diagEl);
				for (int colNum = 0; colNum < matRes.xSize; colNum++)
				{
					*(matRes.data + rowNum * matRes.xSize + colNum) += *(matRes.data + diagEl * matRes.xSize + colNum) * rowReduction;
				}
			}
		}
	}

	for (int diagEl = 0; diagEl < matRes.ySize; diagEl++)
	{
		det *= *(matRes.data + diagEl * matRes.xSize + diagEl);
	}
	return det;
}

Matrix* matrixInversion(Matrix* matA)
{
	float rowReduction = 0;
	Matrix matRes = createIdentityMatrix(matA->xSize, matA->ySize);
	Matrix matTmp = createIdenticalMatrix(matA);

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
					*(matRes.data + rowNum * matRes.xSize + colNum) += *(matRes.data + diagEl * matRes.xSize + colNum) * rowReduction;
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
					*(matRes.data + rowNum * matRes.xSize + colNum) += *(matRes.data + diagEl * matRes.xSize + colNum) * rowReduction;
				}
			}
		}
	}

	for (int rowNum = 0; rowNum < matRes.ySize; rowNum++)
	{
		float temp = *(matTmp.data + rowNum * matTmp.xSize + rowNum);
		for (int colNum = 0; colNum < matRes.xSize; colNum++)
		{
			*(matRes.data + rowNum * matRes.xSize + colNum) /= temp;
		}
	}

	free(matTmp.data);
	return &matRes;
}

int main()
{
	Matrix matA, matB;
	FILE* fp;

	initRandomMatrix(&matA);
	printMatrix(&matA, "Matrix A:");
	
	initMatrixFromFile(&matB);
	printMatrix(&matB, "Matrix B:");

	printMatrix(matrixSumm(&matA, &matB), "A + B:");
	printMatrix(matrixMultiplication(&matA, &matB), "A x B:");
	printMatrix(matrixTranspose(&matA), "Transposed A:");
	printf("Determinant B: %f\n", matrixDeterminant(&matB));
	//printMatrix(matrixInversion(&matB), "matInv");

	fopen_s(&fp, "mat_res.txt", "ab+");
	{
		writeMatrixToFile(fp, &matA, "Matrix A:");
		writeMatrixToFile(fp, &matB, "Matrix B:");
		writeMatrixToFile(fp, matrixSumm(&matA, &matB), "A + B:");
		writeMatrixToFile(fp, matrixMultiplication(&matA, &matB), "A x B:");
		writeMatrixToFile(fp, matrixTranspose(&matA), "Transposed A:");
		fprintf(fp, "%s%f", "Determinant B: ", matrixDeterminant(&matB));
		writeMatrixToFile(fp, matrixInversion(&matB), "Inversion A:");
	}
	fclose(fp);

	free(matA.data);
	free(matB.data);
}
