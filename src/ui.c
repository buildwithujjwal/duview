#include <stdio.h>  // printf(), snprintf()
#include "ui.h"

// Clears the whole screen and moves the cursor to the top-left corner using ANSI escape codes.
static void clear_screen(void) {
    printf("\033[2J\033[H");
}

void render(Node *node) {
    clear_screen();

    // Header: current folder and its total size
    printf("%s  (%lld bytes)\n", node->name, node->size);
    printf("------------------------------------------------------------\n");

    // One line per child, name padded/truncated to a fixed 40-char column
    for (int i = 0; i < node->child_count; i++) {
        Node *child = &node->children[i];

        // Add a trailing "/" to folder names so they stand out from files
        char label[300];
        snprintf(label, sizeof(label), "%s%s", child->name, child->is_dir ? "/" : "");

        printf("  %-40.40s %12lld bytes\n", label, child->size);
    }

    printf("------------------------------------------------------------\n");
    printf("q: quit\n");
}