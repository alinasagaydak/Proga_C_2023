#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP_SIZE 3
#define MANT_SIZE 4
#define EXP_BIAS
typedef int float8; /* 0..255 */

typedef struct
{
	int sign;
	int ex;
	int man;
} VarFlist;

int MSB_seeker(int a)
{
    int MSB = 0;
   
    for (int i = sizeof(int) * 8; i > 0; i--) {

        MSB = (a & 1); 

        a >>= 1;
    }

	return a;
}

void F8toF32(float8 x)
{

}

float8 F32toF8(float x, VarFlist* fpRes)
{
	int sign = !!signbit(x) << 7;
	x = fabs(x);
	int e;
	x = frexp(x, &e) - .5;

	return sign | (e - 1 + 3) << 4 | (uint8_t)(x * 0x1p5);
}


int main()
{

}
