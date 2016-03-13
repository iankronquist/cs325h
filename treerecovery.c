#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    char value;
    struct node *left, *right;
};

struct node *tree_recovery(char *pre_order, char *in_order, int size);
void post_order_print(struct node *tree);

int main() {
    char *in = "ABCDEFG";
    char *pre = "DBACEGF";
    struct node *result = tree_recovery(in, pre, strlen(in));
    post_order_print(result);
    // Remember kids, the OS does a fine job freeing your memory for you!
    return 0;
}

/*
def tree_recovery(pre, post):
    if len(pre) == 1:
        return Tree(pre[0])
    elif len(pre) == 0:
        return None
    i = 0
    root = pre[0]
    for i, item in enumerate(post):
        if item == root:
            break
    left = tree_recovery(pre[1:i+1], post[:i])
    right = tree_recovery(pre[i+1:], post[i+1:])
    n = Tree(root, left, right)
    return n
    */


struct node *make_node(char v) {
    struct node *n = malloc(sizeof(struct node));
    n->value = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct node *tree_recovery(char *pre_order, char *in_order, int size) {
    int index;
    if (size == 1) {
        return make_node(pre_order[0]);
    } else if (size == 0) {
        return NULL;
    }
    char root = pre_order[0];
    int i;
    for (i = 0; i < size; ++i) {
        if (in_order[i] == root) {
            break;
        }
    }
    struct node *left = tree_recovery(&pre_order[1], in_order, i);
    struct node *right = tree_recovery(&pre_order[i+1], &in_order[i+1], size-i);
    struct node *root_node = make_node(root);
    root_node->left = left;
    root_node->right = right;
    return root_node;
}

void post_order_print(struct node *tree) {
    if (tree == NULL) {
        return;
    }
    post_order_print(tree->left);
    post_order_print(tree->right);
    printf("%c", tree->value);
}
