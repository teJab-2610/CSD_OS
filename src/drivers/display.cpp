/**
 * Memory size is 200kB
 * Display size is 1024 * 600 pixels. 
 *
 * Number of characters: 80 (CHARS) X 60
 *
 * 80 characters row wise (12 pixels horizontally)
 * 45 characters column wise (13 pixels vertically)
 *
 * IO_DISPLAY_START = 0
 * display_start = 0
 * IO_DISPLAY_SIZE = 29000 lines (size of display io in bits map divided by 8)
 * display_end = 29000
 * keyboard_start = 29000
 *
 * 80 X 45 X 8 bytes = 28800 bytes 
 *
 * Memory size: 200 kB
 *
 *  display => 29 kB
 *  fontmap => 2kB
 *  temp    => 10kB
 *
 * Fontmap (8x8 pixels represented by 8 bytes):
 *  128 -> 1kilo byte
 *  256 -> 2kilo bytes
 *
 *  All the extra pixels other than 8*8 can be said for padding.
 *  
 *  Presently we have support for 128 ascii codes, but we have reserved other 128 for future purpose.
 */

#include <stdbool.h>
#include <cstring>
#include <iostream>

#include "../../include/drivers/display.h"
#include "../../include/kernel/globals.h"
// #include "keyboard.cpp"
#include "../../include/drivers/font.h"
#include "../../include/kernel/memory.h"


const int max_com_len = 10; // max command length

int LINE = 0;   // current row
int COLUMN = 0; // current column

int focus_mode = 0;
int focus_mode_col = 0;

int write_char(char c);
int write_char_at(char c, int line, int col);
void save_screen();
int write_int(int a);

/**
 * @brief write string array in to the display location currently at.
 * @returns returns 0 on success, otherwise failure. Failure occurs when the fontmap doesn't exist
 * @note supports word wrapping
 */
int write_string(char* msg, int len)
{
    if (SCREEN_LOCK == 0)
    {
        int g = 0;
        for (int i = 0; i < len; i++)
        {
            g = write_char(msg[i]);

            if (g != 0)
            {
                return g;
            }
        }
        return 0;
    }
}

int write_string_at(char* msg, int len, int line, int col)
{
    int g = 0;
    for (int i = 0; i < len; i++)
    {
        g = write_char_at(msg[i], line, col);
        if (g != 0)
        {
            return g;
        }

        col++;
        if (col == ROW_CHAR_SIZE)
        {
            col = 0;
            line += 8;
        }

        if (line == 8 * COLUMN_CHAR_SIZE)
        {
            line = 0;
            col = 0;

            return 1;
        }
    }
    return 0;
}

int write_int(int a) {
    if (SCREEN_LOCK == 0) {
        char temp[10];
        int count = 0;
        while (a > 0) {
            temp[count++] = (a % 10) + '0';
            a /= 10;
        }

        for (int i = count - 1;i >= 0;i--) {
            write_char(temp[i]);
        }

        return 0;
    }

    return 1;
}

int set_cursor_pos(int line, int col)
{
    if (line < 0 || line >= 8 * COLUMN_CHAR_SIZE)
        return 1;
    if (col < 0 || col >= ROW_CHAR_SIZE)
        return 1;

    LINE = line;
    COLUMN = col;

    return 0;
}

void get_cursor_pos(int* vals)
{
    vals[0] = LINE;
    vals[1] = COLUMN;
}

int write_string_at_col(char* msg, int len, int line, int col)
{
    if (SCREEN_LOCK == 0)
    {
        if (line >= 8 * COLUMN_CHAR_SIZE)
            return 1;
        if (col >= ROW_CHAR_SIZE || col < 0)
            return 1;

        int g = 0;
        for (int i = 0; i < len; i++)
        {
            g = write_char_at(msg[i], line, col);
            if (g != 0)
            {
                return g;
            }

            line += 8;

            if (line == 8 * COLUMN_CHAR_SIZE)
            {
                line = 0;
                col = 0;

                return 1;
            }

            if (col == ROW_CHAR_SIZE)
            {
                col = 0;
                line += 8;
            }
        }
    }

    return 1;
}

