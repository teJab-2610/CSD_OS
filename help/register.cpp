/**
 * Register: Regiter stores the value of all risc-v registers.
*/

//General purpose registers
int R0;
int R1;
int R2;
int R3;
int R4;
int R5;
int R6;
int R7;
int R8;
int R9;
int R10;
int R11;
int R12;
int R13;
int R14;
int R15;

//Floating point registers
int F0;
int F1;
int F2;
int F3;
int F4;
int F5;

//Special Purpose Registers
int PC; //Program Counter
int SP; //Stack Pointer
int GP; //Global Pointer
int FP; //Frame Pointer
int RA; //Return Address

//Control and Status Registers
int MSTATUS;
int MIE;
int MTVEC;
int MEPC;
int MCAUSE;
int MTVAL;
int MIP;

//Machine Trap Cause Values
#define CAUSE_INTERRUPT 0x80000000
#define CAUSE_EXCEPTION 0x80000001
#define CAUSE_ILLEGAL_INSTRUCTION 0x80000002
#define CAUSE_BREAKPOINT 0x80000003
#define CAUSE_LOAD_ADDRESS_MISALIGNED 0x80000004
#define CAUSE_STORE_ADDRESS_MISALIGNED 0x80000005
#define CAUSE_LOAD_ACCESS_FAULT 0x80000006
#define CAUSE_STORE_ACCESS_FAULT 0x80000007
#define CAUSE_USER_SOFTWARE_INTERRUPT 0x80000008
#define CAUSE_SUPERVISOR_SOFTWARE_INTERRUPT 0x80000009


