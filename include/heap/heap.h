#ifndef __HEAP_H
#define __HEAP_H

#include "ds_comm.h"

// 堆结构体
typedef struct _heap_t {
    void** buffer;         // 存储指针的数组
    int count;             // 当前元素数量
    int capacity;          // 堆容量
    int (*compare)(const void*, const void*);  // 比较函数回调
} heap_t;

// 堆 API
int heap_init(heap_t *heap, void **buffer, int capacity, 
              int (*compare)(const void*, const void*));

int heap_is_empty(heap_t *heap);
int heap_is_full(heap_t *heap);
int heap_insert(heap_t *heap, void *value);
int heap_pop(heap_t *heap, void **out_value);

#endif // __HEAP_H
