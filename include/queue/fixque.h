#ifndef __FIXQUE_H
#define __FIXQUE_H
#include "ds_comm.h"
typedef struct _fixque_t {
    int head;          // 头部索引（出队）
    int tail;          // 尾部索引（入队）
    int capacity;      // 队列最大存储容量
    int count;         // 当前元素数量
    int element_size;  // 单个元素大小（支持任意类型）
    void *buffer;      // 数据存储的指针（用户提供）

    // 赋值回调函数
    void (*assign_callback)(void *dest, const void *src);
} fixque_t;

// 初始化队列
void fixque_init(fixque_t *que, void *buffer, size_t element_size, int capacity,uintptr_t assign_callback);

// 队列操作
int fixque_is_empty(fixque_t *que);
int fixque_is_full(fixque_t *que);
int fixque_enqueue(fixque_t *que, const void *value);
int fixque_dequeue(fixque_t *que, void *value);

#endif