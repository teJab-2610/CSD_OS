#include "../include/kernel/globals.h"
#include "../include/kernel/process.h"

#include "../drivers/keyboard.cpp"
int handle_keyboard_interrupt(){
    //TODO: Buffer will be a fixed location in the memory where other processes will read from.
    char* buffer;
    getBuffer(buffer);
    return 1;   
}

int handle_division_by_zero_exception(){
    return 1;
}

int handle_invalid_opcode_exception(){
    return 1;
}

int find_isr(InterruptType interrupt) {
    if (interrupt == InterruptType::KEYBOARD_INTERRUPT)
        return handle_keyboard_interrupt();
    else if (interrupt == InterruptType::DIVISION_BY_ZERO_EXCEPTION)
        return handle_division_by_zero_exception();
    else if (interrupt == InterruptType::INVALID_OPCODE_EXCEPTION)
        return handle_invalid_opcode_exception();
    else
        return 0;
}


int handle_interrupt(InterruptType interrupt){
    //Save the state of the current process
    pause_process(current_process_id);
    //Find the ISR for the interrupt type
    int isr = find_isr(interrupt);
    //Resume the process
    resume_process(current_process_id);
    return isr;
}

int interrupt_recieved(InterruptType interrupt_type) {
    if (current_mode == SystemMode::USER_MODE) {
        current_mode = SystemMode::KERNEL_MODE;
        MSTATUS |= 0x8;
        if (handle_interrupt(interrupt_type)) {
            //Interrupt handled successfully
            return 1;
        } else {
            //Interrupt not handled
            return 0;
        }
    } else {
        //Ignore the interrupt since we are in kernel mode
        return 0;
    }
} 

//Raise an interrupt
int raise_interrupt(InterruptType interrupt_type) {
    int interrupt_acknowledged = interrupt_recieved(interrupt_type);
    return interrupt_acknowledged;
}
