#include <conio.h>    // _getch() - read a single keypress instantly
#include <windows.h>  // Windows Console API - for enabeling ANSI support
#include "terminal.h"

void enable_ansi_support(void) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(console, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console, mode);
}

int read_key(void) {
    int ch = _getch();

    // Arrow keys arrive as two bytes: 0xE0 (prefix) then the actual code
    if (ch == 0xE0) {
        int second = _getch();
        if (second == 72) return KEY_UP;    // up arrow
        if (second == 80) return KEY_DOWN;  // down arrow
        return -1; // some other special key we're not handling yet
    }

    if (ch == 13) return KEY_ENTER;     // Enter key
    if (ch == 8)  return KEY_BACK;      // Backspace
    if (ch == 'q' || ch == 'Q') return KEY_QUIT;

    return ch; // any regular character key
}