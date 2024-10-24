#include "../include/kernel/globals.h"
#include "../include/kernel/registers.h"
#include "../include/kernel/memory.h"
#include "../include/drivers/display.h"
#include "../include/drivers/keyboard.h"


//TODO:: Incomplete Process

/**
 *
 * joios:/> [ls| cd <dir> | cat <file> | mkdir <dir> | pwd | clear | exit]
 *
 * dir1\
 *      file1
 *      file2
 * dir2\
 *      file1
 *      file2
*/
char path[20];
int path_len = 0;

void set_path(char* new_path, int len) {
    if (len >= 20) return;

    for (int i = 0;i < len;i++) {
        path[i] = new_path[i];
    }

    path_len = len;
}

void print_new_path() {
    write_char('\n');
    write_string(path, path_len);
}

void ls_on_dir1() {
    write_string("file1 file2", 11);
}

void ls_on_dir2() {
    write_string("file1 file2", 11);
}

void cat_on_dir1_file1() {
    write_string("This is file1 content in dir1", 29);
}

void cat_on_dir1_file2() {
    write_string("This is file2 content in dir1", 29);
}

void cat_on_dir2_file1() {
    write_string("This is file1 content in dir2", 29);
}

void cat_on_dir2_file2() {
    write_string("This is file2 content in dir2", 29);
}

void clear_path() {
    for (int i = 0;i < 20;i++) {
        path[i] = '\0';
    }
}

void terminal() {
    clear_screen();
    set_path("joios:/> ", 11);
    print_new_path();

    char preinput[20];
    int len = 0;

    while (true) {
        char* input;
        readKeyboardInput(input);

        if (*input == '.') {

            printf("preinput: %s\n", preinput);

            if (len == 0) {
                print_new_path();
                continue;
            }

            if (preinput[0] == 'l' && preinput[1] == 's') {
                if (len >= 7 && preinput[3] == 'd' && preinput[4] == 'i' && preinput[5] == 'r' && preinput[6] == '1') {
                    write_char('\n');
                    ls_on_dir1();

                    set_path("joios:/> ", 11);
                    len = 0;
                    print_new_path();
                }
                else if (len >= 7 && preinput[3] == 'd' && preinput[4] == 'i' && preinput[5] == 'r' && preinput[6] == '2') {
                    write_char('\n');
                    ls_on_dir2();

                    set_path("joios:/> ", 11);
                    len = 0;
                    print_new_path();
                }
                else {
                    write_string("\nInvalid directory\n", 19);
                }
            }
            else if (preinput[0] == 'c' && preinput[1] == 'd') {
                if (preinput[3] == 'd' && preinput[4] == 'i' && preinput[5] == 'r' && preinput[6] == '1') {
                    set_path("joios:dir1/> ", 14);
                    print_new_path();
                    len = 0;
                }
                else if (preinput[3] == 'd' && preinput[4] == 'i' && preinput[5] == 'r' && preinput[6] == '2') {
                    set_path("joios:dir2/> ", 14);
                    print_new_path();
                    len = 0;
                }
                else if (preinput[3] == '/') {
                    set_path("joios:/> ", 11);
                    print_new_path();
                    len = 0;
                }
                else {
                    write_string("Invalid directory\n", 18);
                }
            }
            else if (preinput[0] == 'c' && preinput[1] == 'a' && preinput[2] == 't') {
                write_string("cat\n", 4);
            }
            else if (preinput[0] == 'm' && preinput[1] == 'k' && preinput[2] == 'd' && preinput[3] == 'i' && preinput[4] == 'r') {
                write_string("mkdir\n", 6);
            }
            else if (preinput[0] == 'p' && preinput[1] == 'w' && preinput[2] == 'd') {
                write_string("pwd\n", 4);
            }
            else if (preinput[0] == 'e' && preinput[1] == 'x' && preinput[2] == 'i' && preinput[3] == 't') {
                write_string("exit\n", 5);
                break;
            }
            else if (preinput[0] == 'c' && preinput[1] == 'l' && preinput[2] == 'e' && preinput[3] == 'a' && preinput[4] == 'r') {
                clear_screen();
                print_new_path();
            }
            else {
                write_string("\nInvalid command\n", 17);
                print_new_path();
                len = 0;
            }
        }
        else {
            preinput[len] = *input;
            len++;
            write_char(*input);
        }
    }

}
