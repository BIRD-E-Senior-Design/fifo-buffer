#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>
#include "pico/mutex.h"

#define BUFSIZE 64 

typedef struct {
    size_t buffer[BUFSIZE];
    int head; 
    int tail; 
    int count; 
    mutex_t mx; 
} fifo_t; 

/*!
* \brief Pop the oldest value in the buffer
*/
size_t fifo_pop(fifo_t* buffer); 

/*!
* \brief Push a new value into the buffer
* \param val: obtained sensor value 
*/
void fifo_push(fifo_t* buffer, size_t val); 

/*!
* \brief print all fields of the buffer
*/
void fifo_print(fifo_t* buffer); 

#endif