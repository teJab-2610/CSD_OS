#ifndef GLOBALS_H
#define GLOBALS_H

// System modes
enum class SystemMode {
    KERNEL_MODE,
    USER_MODE
};

//Types of interrupts
enum class InterruptType {
    KEYBOARD_INTERRUPT,
    DISPLAY_INTERRUPT,
    DISK_INTERRUPT,
    NETWORK_INTERRUPT,

    //Exceptions
    DIVISION_BY_ZERO_EXCEPTION,
    INVALID_OPCODE_EXCEPTION
};

//Status of processes
enum class ProcessStatus {
    RUNNING,
    WAITING,
    READY
};

//Current running process ID
int current_process_id;

// Control and Status registers
int MSTATUS; // Machine status register
int MISA; // Machine ISA register
int MEDELEG; // Machine exception delegation register
int MIDELEG; // Machine interrupt delegation register
int MIE; // Machine interrupt-enable register
int MTVEC; // Machine trap-handler base address
int MSCRATCH; // Scratch register for machine trap handlers
int MEPC; // Machine exception program counter
int MCAUSE; // Machine trap cause
int MTVAL; // Machine bad address or instruction
int MIP; // Machine interrupt pending

//Control codes
#define CTRL_CODE_BACKSPACE 0x08
#define CTRL_CODE_ENTER 0x0A

#define CTRL_CODE_CTRL 0x11
#define CTRL_CODE_ALT 0x12
#define CTRL_CODE_SHIFT 0x10
#define CTRL_CODE_CAPSLOCK 0x14
#define CTRL_CODE_BACKSPACE 0x08

SystemMode current_mode;

#endif // GLOBALS_H
