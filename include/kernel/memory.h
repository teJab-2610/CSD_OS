/**
 * Memory module consists of functions for memory management.
 * Functiolaity includes memory initialization, copying, setting, allocation and freeing.
*/

#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>

#include "../../config/memory_map.h"
extern char filename[];
extern char memory[];

/**
 * @brief write into file at specific col, row
 *  read from file at specific row, col
*/

// char => to bits 
void __load_char_as_bits(char c, char* out);

// read a single character from file
// note: the file is a text file, so we need to convert the char to bits in out
void mread(int addr, char* out);
char mread_char(int addr);
void mwrite(char c, int addr);
char mread_keyboard_char(int addr);
void minit();
void mclose();
int m_alloc(int size);
int m_free(int addr);
#endif // MEMORY_H














// #ifndef KERNEL_MEMORY_H
// #define KERNEL_MEMORY_H

// #include <stddef.h>
// #include <stdint.h>
// #include "config/memory_map.h"

// // Memory map structure
// typedef struct {
//     void* kernel_start;
//     size_t kernel_size;
//     void* heap_start;
//     size_t heap_size;
//     void* stack_start;
//     size_t stack_size;
//     void* pcb_pool_start;
//     size_t pcb_pool_size;
// } MemoryMap;

// // Function prototypes
// void memory_map_init(MemoryMap* map);
// void* kmalloc(size_t size);
// void kfree(void* ptr);


// #endif // KERNEL_MEMORY_H