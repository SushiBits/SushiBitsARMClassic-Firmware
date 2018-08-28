/*
 * main.c
 *
 *  Created on: Aug 25, 2018
 *      Author: technix
 */

#include <stm32f0xx.h>
#include "ring-buffer.h"

int main(void)
{
	for (;;)
		__WFE();
}
