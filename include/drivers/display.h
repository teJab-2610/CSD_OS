#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

// Constants
#define ROW_CHAR_SIZE 80
#define COLUMN_CHAR_SIZE 60
#define SCREEN_LOCK 0x00
#define MUL_CONS 9

// Global variables
extern int LINE;
extern int COLUMN;
extern int focus_mode;
extern int focus_mode_col;

// Function prototypes
int write_char(char c);
int write_char_at(char c, int line, int col);
void save_screen();
int write_int(int a);
int write_string(char* msg, int len);
int write_string_at(char* msg, int len, int line, int col);
int set_cursor_pos(int line, int col);
void get_cursor_pos(int* vals);
int write_string_at_col(char* msg, int len, int line, int col);
int write_zero_line_at(int line);
int write_zero_line();
void write_char_last_line(char c);
void write_face(char font[128][16]);
int display_up();
int display_down();
void clear_screen();
int focus_info_panel();
void retrieve_screen();
int set_fontmap(char* filename, int len);
void save_memory(char* filename, int len);

#endif // DISPLAY_H























// #ifndef DISPLAY_H
// #define DISPLAY_H

// #include <stdbool.h>

// #define ROW_CHAR_SIZE 80
// #define COLUMN_CHAR_SIZE 60
// #define SCREEN_LOCK 0x00

// // Existing function prototypes
// int write_char(char c);
// int write_char_at(char c, int line, int col);
// int write_string(char* msg, int len);
// int write_string_at(char* msg, int len, int line, int col);
// int write_int(int a);
// int set_cursor_pos(int line, int col);
// void get_cursor_pos(int* vals);
// int write_zero_line_at(int line);
// int write_zero_line();
// int display_up();
// int display_down();
// void clear_screen();
// void save_screen();
// void retrieve_screen();

// // New function prototypes for shapes and game-related functions
// void draw_pixel(int x, int y, char symbol);
// void clear_pixel(int x, int y);
// void draw_rectangle(int x1, int y1, int x2, int y2, char symbol);
// void draw_line(int x1, int y1, int x2, int y2, char symbol);
// void fill_rectangle(int x1, int y1, int x2, int y2, char symbol);
// void draw_circle(int x, int y, int radius, char symbol);
// int random(int min, int max);

// #endif // DISPLAY_H