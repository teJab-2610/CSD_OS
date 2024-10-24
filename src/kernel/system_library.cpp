#include "../drivers/keyboard.cpp"
#include "../drivers/display.cpp"
#include "interrupt.cpp"
char* readKeyboardInput() {
    //Raise interrupt for keyboard
    raise_interrupt(InterruptType::KEYBOARD_INTERRUPT);
    //Read the keyboard buffer
    char* buffer;
    getBuffer(buffer);
    return buffer;
}

int displayToScreen(char* buffer) {
    //Raise interrupt for display
    raise_interrupt(InterruptType::DISPLAY_INTERRUPT);
    //Return 1 if successful, 0 if not
    return display_buffer(buffer);
}
