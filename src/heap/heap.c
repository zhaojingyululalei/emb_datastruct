#include "heap/heap.h"
#include "debug.h"
/**
 * 初始化堆
 */
int heap_init(heap_t *heap, void **buffer, int capacity, 
              int (*compare)(const void*, const void*)) {
    if (!compare ) {
        return -1;
    }
    heap->buffer = buffer;
    heap->count = 0;
    heap->capacity = capacity;
    heap->compare = compare;
    return 0;
}

/**
 * 判断堆是否为空
 */
int heap_is_empty(heap_t *heap) {
    return heap->count == 0;
}

/**
 * 判断堆是否已满
 */
int heap_is_full(heap_t *heap) {
    return heap->count >= heap->capacity;
}

/**
 * 交换堆中的两个元素
 */
static void heap_swap(heap_t *heap, int i, int j) {
    void* temp = heap->buffer[i];
    heap->buffer[i] = heap->buffer[j];
    heap->buffer[j] = temp;
}

/**
 * 上浮调整（用于插入）
 */
static void heap_sift_up(heap_t *heap, int index) {
    int parent = (index - 1) / 2;

    while (index > 0 && heap->compare(heap->buffer[index], heap->buffer[parent]) < 0) {
        heap_swap(heap, index, parent);
        index = parent;
        parent = (index - 1) / 2;
    }
}

/**
 * 下沉调整（用于删除）
 */
static void heap_sift_down(heap_t *heap, int index) {
    int left, right, smallest;

    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < heap->count && heap->compare(heap->buffer[left], heap->buffer[smallest]) < 0) {
            smallest = left;
        }

        if (right < heap->count && heap->compare(heap->buffer[right], heap->buffer[smallest]) < 0) {
            smallest = right;
        }

        if (smallest == index) break;

        heap_swap(heap, index, smallest);
        index = smallest;
    }
}

/**
 * 插入元素到堆
 */
int heap_insert(heap_t *heap, void *value) {
    if (heap_is_full(heap)) return 0;

    
    heap->buffer[heap->count] = value;
    heap_sift_up(heap, heap->count);
    heap->count++;
    return 1;
}

/**
 * 删除堆顶元素
 */
int heap_pop(heap_t *heap, void **out_value) {
    if (heap_is_empty(heap)) return 0;

    *out_value = heap->buffer[0];  // 返回指向实际数据的指针

    heap->count--;
    heap->buffer[0] = heap->buffer[heap->count];
    heap_sift_down(heap, 0);

    return 1;
}

