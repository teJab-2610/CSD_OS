#ifndef KERNEL_SCHEDULER_H
#define KERNEL_SCHEDULER_H

#include "kernel/process.h"

// Scheduler states
typedef enum {
    SCHEDULER_IDLE,
    SCHEDULER_RUNNING
} SchedulerState;

// Scheduler structure
typedef struct {
    SchedulerState state;
    PCB* current_process;
    PCB* ready_queue;  // Head of the ready queue
} Scheduler;

// Function prototypes

// Initialize the scheduler
void scheduler_init(void);

// Add a process to the ready queue
void scheduler_add_process(PCB* process);

// Remove a process from the ready queue
void scheduler_remove_process(PCB* process);

// Get the next process to run
PCB* scheduler_get_next_process(void);

// Perform a context switch
void scheduler_context_switch(void);

// Schedule function - decides which process to run next
void schedule(void);

// Yield function - voluntarily give up CPU
void yield(void);

// Get the current running process
PCB* get_current_process(void);

// Get the scheduler state
SchedulerState get_scheduler_state(void);

#endif // KERNEL_SCHEDULER_H