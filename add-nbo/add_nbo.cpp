#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "add_nbo.h"

uint32_t ntohl(uint32_t netlong){
	uint32_t a1 = (netlong & 0xff000000) >> 24;
	uint32_t a2 = (netlong & 0x00ff0000) >> 8;
	uint32_t a3 = (netlong & 0x0000ff00) << 8;
	uint32_t a4 = (netlong & 0x000000ff) << 24;
	return (a1 | a2 | a3 | a4);
}

/*uint32_t hex2d(uint32_t num){
	
}

uint32_t add_nbo(uint32_t num1, uint32_t num2){

}*/
