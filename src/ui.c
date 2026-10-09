#include <stdio.h>  // printf(), snprintf()
#include "ui.h"
#include "terminal.h"

// Moves the cursor to the top-left without blanking the screen.
// Drawing over the old frame avoids the flicker a full clear causes.
static void cursor_home(void) {
    printf("\033[H");
}

// Converts a byte count into a short readable string, e.g. "4.6 MB".
// The caller supplies the buffer, so we never malloc here.
static void format_size(long long bytes, char *buf, size_t buf_size) {
    const char *units[] = {"B", "KB", "MB", "GB", "TB"};
    double value = (double)bytes;
    int unit = 0;

    // Divide by 1024 until the number is small enough to read
    while (value >= 1024.0 && unit < 4) {
        value /= 1024.0;
        unit++;
    }

    // Plain bytes have no fraction, so print them as an integer
    if (unit == 0) snprintf(buf, buf_size, "%lld B", bytes);
    else           snprintf(buf, buf_size, "%.1f %s", value, units[unit]);
}

void render(Node *node, int selected, int *scroll) {
    int visible = get_terminal_rows() - 5;
    if (visible < 1) visible = 1;

    if (selected < *scroll) *scroll = selected;
    if (selected >= *scroll + visible) *scroll = selected - visible + 1;

    cursor_home();

        char total[32];
    format_size(node->size, total, sizeof(total));
    printf("%s  (%s)\033[K\n", node->name, total);
    printf("------------------------------------------------------------\033[K\n");

    int end = *scroll + visible;
    if (end > node->child_count) end = node->child_count;

    for (int i = *scroll; i < end; i++) {
        Node *child = &node->children[i];

        char label[300];
        snprintf(label, sizeof(label), "%s%s", child->name, child->is_dir ? "/" : "");

        if (i == selected) printf("\033[7m");

        char size_text[32];
        format_size(child->size, size_text, sizeof(size_text));
        printf("  %-40.40s %10s", label, size_text);

        if (i == selected) printf("\033[0m");
        printf("\033[K\n");
    }

    printf("------------------------------------------------------------\033[K\n");
    printf("Up/Down: move   Enter: open   Backspace: back   q: quit\033[K\n");

    // \033[J erases everything below the last line (old rows from a longer list)
    printf("\033[J");

    // Push the whole frame to the screen at once
    fflush(stdout);
}