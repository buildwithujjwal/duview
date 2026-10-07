#include <stdio.h>
#include "tree.h"      // build_tree(), free_tree()
#include "sort.h"      // sort_tree()
#include "terminal.h"  // enable_ansi_support(), read_key(), KEY_QUIT
#include "ui.h"        // render()

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    enable_ansi_support();

    // Scan and sort, same as before
    Node root = build_tree(path, path);
    sort_tree(&root);

    // Draw once, then wait until the user presses q
    render(&root);

    int key;
    do {
        key = read_key();
    } while (key != KEY_QUIT);

    free_tree(&root);
    return 0;
}