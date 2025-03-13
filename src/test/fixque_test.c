#include "test.h"
#include "queue/fixque.h"

#define STUDENT_SIZE 5
static student_t buffer[STUDENT_SIZE];  // 定义存储空间
static fixque_t queue;  // 定义队列

void assign_student(void *dest, const void *src) {
    student_t *d = (student_t*)dest;
    const student_t *s = (const student_t*)src;
    d->id = s->id;
    snprintf(d->name, sizeof(d->name), "%s", s->name);  // 复制字符串
}

void fixque_test(void) {
    fixque_init(&queue, buffer, sizeof(student_t), STUDENT_SIZE,assign_student);

    // 入队
    for (int i = 1; i <= 5; i++) {
        student_t s = { .id= i };
        if (fixque_enqueue(&queue, &s)) {
            printf("入队: id=%d, name=%s\n", s.id, s.name);
        } else {
            printf("队列满，无法入队: id=%d\n", s.id);
        }
    }

    // 出队
    student_t s;
    while (fixque_dequeue(&queue, &s)) {
        printf("出队: id=%d, name=%s\n", s.id, s.name);
    }
}