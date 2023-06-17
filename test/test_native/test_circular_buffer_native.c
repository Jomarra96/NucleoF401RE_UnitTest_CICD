#include <unity.h>
#include "c_buffer.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_circular_buffer_must_be_empty_after_init() {
    cbuffer_t buff;
    
    init_buffer(&buff);
    
    TEST_ASSERT_TRUE(buffer_is_empty(&buff));
}

void test_buffer_must_not_be_empty_after_adding_an_element() {
    cbuffer_t buff;
    uint8_t new_data = 0;

    init_buffer(&buff);
    add_element(&buff, new_data);
    
    TEST_ASSERT_FALSE(buffer_is_empty(&buff));
}

void test_add_element_must_overwrite_oldest_when_buffer_is_full() {
    cbuffer_t buff;
    uint8_t counter = 0;
    
    init_buffer(&buff);

    do {        
        add_element(&buff, counter);
        counter++;
        
    } while(counter < BUFFER_SIZE+1);
    
    TEST_ASSERT_TRUE( buff.buffer[buff.head-1] == (counter-1) );
}

void test_retrieve_element_must_provide_oldest_element() {
    cbuffer_t buff;
    uint8_t counter = 55;
    uint8_t retrieved_element = 0;
    uint8_t initial_counter_value = counter;
    
    init_buffer(&buff);

    do {        
        add_element(&buff, counter);
        counter++;
        
    } while(counter < BUFFER_SIZE);
    
    retrieved_element = pop_element(&buff);

    TEST_ASSERT_TRUE( retrieved_element == initial_counter_value );
}

void test_element_count_must_account_for_insertions_and_deletions() {
    cbuffer_t buff;
    uint8_t counter = 0;
    uint8_t elements_in_buffer = 0;
    bool is_counter_correct = false;
    
    init_buffer(&buff);

    do {        
        add_element(&buff, counter);
        elements_in_buffer++;

        pop_element(&buff);
        elements_in_buffer--;

        add_element(&buff, counter);
        elements_in_buffer++;
        
        counter++;
    } while(counter < 5);

    if(count_buffer_elements(&buff) == elements_in_buffer)
    {
        is_counter_correct = true;
    }

    TEST_ASSERT_TRUE(is_counter_correct);
}

void test_buffer_must_be_empty_after_clearing() {
    cbuffer_t buff;
    uint8_t counter = 0;

    init_buffer(&buff);

    do {        
        add_element(&buff, counter);
        counter++;

    } while(counter < BUFFER_SIZE);

    clear_buffer(&buff);

    TEST_ASSERT_TRUE( buffer_is_empty(&buff));
}

int main() {
    
    UNITY_BEGIN();

    RUN_TEST(test_circular_buffer_must_be_empty_after_init);
    RUN_TEST(test_buffer_must_not_be_empty_after_adding_an_element);
    RUN_TEST(test_add_element_must_overwrite_oldest_when_buffer_is_full);
    RUN_TEST(test_retrieve_element_must_provide_oldest_element);
    RUN_TEST(test_element_count_must_account_for_insertions_and_deletions);
    RUN_TEST(test_buffer_must_be_empty_after_clearing);

    UNITY_END();

    while (1)
    {
    }
}
