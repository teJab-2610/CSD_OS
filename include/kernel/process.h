#ifndef KERNEL_PROCESS_H
#define KERNEL_PROCESS_H

#include <stdint.h>
#include "memory.h"
#include "./registers.h"

int PROCESS_TEXT_SEGMENT_SIZE = 1024 * 1024;  // 1 MB
int PROCESS_STACK_SIZE = 64 * 1024;           // 64 KB
int PROCESS_INITIAL_HEAP_SIZE = 256 * 1024;   // 256 KB

typedef enum {
    PROCESS_NEW,
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} ProcessState;


//TODO: Give a particular location in memory layout to store PCBs.
struct PCB {
    int process_id;
    ProcessState state;
    Registers registers;
    PCB* next;
    void* text_segment;
    void* stack_base;
    void* heap_start;
    void* heap_end;
    size_t heap_size;
};

//Head of the PCB linked list
PCB* head;

void intit_process();
PCB* allocate_pcb(void);
void free_pcb(PCB* pcb);
PCB* create_process(/* parameters for process creation */);
void destroy_process(int process_id);

//Pause and resume processes when an interrupt is recieved
void pause_process(int process_id);
void resume_process(int process_id);

//Scheduler to schedule the processes
void scheduler();

#endif
