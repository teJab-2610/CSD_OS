#include "ps2_scancode_map.h"

class KeyboardDriver {
    public:
        KeyboardDriver();
        ~KeyboardDriver();

        int keyboardInit();
        void handleKeyPress(unsigned char scanCode);
        void addToBuffer(unsigned char ascii);
        char* getBuffer();
};

