#ifndef __RB_TREE_H
#define __RB_TREE_H


#include "ds_comm.h"
#define rb_node_parent(node, parent_type, node_name)   \
        ((parent_type *)(node ? offset_to_parent((node), parent_type, node_name) : 0))


// 颜色定义
typedef enum { RED, BLACK } rb_color_t;

// 红黑树节点结构（不存储 `void* data`，通过 `offset_to_parent` 获取）
typedef struct _rb_node_t {
    struct _rb_node_t *left, *right, *parent;
    rb_color_t color;
    int count;    // 相同元素计数
} rb_node_t;

// 红黑树结构
typedef struct _rb_tree_t {
    rb_node_t *root;           // 根节点
    rb_node_t *nil;            // 哨兵节点（NULL替代）
    int count;                 // 记录总节点数
    int capacity;              // 最大容量
    int (*compare)(const void*, const void*);  // **通用比较回调**
    rb_node_t* (*get_node)(const void*);  // **获取节点回调**
    void* (*get_parent)(rb_node_t*); //获取父结构
} rb_tree_t;

// 红黑树操作
void rb_tree_init(rb_tree_t *tree, int capacity, uintptr_t compare, uintptr_t get_node,uintptr_t get_parent);
int rb_tree_insert(rb_tree_t *tree, void *data);
int rb_tree_remove(rb_tree_t *tree, void *data);
rb_node_t* rb_tree_find(rb_tree_t *tree, const void *data);
void rb_tree_clear(rb_tree_t *tree);
void rb_tree_inorder(rb_tree_t *tree,rb_node_t *node, void (*print)(const void*));

#endif