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

// Deletes a file or folder (recursively) from disk. Returns 0 on success.
int delete_path(const char *path);

// Removes one child from a node's array and frees its subtree.
void remove_child(Node *parent, int index);

// Frees all dynamically-allocated memory in a tree.
void free_tree(Node *node);

// Debug: prints the tree with indentation per depth level.
void print_tree(Node *node, int depth);

#endif