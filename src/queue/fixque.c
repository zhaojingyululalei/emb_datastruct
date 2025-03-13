#include "queue/fixque.h"
#include <string.h>
#include <stdint.h>
/**
 * 初始化队列
 * @param que 队列指针
 * @param buffer 用户提供的存储数组
 * @param element_size 单个元素的大小
 * @param capacity 队列容量
 */
void fixque_init(fixque_t *que, void *buffer, size_t element_size, int capacity,uintptr_t assign_callback) {
    que->head = 0;
    que->tail = 0;
    que->capacity = capacity;
    que->count = 0;
    que->element_size = element_size;
    que->buffer = buffer;
    que->assign_callback = assign_callback;  // 默认不使用回调
}

/**
 * 判断队列是否为空
 */
int fixque_is_empty(fixque_t *que) {
    return que->count == 0;
}

/**
 * 判断队列是否已满
 */
int fixque_is_full(fixque_t *que) {
    return que->count == que->capacity;
}

/**
 * 入队操作（通用类型）
 */
int fixque_enqueue(fixque_t *que, const void *value) {
    if (fixque_is_full(que)) {
        return 0;  // 队列满，无法入队
    }

    void *dest = (char*)que->buffer + (que->tail * que->element_size);  // 计算存储位置

    if (que->assign_callback) {
        que->assign_callback(dest, value);  // 使用自定义回调赋值
    } else {
        memcpy(dest, value, que->element_size);  // 默认使用 memcpy
    }

    que->tail = (que->tail + 1) % que->capacity;  // 更新尾部索引
    que->count++;
    return 1;
}

/**
 * 出队操作（通用类型）
 */
int fixque_dequeue(fixque_t *que, void *value) {
    if (fixque_is_empty(que)) {
        return 0;  // 队列为空
    }

    void *src = (char*)que->buffer + (que->head * que->element_size);  // 计算出队位置
    memcpy(value, src, que->element_size);  // 复制数据

    que->head = (que->head + 1) % que->capacity;  // 更新头部索引
    que->count--;
    return 1;
}