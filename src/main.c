#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "fifo.h"

// #define TEST1
#define TEST2

int main() {
    stdio_init_all(); 
    fifo_t sensor_buf = {0}; 
    mutex_init(&sensor_buf.mx); 

    #ifdef TEST1 
    printf("Test 1: Try to pop an empty buffer\n");
    size_t val = fifo_pop(&sensor_buf);
    #endif

    #ifdef TEST2 // push values

    printf("Test 2: Push a single value into the buffer"); 
    for(size_t i = 0; i < BUFSIZE + 1; i++){
        fifo_push(&sensor_buf, i);
    }
    fifo_print(&sensor_buf);
    #endif

    #ifdef TEST3 
    #endif


}
