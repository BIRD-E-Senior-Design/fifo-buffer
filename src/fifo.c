#include <stdio.h>
#include "pico/mutex.h"
#include "fifo.h"

#define BUFSIZE 64 // to be changed
#define FIFO_ERROR 5000 // out of range of sensor values
/*!
* \brief Pop the oldest value in the buffer
*/
size_t fifo_pop(fifo_t* fifo) {
    mutex_enter_blocking(&fifo->mx); 
    
    if(!fifo->count) {
        printf("FIFO Count is 0, you have nothing to pop from the buffer.\n"); 
        mutex_exit(&fifo->mx); 
        return FIFO_ERROR;
    }
    int popped_val = fifo->buffer[fifo->head];
    fifo->count--;
    fifo->head = (fifo->head + 1) % BUFSIZE;

    mutex_exit(&fifo->mx); 
    return popped_val; 
}

void fifo_push(fifo_t* fifo, size_t val) {
    mutex_enter_blocking(&fifo->mx);   
    
    if(fifo->count + 1 > BUFSIZE) {
        printf("You have exceeded the size of the buffer and may not continue to populate with values.\n");
        mutex_exit(&fifo->mx); 
        return;
    }
    fifo->buffer[fifo->tail] = val; 
    fifo->tail = (fifo->tail + 1) % BUFSIZE;
    fifo->count++; 
    
    mutex_exit(&fifo->mx); 
}

/*!
* \brief print the contents of the fifo out
*/
void fifo_print(fifo_t* fifo) {
    
    printf("Printing FIFO with %d elements\n", fifo->count);
    printf("Oldest value at %d with value %d\n", fifo->head, fifo->buffer[fifo->head]);
    printf("Next push at buffer[%d]\n", fifo->tail);
    printf("Values alive in the buffer starting at head: ");
    for(int i = fifo->head; i < fifo->head + fifo->count; i++) { // print the values
        printf("%d ", fifo->buffer[i]); 
    }
    printf("\n"); 
}
