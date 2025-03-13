#include "heap/heap.h"
#include "debug.h"
/**
 * 初始化堆
 */
int heap_init(heap_t *heap, void *buffer, size_t element_size, int capacity, uintptr_t compare,uintptr_t alloc_elem,uintptr_t free_elem) {
    if(!compare||!alloc_elem ||!free_elem){
        dbg_error("compare func or alloc_elem func or free_elem is null\n");
        return -1;
    }
    heap->buffer = buffer;
    heap->count = 0;
    heap->capacity = capacity;
    heap->element_size = element_size;
    heap->compare = compare;
    heap->alloc_elem = alloc_elem;
    heap->free_elem = free_elem;
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
    void *buffer = heap->buffer;
    
    void*temp = heap->alloc_elem();
    void *a = (char*)buffer + i * heap->element_size;
    void *b = (char*)buffer + j * heap->element_size;

    memcpy(temp, a, heap->element_size);
    memcpy(a, b, heap->element_size);
    memcpy(b, temp, heap->element_size);
    heap->free_elem(temp);
    
}

/**
 * 上浮调整（用于插入）
 */
static void heap_sift_up(heap_t *heap, int index) {
    void *buffer = heap->buffer;
    int parent = (index - 1) / 2;
    
    while (index > 0 && heap->compare((char*)buffer + index * heap->element_size, (char*)buffer + parent * heap->element_size) < 0) {
        heap_swap(heap, index, parent);
        index = parent;
        parent = (index - 1) / 2;
    }
}

/**
 * 下沉调整（用于删除）
 */
static void heap_sift_down(heap_t *heap, int index) {
    void *buffer = heap->buffer;
    int left, right, smallest;
    
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < heap->count && heap->compare((char*)buffer + left * heap->element_size, (char*)buffer + smallest * heap->element_size) < 0) {
            smallest = left;
        }

        if (right < heap->count && heap->compare((char*)buffer + right * heap->element_size, (char*)buffer + smallest * heap->element_size) < 0) {
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
int heap_insert(heap_t *heap, const void *value) {
    if (heap_is_full(heap)) return 0;

    void *dest = (char*)heap->buffer + heap->count * heap->element_size;
    memcpy(dest, value, heap->element_size);
    heap_sift_up(heap, heap->count);
    heap->count++;
    return 1;
}

/**
 * 删除堆顶元素
 */
int heap_pop(heap_t *heap, void *out_value) {
    if (heap_is_empty(heap)) return 0;

    void *buffer = heap->buffer;
    memcpy(out_value, buffer, heap->element_size);

    heap->count--;
    memcpy(buffer, (char*)buffer + heap->count * heap->element_size, heap->element_size);
    heap_sift_down(heap, 0);

    return 1;
}

/**
 * 清空堆
 */
void heap_clear(heap_t *heap) {
    heap->count = 0;
}