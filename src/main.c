#include <stdio.h>
#include "tree.h"

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    Node root = build_tree(path, path);
    print_tree(&root, 0);
    free_tree(&root);

    return 0;
}