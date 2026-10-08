#include <stdio.h>
#include "tree.h"      // build_tree(), free_tree()
#include "sort.h"      // sort_tree()
#include "terminal.h"  // enable_ansi_support(), read_key(), KEY_QUIT
#include "ui.h"        // render()

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    enable_ansi_support();

    setvbuf(stdout, NULL, _IOFBF, 1 << 16);  // buffer output so each frame appears at once
    printf("\033[2J");                        // clear the screen once, at startup

    // Scan and sort, same as before
    Node root = build_tree(path, path);
    sort_tree(&root);

        Node *current = &root;  // the folder currently shown on screen
    int selected = 0;       // index of the highlighted entry
    int scroll = 0;         // index of the first entry shown on screen
    int key;

    do {
        render(current, selected, &scroll);
        key = read_key();

        // Move the selection, staying inside the list
        if (key == KEY_UP && selected > 0) selected--;
        if (key == KEY_DOWN && selected < current->child_count - 1) selected++;

        // Enter: open the highlighted entry if it is a non-empty folder
        if (key == KEY_ENTER && current->child_count > 0) {
            Node *target = &current->children[selected];
            if (target->is_dir && target->child_count > 0) {
                current = target;
                selected = 0;
                scroll = 0;
            }
        }
    } while (key != KEY_QUIT);


    free_tree(&root);
    return 0;
}