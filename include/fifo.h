#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>
#include "pico/mutex.h"

#define BUFSIZE 64 
#define FIFO_ERROR 5000

typedef struct {
    size_t buffer[BUFSIZE];
    int count; 
    int head; 
    int tail; 
    mutex_t mx; 
} fifo_t; 

/*!
* \brief Pop the oldest value (from the head)
*/
size_t fifo_pop(fifo_t* buffer); 

/*!
* \brief Push a new value into the buffer through the tail
* \param val: obtained sensor value 
*/
void fifo_push(fifo_t* buffer, size_t val); 

/*!
* \brief print all fields of the buffer
*/
void fifo_print(fifo_t* buffer); 

#endif