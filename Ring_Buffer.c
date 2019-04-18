#include "Ring_Buffer.h"
/*
Ring_Buffer initialisation
 
bool init_Buffer(RingBuffer * ring_buffer, uint32_t capacity) 
Input:
ptr to RingBuffer structure, total capacity
return:
check state (true/false)
*/
bool init_Buffer(RingBuffer * ring_buffer, size_t capacity){
  ring_buffer->buffer=malloc(capacity);
  if (!ring_buffer->buffer){
    perror("memmory allocation failure in init_Buffer");
    return false;
  }
  ring_buffer->capacity=capacity;
  ring_buffer->size=0x00;
  ring_buffer->head=0x00;
  ring_buffer->tail=0x00;
  return true;
}

/*
Ring_Buffer deinitialisation
 
bool deinit_Buffer(RingBuffer * ring_buffer) 
Input:
ptr to RingBuffer structure
return:
check state (true/false)
*/
bool deinit_Buffer(RingBuffer * ring_buffer){
  if(!clear_Buffer(ring_buffer)){
    perror("deinit error - clear failure");
    return false;
  }
  free(ring_buffer->buffer);
  return true;
}

/*
Ring_Buffer clear
 
bool clear_Buffer(RingBuffer * ring_buffer) 
Input:
ptr to RingBuffer structure
return:
check state (true/false)
function:
clears buffer by setting all head, tail, size to zeros
*/
bool clear_Buffer(RingBuffer* ring_buffer){
  ring_buffer->head =0x00;
  ring_buffer->tail =0x00;
  ring_buffer->size =0x00;
  if((ring_buffer->size !=0x00)||(ring_buffer->head !=0x00)||(ring_buffer->tail !=0x00)){
    perror("clear error - clear failure");
    return false;
  }
  return true;
}
bool is_empty_Buffer(RingBuffer* ring_buffer){
  if(ring_buffer->head == ring_buffer->tail && ring_buffer->size != 0x00){
    return true;
  }
  return false;
}
/*
Ring_Buffer write
 
bool write_into_Buffer(uint8_t write,RingBuffer * ring_buffer) 
Input:
value to be written,ptr to RingBuffer structure
return:
check state (true/false)
function:
writes one character to the buffer and advance head pointer
*/
bool write_into_Buffer(uint8_t write,RingBuffer* ring_buffer){
  ring_buffer->buffer[ring_buffer->head] = write;
  if(ring_buffer->buffer[ring_buffer->head] != write){
    perror("write error - value is different than entered one");
    return false;
  }
  if(!advance_head(ring_buffer)){
    perror("write error - advanced head error");
    return false;
  }
  return true;
}

bool read_from_Buffer(uint8_t* read,RingBuffer* ring_buffer){
  if(is_empty_Buffer(ring_buffer)){
    return false;
  }
  read = ring_buffer->buffer[ring_buffer->tail];
  advance_tail(ring_buffer);
  return true;
}

/*
Ring_Buffer advance
 
bool write_into_Buffer(RingBuffer * ring_buffer) 
Input:
ptr to RingBuffer structure
return:
check state (true/false)
function:
advance head pointer of buffer - when capacity is reached, pointer is reseted to zero and data will be overwritten
*/
bool advance_head(RingBuffer* ring_buffer){
  if(ring_buffer->head == ring_buffer->capacity){
    ring_buffer->head = 0x00;
    if(ring_buffer->head != 0x00){
      perror("advance head - reseting head error");
      return false;
    }
  }
  else{
    ring_buffer->head += 1;
  }
  return true;
}

/*
Ring_Buffer advance
 
bool write_into_Buffer(RingBuffer * ring_buffer) 
Input:
ptr to RingBuffer structure
return:
check state (true/false)
function:
advance tail pointer of buffer - when capacity is reached, pointer is reseted to zero
*/
bool advance_tail(RingBuffer* ring_buffer){
  if(ring_buffer->tail == ring_buffer->head){
    return true;
  }
  else if(ring_buffer->tail == ring_buffer->capacity){
    ring_buffer->tail = 0x00;
    if(ring_buffer->tail != 0x00){
      perror("advance head - reseting head error");
      return false;
    }
  }
  else{
    ring_buffer->tail += 1;
  }
  return true;
}