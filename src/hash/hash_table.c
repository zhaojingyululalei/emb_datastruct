#include "hash/hash_table.h"
#include "test.h"


#include <string.h>  // memcpy

/**
 * 初始化哈希表
 */
void hash_table_init(hash_table_t *table, uintptr_t hash_func, uintptr_t compare, uintptr_t get_node, uintptr_t get_parent) {
    memset(table->buckets, 0, sizeof(table->buckets));
    table->hash_func = (int (*)(const void*))hash_func;
    table->compare = (int (*)(const void*, const void*))compare;
    table->get_node = (hash_node_t* (*)(const void*))get_node;
    table->get_parent = (void* (*)(hash_node_t*))get_parent;
}

/**
 * 插入数据
 */
int hash_table_insert(hash_table_t *table, void *data) {
    int index = table->hash_func(data) % HASH_TABLE_SIZE;  // 计算哈希值
    hash_node_t *node = table->get_node(data);
    node->next = table->buckets[index];  // 头插法
    table->buckets[index] = node;
    return 1;
}

/**
 * 查找数据
 */
void* hash_table_find(hash_table_t *table, const void *key) {
    int index = table->hash_func(key) % HASH_TABLE_SIZE;
    hash_node_t *node = table->buckets[index];

    while (node) {
        void *parent = table->get_parent(node);
        if (table->compare(key, parent) == 0) {
            return parent;
        }
        node = node->next;
    }
    return NULL;  // 未找到
}

/**
 * 删除数据
 */
int hash_table_remove(hash_table_t *table, const void *key) {
    int index = table->hash_func(key) % HASH_TABLE_SIZE;
    hash_node_t **prev = &table->buckets[index];
    hash_node_t *node = *prev;

    while (node) {
        void *parent = table->get_parent(node);
        if (table->compare(key, parent) == 0) {
            *prev = node->next;  // 删除节点
            return 1;
        }
        prev = &node->next;
        node = node->next;
    }
    return 0;  // 未找到
}
