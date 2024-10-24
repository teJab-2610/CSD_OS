#include <stdlib.h>
#include "../include/kernel/process.h"
#include "../include/kernel/globals.h"
#include "../include/kernel/registers.h"
#include "../include/kernel/memory.h"

int current_processes = 0;

void process_init() {
    PCB* pcb = allocate_pcb();
    // Allocate text segment
    pcb->text_segment = malloc(PROCESS_TEXT_SEGMENT_SIZE);
    if (pcb->text_segment == NULL) {
        free_pcb(pcb->process_id);
        return;
    }
    // Allocate stack
    pcb->stack_base = malloc(PROCESS_STACK_SIZE);
    if (pcb->stack_base == NULL) {
        free(pcb->text_segment);
        free_pcb(pcb->process_id);
        return;
    }
    // Set up initial stack pointer
    pcb->registers.ESP = (uint32_t)pcb->stack_base + PROCESS_STACK_SIZE;

    // Allocate initial heap
    pcb->heap_start = malloc(PROCESS_INITIAL_HEAP_SIZE);
    if (pcb->heap_start == NULL) {
        free(pcb->text_segment);
        free(pcb->stack_base);
        free_pcb(pcb->process_id);
        return;
    }
    pcb->heap_end = (char*)pcb->heap_start + PROCESS_INITIAL_HEAP_SIZE;
    pcb->heap_size = PROCESS_INITIAL_HEAP_SIZE;

    pcb->next = head;
    head = pcb;

    pcb->state = ProcessState::PROCESS_READY;
}

PCB* allocate_pcb() {
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->process_id = current_processes++;
    pcb->state = ProcessState::PROCESS_READY;
    pcb->registers = Registers();
    pcb->next = NULL;
    return pcb;
}

PCB* find_pcb(int process_id) {
    PCB* current = head;
    while (current != NULL) {
        if (current->process_id == process_id) {
           return current;
        }
        current = current->next;
    }
}

void free_pcb(int process_id) {
    PCB* prev = NULL;
    PCB* current = head;
    
    while (current != NULL) {
        if (current->process_id == process_id) {
            // Free allocated memory
            free(current->text_segment);
            free(current->stack_base);
            free(current->heap_start);

            // Remove PCB from the list
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void pause_process(int process_id) {
    //Make the process state as waiting when an interrupt is recieved
    PCB* pcb = find_pcb(process_id);
    pcb->state = ProcessState::PROCESS_WAITING;
}

void resume_process(int process_id) {
    //Resume the process after the interrupt is handled
    PCB* pcb = find_pcb(process_id);
    pcb->state = ProcessState::PROCESS_READY;
}

void destroy_process(int process_id) {
    PCB* pcb = find_pcb(process_id);
    free_pcb(pcb);
}

//Scheduler to schedule the processes
void scheduler() {
    //Find the first process which is ready to execute 
    PCB* current = head;
    while (current != NULL) {
        if (current->state == ProcessState::PROCESS_READY) {
            break;
        }
        current = current->next;
    }
    //Set the current process as the one to execute
    current_process_id = current->process_id;
}
