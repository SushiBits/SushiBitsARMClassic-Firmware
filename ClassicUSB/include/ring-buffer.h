/*
 * ring-buffer.h
 *
 *  Created on: Sep 17, 2017
 *      Author: technix
 */

#ifndef SYSTEM_INCLUDE_DREAMOS_RT_RING_BUFFER_H_
#define SYSTEM_INCLUDE_DREAMOS_RT_RING_BUFFER_H_

#include <stdint.h>
#include <sys/types.h>
#include <sys/cdefs.h>

#define RING_BUFFER_DYNAMIC_MAGIC 0xCAFEBABE
#define RING_BUFFER_STATIC_MAGIC  0xDEADBEEF

typedef struct ring_buffer
{
	uint32_t magic;
	char *buffer;
	size_t length;
	off_t head;
	off_t tail;
} *ring_buffer_t;

__BEGIN_DECLS

#define RING_BUFFER_INIT(name, len) \
	uint8_t __rb_buf_##name[len]; \
	struct ring_buffer __rb_obj_##name = \
	{ \
		.magic = RING_BUFFER_STATIC_MAGIC, \
		.buffer = __rb_buf_##name, \
		.length = len, \
		.head = 0, \
		.tail = 0 \
	}; \
	ring_buffer_t name = &__rb_obj_##name
ring_buffer_t ring_buffer_init(size_t length);
void ring_buffer_dealloc(ring_buffer_t buffer);
int ring_buffer_putchar(ring_buffer_t buffer, char ch);
int ring_buffer_getchar(ring_buffer_t buffer);
int ring_buffer_peekchar(ring_buffer_t buffer);
int ring_buffer_getlength(ring_buffer_t buffer);
int ring_buffer_getalloc(ring_buffer_t buffer);
int ring_buffer_getspace(ring_buffer_t buffer);

__END_DECLS

#endif /* SYSTEM_INCLUDE_DREAMOS_RT_RING_BUFFER_H_ */
