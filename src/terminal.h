#ifndef TERMINAL_H
#define TERMINAL_H

// Enables ANSI escape code support in the Windows console (needed for cursor movement and color later).
void enable_ansi_support(void);

// Reads one keypress and returns a simple code identifying it. Handles regular keys directly; arrow keys are detected and translated into easy-to-check constants.
int read_key(void);

// key codes returned by read_key() for special keys
#define KEY_UP     1000
#define KEY_DOWN   1002
#define KEY_ENTER  1003
#define KEY_BACK   1004
#define KEY_QUIT   1005

#endif
