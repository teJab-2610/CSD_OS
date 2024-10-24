#ifndef KERNEL_SYSCALLS_H
#define KERNEL_SYSCALLS_H
#include <stdint.h>
#include <stddef.h>

/*
This syscalls.h file includes:
An enum SyscallNumbers that defines the system call numbers. These numbers are used to identify which system call is being invoked.
Function prototypes for each system call. These functions will be implemented in the kernel to handle the actual system call operations.
A handle_syscall function prototype. This function will be called by the system call interrupt handler to dispatch the appropriate system call based on the syscall number.
Here's a brief explanation of each system call:
sys_exit: Terminates the current process.
sys_fork: Creates a new process by duplicating the calling process.
sys_read: Reads from a file descriptor into a buffer.
sys_write: Writes from a buffer to a file descriptor.
sys_open: Opens a file and returns a file descriptor.
sys_close: Closes a file descriptor.
sys_yield: Voluntarily gives up the CPU, allowing other processes to run.
sys_getpid: Returns the process ID of the calling process.
*/

// System call numbers
enum SyscallNumbers {
    SYS_EXIT = 1,
    SYS_FORK = 2,
    SYS_READ = 3,
    SYS_WRITE = 4,
    SYS_OPEN = 5,
    SYS_CLOSE = 6,
    SYS_YIELD = 7,
    SYS_GETPID = 8,
    // Add more system calls as needed
};

// Initialize the system call infrastructure
void syscalls_init(void);

// System call function prototypes
void sys_exit(int status);
int sys_fork(void);
int sys_read(int fd, void *buf, size_t count);
int sys_write(int fd, const void *buf, size_t count);
int sys_open(const char *pathname, int flags);
int sys_close(int fd);
void sys_yield(void);
int sys_getpid(void* unused);

// System call handler
int handle_syscall(int syscall_number, int arg1, int arg2, int arg3);

#endif // KERNEL_SYSCALLS_H