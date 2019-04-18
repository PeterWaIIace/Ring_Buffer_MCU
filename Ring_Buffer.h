#ifndef  __RING_BUFFER__
#define  __RING_BUFFER__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct{
size_t head;
size_t tail;
size_t capacity;
size_t size; 
uint8_t* buffer;
}RingBuffer;

bool init_Buffer(RingBuffer * ring_buffer, size_t capacity);

bool clear_Buffer(RingBuffer* ring_buffer);

bool is_empty_Buffer(RingBuffer* ring_buffer);

bool write_into_Buffer(uint8_t write,RingBuffer* ring_buffer);

bool read_from_Buffer(uint8_t* read,RingBuffer* ring_buffer);

bool advance_head(RingBuffer* ring_buffer);

bool advance_tail(RingBuffer* ring_buffer);

#endif