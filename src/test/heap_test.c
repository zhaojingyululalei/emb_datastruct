#include "heap/heap.h"
#include "test.h"
#define STUDENT_MAX_CNT 10
static student_t student_buffer[STUDENT_MAX_CNT];
/**
 * 以 `score` 为依据进行升序排序（最小堆）
 */
// int student_compare(const void *a, const void *b) {
//     return ((student_t*)a)->score - ((student_t*)b)->score;
// }
/**
 * 以 `score` 为依据进行降序排序（最大堆）
 */
int student_compare(const void *a, const void *b) {
    return ((student_t*)b)->score - ((student_t*)a)->score;  
}

void heap_test() {
    const int HEAP_CAPACITY = 5;
    void *heap_storage[HEAP_CAPACITY];  // 存储指针的数组
    heap_t heap;

    // 初始化堆
    heap_init(&heap, heap_storage, HEAP_CAPACITY, student_compare);

    // 创建学生数据
    student_t s1 = {STUDENT_STATE_USE, 1, "Alice", 20, 85};
    student_t s2 = {STUDENT_STATE_USE, 2, "Bob", 22, 90};
    student_t s3 = {STUDENT_STATE_USE, 3, "Charlie", 21, 78};

    // 插入学生
    heap_insert(&heap, &s1);
    heap_insert(&heap, &s2);
    heap_insert(&heap, &s3);

    // 取出最小分数的学生
    student_t *popped_student;
    while (heap_pop(&heap, (void **)&popped_student)) {
        printf("Popped Student ID: %d, Name: %s, Age: %d, Score: %d\n",
               popped_student->id, popped_student->name, popped_student->age, popped_student->score);
        
    }

    return 0;
}