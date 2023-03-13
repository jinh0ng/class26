//add_nbo.h
#pragma once
#ifndef ADD_NBO_H
# define ADD_NBO_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t ntohl(uint32_t netlong);
uint32_t hex2d(uint32_t num);
uint32_t add_nbo(int32_t num1, uint32_t num2);



#endif