int write_zero_line_at(int line)
{
    if (SCREEN_LOCK == 0)
    {
        if (line < 0 || line >= 8 * COLUMN_CHAR_SIZE)
            return 1;

        int A = IO_DISPLAY_START + ROW_CHAR_SIZE * line;
        for (int i = 0; i < ROW_CHAR_SIZE * 8; i++)
        {
            mwrite(0, A + i);
        }

        return 0;
    }

    return 1;
}

int write_zero_line()
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE;
        for (int i = 0; i < ROW_CHAR_SIZE * 8; i++)
        {
            mwrite(0, A + i);
        }

        return 0;
    }

    return 1;
}

/**
 * @brief write_char writes a character included in fontmap at the last location
 * @note takes care of word wrapping
 * @returns 1 if not able to write else 0
 */
int write_char(char c){
    if (SCREEN_LOCK == 0){
        if (c == '\n'){
            COLUMN = 0;
            LINE += 8;
            if (LINE == 8 * COLUMN_CHAR_SIZE){
                LINE = 0;
                COLUMN = 0;
                return 1;
            }
            return 0;
        }
        else if (c == '_') {
            COLUMN++;

            if (COLUMN == ROW_CHAR_SIZE)
            { // if the row is full
                COLUMN = 0;
                LINE += 8;
                if (LINE >= 8 * COLUMN_CHAR_SIZE)
                {
                    LINE = 0;
                    COLUMN = 0;
                    return 1;
                }
            }
        }
        else if (c == '\r')
        {
            COLUMN = 0;
            return 0;
        }
        else if (c == '\f')
        {
            LINE += 8;
            if (LINE >= 8 * COLUMN_CHAR_SIZE)
            {
                LINE = 0;
                COLUMN = 0;
                return 1;
            }

            return 0;
        }
        else if (c == '\t')
        {
            COLUMN += 4;
            if (COLUMN >= ROW_CHAR_SIZE)
            {
                COLUMN = 0;
                LINE += 8;
                if (LINE >= 8 * COLUMN_CHAR_SIZE)
                {
                    LINE = 0;
                    COLUMN = 0;
                    return 1;
                }
            }

            return 0;
        }
        else if (c == CTRL_CODE_BACKSPACE)
        {
            if (COLUMN == 0)
            {
                if (LINE == 0)
                {
                    return 0;
                }
                else
                {
                    COLUMN = ROW_CHAR_SIZE - 1;
                    LINE -= 8;
                }
            }
            else
            {
                COLUMN--;
            }

            int A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE + COLUMN;
            for (int i = 0; i < 8; i++)
            {
                mwrite(0, A + ROW_CHAR_SIZE * i);
            }

            return 0;
        }
        else
        {
            char font[8];
            
            for (int i = 0; i < 8; i++)
            {
                font[i] = font_map[c][i];
            }
            // for (int i = 0; i < 8; i++)
            // {
            //     printf("%d ", font[i]);
            // }
            // printf("\n");
            int A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE + COLUMN; // location of the first character in the line
            for (int i = 0; i < 8; i++)
            {
                mwrite(font[i], A + ROW_CHAR_SIZE * i);
            }

            COLUMN++;
            if (COLUMN == ROW_CHAR_SIZE)
            { // if the row is full
                COLUMN = 0;
                LINE += 8;
                return 0;
            }

            if (LINE == 8 * COLUMN_CHAR_SIZE)
            { // if the screen is full
                LINE = 0;
                COLUMN = 0;

                return 1;
            }

            return 0;
        }
    }

    return 1;
}

int write_char_at(char c, int line, int col)
{
    if (SCREEN_LOCK == 0)
    {

        if (line < 0 || line >= 8 * COLUMN_CHAR_SIZE)
            return 1;
        if (col < 0 || col >= ROW_CHAR_SIZE)
            return 1;

        char font[8];
        for (int i = 0; i < 8; i++)
        {
            font[i] = font_map[c][i];
        }

        int A = IO_DISPLAY_START + ROW_CHAR_SIZE * line + col; // location of the first character in the line
        for (int i = 0; i < 8; i++)
        {
            mwrite(font[i], A + ROW_CHAR_SIZE * i);
        }

        return 0;
    }

    return 1;
}

