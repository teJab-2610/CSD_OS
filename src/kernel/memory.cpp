#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../config/memory_map.h"
#include "../../include/kernel/memory.h"
#include "../../config/memory_map.h"

char filename[] = "memory.txt";
char memory[MEMORY_SIZE];
//Variable to store the metadata about the heap
int heap_metadata[HEAP_SIZE];

FILE* fp;

void __load_char_as_bits(char c, char* out) {
    int g = c;
    for (int i = 0; i < 8;i++) {
        out[i] = (g & 1) + '0';
        g >>= 1;
    }
    // for (int i = 0; i < 4;i++) {
    //     char temp = out[i];
    //     out[i] = out[7 - i];
    //     out[7 - i] = temp;
    // }
}

char __convert_bits_to_char(char* out) {
    //reverse the bits and compute the character
    char g = 0;
    for (int i = 0;i < 8;i++) {
        g <<= 1;
        g |= out[7 - i] - '0';
    }
    return g;
}

void mread(int addr, char* out) {
    assert(addr >= 0 && addr < MEMORY_SIZE);
    fseek(fp, addr * 10, SEEK_SET);
    fread(out, sizeof(char), 9, fp); 
}

char mread_char(int addr) {
    char out[9];
    mread(addr, out);
    char g;
    for (int i = 0;i < 8;i++) {
        g <<= 1;
        g |= out[i] - '0';
    }
    return g;
}

char mread_keyboard_char(int addr) {
    char out[9];
    mread(addr, out);
    return __convert_bits_to_char(out);
}

void mwrite(char c, int addr) {
    assert(addr >= 0 && addr < MEMORY_SIZE);  
    fseek(fp, addr * 10, SEEK_SET);
    char line[9];
    line[8] = '\n';
    __load_char_as_bits(c, line);
    fwrite(line, sizeof(char), 9, fp);
    fflush(fp);
}

void minit() {
    fp = fopen(filename, "r+");
    if (fp == NULL) {
        fp = fopen(filename, "w+");
        printf("Creating memory file\n");
        printf("MEMORY_SIZE: %d\n", MEMORY_SIZE);
        for (int i = 0;i < MEMORY_SIZE;i++) {
            char line[9];
            line[8] = '\n';
            __load_char_as_bits(0, line);
            fwrite(line, sizeof(char), 9, fp);
        }
    }
}

void mclose() {
    fclose(fp);
}

int m_alloc(int size){
    int head = HEAP_START;
    int free_found_size = 0;
    while(head < HEAP_SIZE) {
        if(free_found_size == size) {
            break;
        }
        if (heap_metadata[head] == 0) {
            head++;
            free_found_size++;
        } else {
            head = head + heap_metadata[head];
            free_found_size = 0;
        }
    }
    return head;
}

int m_free(int addr){
    heap_metadata[addr] = 0;
    return 1;
}

