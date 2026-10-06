#include <stdlib.h>  //qsort()
#include "sort.h"

// qsort gives us generic (void *) pointers, so first cast them back to what they actually are - Node pointers.
static int compare_by_size_desc(const void *a, const void *b) {
    const Node *node_a = (const Node *)a;
    const Node *node_b = (const Node *)b;

    if (node_b->size > node_a->size) return 1;
    if (node_b->size < node_a->size) return -1;
    return 0;
}

void sort_tree(Node *node) {
    // Sort this node's own children by size, largest first
    if (node->child_count > 0) {
        qsort(node->children, node->child_count, sizeof(Node), compare_by_size_desc);
    }

    // Recurse: sort each child's children too
    for (int i = 0; i < node->child_count; i++) {
        sort_tree(&node->children[i]);
    }
}