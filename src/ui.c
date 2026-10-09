#include <stdio.h>  // printf(), snprintf()
#include "ui.h"
#include "terminal.h"

// Moves the cursor to the top-left without blanking the screen.
// Drawing over the old frame avoids the flicker a full clear causes.
static void cursor_home(void) {
    printf("\033[H");
}

void render(Node *node, int selected, int *scroll) {
    int visible = get_terminal_rows() - 5;
    if (visible < 1) visible = 1;

    if (selected < *scroll) *scroll = selected;
    if (selected >= *scroll + visible) *scroll = selected - visible + 1;

    cursor_home();

    // \033[K at the end of each line erases leftovers from the previous frame
    printf("%s  (%lld bytes)\033[K\n", node->name, node->size);
    printf("------------------------------------------------------------\033[K\n");

    int end = *scroll + visible;
    if (end > node->child_count) end = node->child_count;

    for (int i = *scroll; i < end; i++) {
        Node *child = &node->children[i];

        char label[300];
        snprintf(label, sizeof(label), "%s%s", child->name, child->is_dir ? "/" : "");

        if (i == selected) printf("\033[7m");
        printf("  %-40.40s %12lld bytes", label, child->size);
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