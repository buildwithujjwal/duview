#ifndef UI_H
#define UI_H

#include "tree.h"

// Clears the screen and draws the folder's entries, highlighting the
// selected row. Updates *scroll so the selected row stays visible.
void render(Node *node, const char *path, int selected, int *scroll);

#endif