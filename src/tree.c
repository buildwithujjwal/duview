#include <stdio.h>    // Standard I/O functions
#include <stdlib.h>   // malloc(), free()
#include <string.h>   // strcmp(), strncpy()
#include <dirent.h>   // Directory handling functions and structures
#include <sys/stat.h> // stat() and struct stat for file metadata

typedef struct Node {
    char name[256];
    long long size;
    int is_dir;
    int child_count;
    struct Node *children;
} Node;

// Recursively builds a tree node for the given path, including all nested children if it's a directory
Node build_tree(const char *path, const char *name) {
    Node node;
    strncpy(node.name, name, sizeof(node.name) - 1);
    node.name[sizeof(node.name) - 1] = '\0';  // guarantee null-termination
    node.child_count = 0;
    node.children = NULL;

    struct stat info;
    if (stat(path, &info) != 0) {
        node.size = 0;
        node.is_dir = 0;
        return node;
    }

    // it's a plain file: no children, size comes straight from stat
    if (!S_ISDIR(info.st_mode)) {
        node.is_dir = 0;
        node.size = info.st_size;
        return node;
    }

    // it's a directory: open it and build a child node fo revery entry
    node.is_dir = 1;
    node.size = 0;

    DIR *dir = opendir(path);
    if(dir == NULL) {
        return node;
    }

    // First count how many real entries there are ( exluding . and ..);
    struct dirent *entry;
    int count = 0;
    while((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        else count++;
    }

    // Allocate exactly enough space for that many children
    node.children = malloc(sizeof(Node) * count);
    node.child_count = count;

    // Second build each child node
    rewinddir(dir);
    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        node.children[i] = build_tree(full_path, entry->d_name);
        node.size += node.children[i].size; // add size into parent's total
        i++;
    }

    closedir(dir);
    return node;
}

// free all dynamically allocated memory in a tree
void free_tree(Node *node) {
    for (int i = 0; i < node->child_count; i++) {
        free_tree(&node->children[i]);
    }
    free(node->children);
}
// debig print: shoes the tree with indentation per depth level
void print_tree(Node *node, int depth) {
    for (int i = 0; i < depth; i++) printf(" ");
    printf("%s%s - %lld bytes\n", node->name, node->is_dir ? "/" : "", node->size);

    for (int i = 0; i < node->child_count; i++) {
        print_tree(&node->children[i], depth + 1);
    }
}

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    Node root = build_tree(path, path);
    print_tree(&root, 0);
    free_tree(&root);

    return 0;
}
