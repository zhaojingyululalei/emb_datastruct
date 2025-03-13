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
    heap_t heap;
    heap_init(&heap, student_buffer, sizeof(student_t), STUDENT_MAX_CNT, student_compare,student_alloc,student_free);

    printf("开始插入学生...\n");
    for (int i = 0; i < 5; i++) {
        student_t s = { STUDENT_STATE_USE, i + 1, "Student", 20 + i, 90 - i };
        if (heap_insert(&heap, &s)) {
            printf("插入: id=%d, score=%d\n", s.id, s.score);
        }
    }

    printf("开始弹出学生...\n");
    student_t s;
    while (heap_pop(&heap, &s)) {
        printf("弹出: id=%d, score=%d\n", s.id, s.score);
    }
}