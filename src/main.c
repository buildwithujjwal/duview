#include <stdio.h> // Standard I/O functions
#include "tree.h"  // declarations of Struct node and functions signatures
#include "sort.h"

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    Node root = build_tree(path, path);
    sort_tree(&root);
    print_tree(&root, 0);
    free_tree(&root);

    return 0;
}