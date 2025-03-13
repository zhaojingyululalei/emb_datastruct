#include "test.h"
#include "queue/fixque.h"

void fixque_test(void) {
    const int QUEUE_CAPACITY = 3;
    void *queue_storage[QUEUE_CAPACITY];  // 存储指针的数组
    fixque_t queue;

    // 初始化队列（使用 student_assign 进行深拷贝）
    fixque_init(&queue, queue_storage, QUEUE_CAPACITY);

    // 准备要入队的 student_t 结构体
    student_t stu1 = {STUDENT_STATE_USE, 1, "Alice", 20, 85};
    student_t stu2 = {STUDENT_STATE_USE, 2, "Bob", 22, 90};
    student_t stu3 = {STUDENT_STATE_USE, 3, "Charlie", 21, 78};

    // 入队
    fixque_enqueue(&queue, &stu1);
    fixque_enqueue(&queue, &stu2);
    fixque_enqueue(&queue, &stu3);

    // 出队并打印
    student_t *dequeued;
    while (fixque_dequeue(&queue, (void **)&dequeued)) {
        printf("Dequeued Student ID: %d, Name: %s, Age: %d, Score: %d\n",
               dequeued->id, dequeued->name, dequeued->age, dequeued->score);
        
    }

    return 0;
}