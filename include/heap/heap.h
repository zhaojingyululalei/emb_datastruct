#ifndef __HEAP_H
#define __HEAP_H

#include "ds_comm.h"

// 堆结构体
typedef struct _heap_t {
    void* buffer;            // 存储元素的数组
    int count;               // 当前元素数量
    int capacity;            // 堆容量
    size_t element_size;     // 单个元素大小
    int (*compare)(const void*, const void*);  // 比较函数回调
    void* (*alloc_elem)(void); //分配元素回调函数
    void (*free_elem)(void*);//释放元素回调函数
} heap_t;

// 初始化堆
int heap_init(heap_t *heap, void *buffer, size_t element_size, int capacity, uintptr_t compare,uintptr_t alloc_elem,uintptr_t free_elem);

// 堆操作
int heap_is_empty(heap_t *heap);
int heap_is_full(heap_t *heap);
int heap_insert(heap_t *heap, const void *value);
int heap_pop(heap_t *heap, void *out_value);
void heap_clear(heap_t *heap);

#endif // __HEAP_H
