//main.cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "add-nbo.h"

int main(int argc, char **argv){
	FILE *fp1, *fp2;
	int num1, num2, num3;
	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");
	
	fread(&num1, sizeof(uint32_t), 1, fp1);
	fread(&num2, sizeof(uint32_t), 1, fp2);
	
	num1 = ntohl(num1);
	num2 = ntohl(num2);

	printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n",num1, num1, num2, num2, num1 + num2, num1 + num2);
}
