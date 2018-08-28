/*
 * main.h
 *
 *  Created on: Aug 26, 2018
 *      Author: technix
 */

#ifndef INCLUDE_MAIN_H_
#define INCLUDE_MAIN_H_

#include "ring-buffer.h"

#define BUFFER_SIZE 512

extern ring_buffer_t rx_buffer;
extern ring_buffer_t tx_buffer;

#endif /* INCLUDE_MAIN_H_ */
