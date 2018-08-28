/*
 * rcc.c
 *
 *  Created on: Aug 25, 2018
 *      Author: technix
 */

#include <stm32f0xx.h>

#ifndef wait
#define wait(cond) do {} while (!(cond))
#endif

void SystemInit(void)
{
	RCC->CR |= RCC_CR_HSEON;
	wait(RCC->CR & RCC_CR_HSERDY);

	RCC->CFGR = RCC_CFGR_PLLMUL6 | RCC_CFGR_PLLSRC_HSE_PREDIV;
	RCC->CFGR2 = 1 << RCC_CFGR2_PREDIV_Msk;
	RCC->CR |= RCC_CR_PLLON;
	wait(RCC->CR & RCC_CR_PLLRDY);

	FLASH->ACR = FLASH_ACR_PRFTBE | (1 << FLASH_ACR_LATENCY_Pos);
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	wait((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL);
}
