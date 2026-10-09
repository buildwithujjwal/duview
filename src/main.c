#include <stdio.h>
#include "tree.h"      // build_tree(), free_tree()
#include "sort.h"      // sort_tree()
#include "terminal.h"  // enable_ansi_support(), read_key(), KEY_QUIT
#include "ui.h"        // render()

#define MAX_DEPTH 256  // deepest folder nesting we remember for going back

// One remembered position: which folder we were in, and where the cursor was.
typedef struct {
    Node *folder;
    int selected;
    int scroll;
} Frame;

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    enable_ansi_support();

    setvbuf(stdout, NULL, _IOFBF, 1 << 16);  // buffer output so each frame appears at once
    printf("\033[2J");                        // clear the screen once, at startup

    // Scan and sort, same as before
    Node root = build_tree(path, path);
    sort_tree(&root);

        Node *current = &root;      // the folder currently shown on screen
    int selected = 0;           // index of the highlighted entry
    int scroll = 0;             // index of the first entry shown on screen
    Frame history[MAX_DEPTH];   // stack of folders we came from
    int depth = 0;              // how many entries are on the stack
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
            if (target->is_dir && target->child_count > 0 && depth < MAX_DEPTH) {
                // Remember where we are before moving down
                history[depth].folder = current;
                history[depth].selected = selected;
                history[depth].scroll = scroll;
                depth++;

                current = target;
                selected = 0;
                scroll = 0;
            }
        }

        // Backspace: return to the previous folder, if there is one
        if (key == KEY_BACK && depth > 0) {
            depth--;
            current = history[depth].folder;
            selected = history[depth].selected;
            scroll = history[depth].scroll;
        }
    } while (key != KEY_QUIT);


    free_tree(&root);
    return 0;
}