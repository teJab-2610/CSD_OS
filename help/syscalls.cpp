/*
This simplified version:
Defines a SyscallArgs structure to hold syscall arguments.
Uses an array syscall_handlers to store syscall handler functions.
Implements handle_syscall as the main entry point for all syscalls.
4. Provides a register_syscall function to add new syscalls.
Includes a simple example syscall sys_print_string.
To use this in your OS:
Call initialize_syscalls() during kernel initialization.
2. Set up your interrupt handler to call handle_syscall when a syscall interrupt occurs, passing the appropriate SyscallArgs structure.
Implement the assembly code on the user side to trigger the syscall interrupt and pass arguments.
*/

#include <stdint.h>

// Define a simple structure for holding syscall arguments
struct SyscallArgs {
    int syscall_number;
    int arg1;
    int arg2;
    int arg3;

    /*
    Reg the arguments:
    EAX: Usually contains the system call number.
    EBX, ECX, EDX: Typically used for passing the first three arguments.
    EAX is also used to store the return value after the system call completes.
    The exact registers used can vary depending on the specific calling convention your OS uses. Some systems might use different registers or even the stack for passing arguments.
    To access these registers, you'll need a way to get the CPU state when the interrupt occurs.
    This is often passed to the interrupt handler or accessible through a global structure. 
    The exact implementation depends on how your kernel manages interrupts and CPU state.
    */
};

// Define syscall handler type
using syscall_handler_t = int (*)(int arg1, int arg2, int arg3);

// Array to store syscall handlers
#define MAX_SYSCALLS 10
static syscall_handler_t syscall_handlers[MAX_SYSCALLS] = {0};

// Syscall handler function
extern "C" int handle_syscall(SyscallArgs* args) {
    if (args->syscall_number >= 0 && args->syscall_number < MAX_SYSCALLS) {
        syscall_handler_t handler = syscall_handlers[args->syscall_number];
        if (handler) {
            return handler(args->arg1, args->arg2, args->arg3);
        }
    }
    return -1; // Invalid syscall
}

// Function to register a syscall
void register_syscall(int syscall_number, syscall_handler_t handler) {
    if (syscall_number >= 0 && syscall_number < MAX_SYSCALLS) {
        syscall_handlers[syscall_number] = handler;
    }
}

// Example syscall: print_string
int sys_print_string(int str_addr, int length, int unused) {
    // Implementation would depend on your kernel's memory management
    // and console output functions
    // This is just a placeholder
    return 0;
}

// Initialize syscalls
void initialize_syscalls() {
    register_syscall(0, sys_print_string);
    // Register more syscalls here as needed
}































// #include "kernel/syscalls.h"
// #include "kernel/process.h"
// #include "kernel/scheduler.h"
// #include "kernel/interrupt.h" 
// // Include other necessary headers
// // Function pointer type for system calls
// typedef int (*syscall_func_t)(int, int, int);

// // Array of system call function pointers
// static syscall_func_t syscall_table[256];  // Adjust size as needed

// void syscalls_init(void) {
//     // Initialize the syscall table
//     for (int i = 0; i < 256; i++) {
//         syscall_table[i] = NULL;
//     }

//     // Register system calls
//     syscall_table[SYS_EXIT] = (syscall_func_t)sys_exit;
//     syscall_table[SYS_FORK] = (syscall_func_t)sys_fork;
//     syscall_table[SYS_READ] = (syscall_func_t)sys_read;
//     syscall_table[SYS_WRITE] = (syscall_func_t)sys_write;
//     syscall_table[SYS_OPEN] = (syscall_func_t)sys_open;
//     syscall_table[SYS_CLOSE] = (syscall_func_t)sys_close;
//     syscall_table[SYS_YIELD] = (syscall_func_t)sys_yield;
//     syscall_table[SYS_GETPID] = (syscall_func_t)sys_getpid;

//     // Register the system call handler with the interrupt system
//     register_interrupt_handler(SYSCALL_INTERRUPT, handle_syscall);
// }

// void sys_exit(int status) {
//     // Implement process termination
// }

// int sys_fork(void) {
//     // Implement process forking
//     return -1;  // Return -1 if not implemented
// }

// int sys_read(int fd, void *buf, size_t count) {
//     // Implement file reading
//     return -1;  // Return -1 if not implemented
// }

// int sys_write(int fd, const void *buf, size_t count) {
//     // Implement file writing
//     return -1;  // Return -1 if not implemented
// }

// int sys_open(const char *pathname, int flags) {
//     // Implement file opening
//     return -1;  // Return -1 if not implemented
// }

// int sys_close(int fd) {
//     // Implement file closing
//     return -1;  // Return -1 if not implemented
// }

// void sys_yield(void) {
//     // Implement process yielding
//     yield();  // Call the scheduler's yield function
// }

// int sys_getpid(void *unused) {
//     // Implement getting process ID
//     return get_current_process()->process_id;
// }

// // int handle_syscall(int syscall_number, int arg1, int arg2, int arg3) {
// //     switch (syscall_number) {
// //         case SYS_EXIT:
// //             sys_exit(arg1);
// //             break;
// //         case SYS_FORK:
// //             return sys_fork();
// //         case SYS_READ:
// //             return sys_read(arg1, (void*)arg2, arg3);
// //         case SYS_WRITE:
// //             return sys_write(arg1, (void*)arg2, arg3);
// //         case SYS_OPEN:
// //             return sys_open((const char*)arg1, arg2);
// //         case SYS_CLOSE:
// //             return sys_close(arg1);
// //         case SYS_YIELD:
// //             sys_yield();
// //             break;
// //         case SYS_GETPID:
// //             return sys_getpid();
// //         default:
// //             // Handle unknown system call
// //             return -1;
// //     }
// //     return 0;
// // }

void handle_syscall() {
    // Extract syscall number and arguments from registers
    int syscall_number = /* get from appropriate register */;
    int arg1 = /* get from appropriate register */;
    int arg2 = /* get from appropriate register */;
    int arg3 = /* get from appropriate register */;
    
    // Call the actual syscall handler
    int result = handle_syscall_impl(syscall_number, arg1, arg2, arg3);
    
    // Store result in appropriate register
}

int handle_syscall_impl(int syscall_number, int arg1, int arg2, int arg3) {
    if (syscall_number >= 0 && syscall_number < 256 && syscall_table[syscall_number] != NULL) {
        return syscall_table[syscall_number](arg1, arg2, arg3);
    } else {
        // Handle unknown system call
        return -1;
    }
}
