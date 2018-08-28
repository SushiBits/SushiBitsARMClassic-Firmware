/*
 * main.c
 *
 *  Created on: Aug 25, 2018
 *      Author: technix
 */

#include "main.h"

#include <stm32f0xx.h>
#include "ring-buffer.h"
#include "usb/usb.h"

RING_BUFFER_INIT(rx_buffer, BUFFER_SIZE);
RING_BUFFER_INIT(tx_buffer, BUFFER_SIZE);

int main(void)
{
	usb_init();

	for (;;)
		__WFE();
}
