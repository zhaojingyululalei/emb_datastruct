

#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include "ds_comm.h"

#define HASH_TABLE_SIZE 256  // 哈希桶的数量

// 哈希节点
typedef struct _hash_node_t {
    struct _hash_node_t *next;
} hash_node_t;

// 哈希表
typedef struct _hash_table_t {
    hash_node_t *buckets[HASH_TABLE_SIZE];  // 哈希桶（静态数组）
    int (*hash_func)(const void*);         // 哈希函数
    int (*compare)(const void*, const void*); // 比较函数
    hash_node_t* (*get_node)(const void*); // 获取 `hash_node_t` 的回调
    void* (*get_parent)(hash_node_t*);     // 获取完整结构体的回调
} hash_table_t;

// 哈希表操作
void hash_table_init(hash_table_t *table, uintptr_t hash_func, uintptr_t compare, uintptr_t get_node, uintptr_t get_parent);
int hash_table_insert(hash_table_t *table, void *data);
void* hash_table_find(hash_table_t *table, const void *key);
int hash_table_remove(hash_table_t *table, const void *key);

#endif