void write_char_last_line(char c)
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START + (COLUMN_CHAR_SIZE - 1) * 8 * ROW_CHAR_SIZE;

        // todo: write the character at the last line
    }
}

void write_face(char font[128][16])
{
    if (SCREEN_LOCK == 0)
    {

        LINE += 8;
        COLUMN = 0;

        int A = IO_DISPLAY_START + LINE * ROW_CHAR_SIZE + COLUMN;

        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                mwrite(font[i][j], A + i * ROW_CHAR_SIZE + j);
            }
        }

        LINE += 128;
        COLUMN = 0;

        if (LINE >= 8 * COLUMN_CHAR_SIZE)
        {
            LINE = 0;
            COLUMN = 0;
        }
    }
}

/**
 * \brief Shifts the entire display map by one 1 unit upwards
 */
int display_up()
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START;
        for (int j = 0;j < 8;j++) {
            for (int addr = 0; addr < IO_DISPLAY_SIZE - ROW_CHAR_SIZE; addr++) {
                char temp = mread_char(A + addr + ROW_CHAR_SIZE);
                // reverse temp 
                char temp2 = 0;

                for (int i = 0; i < 8; i++) {
                    if ((temp >> i) & 1) {
                        temp2 |= (1 << (7 - i));
                    }
                }

                mwrite(temp2, A + addr);
            }
        }

        // clear the last line (A)
        for (int i = 0; i < ROW_CHAR_SIZE * 8; i++)
        {
            mwrite(0, A + i);
        }

        // update the current line
        LINE -= 8;
        if (LINE < 0)
        {
            LINE = 0;
        }

        return 0;
    }

    return 1;
}

/**
 * \brief Shifts the entire display map by one 1 unit downwards
 *
 */
int display_down()
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START;

        for (int j = 0;j < 8;j++) {
            for (int addr = IO_DISPLAY_SIZE - ROW_CHAR_SIZE; addr >= 0; addr--) {
                char temp = mread_char(A + addr);
                // reverse temp 
                char temp2 = 0;

                for (int i = 0; i < 8; i++) {
                    if ((temp >> i) & 1) {
                        temp2 |= (1 << (7 - i));
                    }
                }

                mwrite(temp2, A + addr + ROW_CHAR_SIZE);
            }
        }
        // clear the first line (A)
        for (int i = 0; i < ROW_CHAR_SIZE * 8; i++)
        {
            mwrite(0, A + i);
        }

        // update the current line
        LINE += 8;
        if (LINE >= 8 * COLUMN_CHAR_SIZE)
        {
            LINE = 8 * COLUMN_CHAR_SIZE - 1;
        }

        return 0;
    }

    return 1;
}

// reset the entire display
void clear_screen()
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START + IO_DISPLAY_SIZE - 1;
        for (int i = A; i >= IO_DISPLAY_START; i--)
        {
            mwrite(0, i);
        }

        LINE = 0;
        COLUMN = 0;
    }
}

void save_screen()
{
    int A = IO_DISPLAY_START;
    int D = TEMP_START;

    for (int i = 0; i < IO_DISPLAY_SIZE; i++)
    {
        char temp = mread_char(A + i);
        mwrite(D + i, temp);
    }
}

// retrieve the saved screen from the memory after exiting focus mode
void retrieve_screen()
{
    int A = IO_DISPLAY_START;
    int D = TEMP_START;

    for (int i = 0; i < IO_DISPLAY_SIZE; i++)
    {
        char temp = mread_char(D + i);
        mwrite(A + i, temp);
    }
}

int set_fontmap(char* filename, int len)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return 1;
    }
    return 0;
}

int display_buffer(char* buffer) {
   //Display the buffer to the screen
    try {    
       for (int i = 0; i < strlen(buffer); i++) {
           write_char(buffer[i]);
       }
       return 1;
    } catch (int e) {
       return 0;
    }
}
