#include "c_buffer.h"

void init_buffer(cbuffer_t *buff) {
    buff->head = 0;
    buff->tail = 0;
    buff->element_count = 0;
}

bool buffer_is_empty(cbuffer_t *buff) {
    return (buff->element_count == 0);
}

bool buffer_is_full(cbuffer_t *buff) {
    return (buff->element_count == BUFFER_SIZE);
}

uint8_t count_buffer_elements(cbuffer_t *buff) {
    return buff->element_count;
}

void add_element(cbuffer_t *buff, uint8_t new_element) {
    if (tail_overflow(buff)) {
        buff->tail = 0;
    }

    if (head_overflow(buff)) {
        buff->head = 0;
    }

    if (buffer_is_full(buff)) {
        buff->tail++;
    }

    buff->buffer[buff->head] = new_element;
    buff->head++;

    if( buff->element_count < BUFFER_SIZE ){
        buff->element_count++;
    }
}

uint8_t pop_element(cbuffer_t *buff) {
    uint8_t element_to_return = 0;

    if (tail_overflow(buff)) {
        buff->tail = 0;
    }

    element_to_return = buff->buffer[buff->tail];

    if(buffer_is_empty(buff)){
        element_to_return = 0;
    } else {        
        buff->tail++;
        buff->element_count--;
    }

    return element_to_return;
}

void clear_buffer(cbuffer_t *buff) {
    init_buffer(buff);
}

bool head_overflow(cbuffer_t *buff) {
    return(buff->head == BUFFER_SIZE);
}

bool tail_overflow(cbuffer_t *buff) {
    return(buff->tail == BUFFER_SIZE);
}