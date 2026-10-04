#ifndef TREE_H
#define TREE_H

typedef struct Node {
    char name[256];
    long long size;
    int is_dir;
    int child_count;
    struct Node *children;
} Node;

// Recursively builds a tree for the given path.
Node build_tree(const char *path, const char *name);

// Frees all dynamically-allocated memory in a tree.
void free_tree(Node *node);

// Debug: prints the tree with indentation per depth level.
void print_tree(Node *node, int depth);

#endif