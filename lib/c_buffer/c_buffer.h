#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE (10)
#endif

typedef struct {

  uint8_t buffer[BUFFER_SIZE];
  uint8_t head;
  uint8_t tail;
  uint8_t element_count;

} cbuffer_t;


void init_buffer(cbuffer_t *buff);
bool buffer_is_empty(cbuffer_t *buff);
bool buffer_is_full(cbuffer_t *buff);
uint8_t count_buffer_elements(cbuffer_t *buff);
void add_element(cbuffer_t *buff, uint8_t new_element);
uint8_t pop_element(cbuffer_t *buff);
void clear_buffer(cbuffer_t *buff);
bool head_overflow(cbuffer_t *buff);
bool tail_overflow(cbuffer_t *buff);


#endif // CIRCULAR_BUFFER_H