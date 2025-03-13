#include "rb_tree.h"
#include <string.h>  // memcpy

/**
 * 初始化红黑树
 */
void rb_tree_init(rb_tree_t *tree, int capacity, uintptr_t compare, uintptr_t get_node,uintptr_t get_parent) {
    tree->capacity = capacity;
    tree->count = 0;
    tree->compare = (int (*)(const void*, const void*))compare;
    tree->get_node = (rb_node_t* (*)(const void*))get_node;
    tree->get_parent = (void* (*)(rb_node_t*))get_parent;
    // 初始化哨兵节点
    tree->nil = (rb_node_t*)0;  // 空指针作为 NIL
    tree->root = tree->nil;
}

/**
 * 左旋
 */
static void rb_tree_left_rotate(rb_tree_t *tree, rb_node_t *x) {
    rb_node_t *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

/**
 * 右旋
 */
static void rb_tree_right_rotate(rb_tree_t *tree, rb_node_t *y) {
    rb_node_t *x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) tree->root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;
    x->right = y;
    y->parent = x;
}

/**
 * 插入修复
 */
static void rb_tree_insert_fix(rb_tree_t *tree, rb_node_t *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rb_node_t *y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rb_tree_left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rb_tree_right_rotate(tree, z->parent->parent);
            }
        } else {
            rb_node_t *y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rb_tree_right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rb_tree_left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

/**
 * 插入元素
 */
int rb_tree_insert(rb_tree_t *tree, void *data) {
    rb_node_t *node = tree->get_node(data);
    rb_node_t *y = NULL;
    rb_node_t *x = tree->root;

    // 找到插入位置
    while (x) {
        y = x;
        int cmp = tree->compare(data, tree->get_parent(x));
        if (cmp == 0) {
            x->count++;  // 相同元素，增加计数
            return 1;
        }
        x = (cmp < 0) ? x->left : x->right;
    }

    // 连接到树
    node->parent = y;
    node->left = node->right = NULL;
    node->color = RED;
    node->count = 1;

    if (!y) tree->root = node;
    else {
        if (tree->compare(data, tree->get_parent(y)) < 0) y->left = node;
        else y->right = node;
    }

    // 修复树
    rb_tree_insert_fix(tree, node);
    return 1;
}

/**
 * 中序遍历
 */
void rb_tree_inorder(rb_tree_t *tree, rb_node_t *node, void (*print)(const void*)) {
    if (node) {
        rb_tree_inorder(tree, node->left, print);
        print(tree->get_parent(node));
        rb_tree_inorder(tree, node->right, print);
    }
}
