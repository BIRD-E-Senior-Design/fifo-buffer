#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "fifo.h"

// #define TEST1
// #define TEST2
// #define TEST3
// #define TEST4


int main() {
    stdio_init_all(); 
    fifo_t sensor_buf = {0};
    mutex_init(&sensor_buf.mx); 

    #ifdef TEST1 // try pop an empty buffer
    size_t val = fifo_pop(&sensor_buf);
    assert(val == FIFO_ERROR);
    #endif

    #ifdef TEST2 // push a range of values into the buffer
    for(size_t i = 0; i < BUFSIZE + 1; i++){
        fifo_push(&sensor_buf, i);
    }
    assert(sensor_buf.head == 0); // the value you can pop is at the idex 0 
    assert(sensor_buf.tail == 0); // next value you can push to is also at the 0 index. head == tail 
    assert(sensor_buf.count == BUFSIZE); // you have BUFSIZE elements, buffer is full and will not add BUFSIZE + 1
    assert(sensor_buf.buffer[sensor_buf.count - 1] == BUFSIZE - 1); // the last value pushed per the previous loop is BUFSIZE
    fifo_print(&sensor_buf);
    #endif

    #ifdef TEST3 // push a range of value then pop one off
    for(size_t i = 0; i < BUFSIZE + 1; i++){
        fifo_push(&sensor_buf, i);
    }
    printf("After pushing values to sensor buffer\n");
    fifo_print(&sensor_buf); 

    int val = fifo_pop(&sensor_buf); 
    printf("After popping %d\n", val); 
    assert(sensor_buf.head == 1); // the next value you can pop is at index 1 
    assert(sensor_buf.tail == 0); // the next value you can push to is at index 0
    assert(sensor_buf.count == BUFSIZE - 1); // if we started with BUFSIZE elems, you should have one less
    assert(val != FIFO_ERROR); 
    fifo_print(&sensor_buf); 
    #endif

    #ifdef TEST4 // alternatively, pop everything 
    for(size_t i = 0; i < BUFSIZE; i++) {
        fifo_push(&sensor_buf, i);
    }
    
    int val; 
    while(sensor_buf.count != 0) {
        val = fifo_pop(&sensor_buf); 
    }

    assert(sensor_buf.head == 0); // the next value you can pop is at index 1 
    assert(sensor_buf.tail == 0); // the next value you can push to is at index 0
    assert(sensor_buf.count == 0); // if we started with BUFSIZE elems, you should have one less
    assert(val != FIFO_ERROR); 

    #endif 

    #ifdef TEST5
    
    #endif

}
