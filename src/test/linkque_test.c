#include "queue/linkque.h"
#include "test.h"

/**
 * 测试链队
 */
void linkque_test() {
    linkque_t queue;
    linkque_init(&queue);

    printf("开始入队...\n");

    // 入队
    for (int i = 0; i < 5; i++) {
        student_t *s = student_alloc();
        if (!s) {
            printf("学生池满，无法分配\n");
            break;
        }

        s->id = i + 1;
        snprintf(s->name, sizeof(s->name), "Student_%d", s->id);
        s->age = 20 + i;
        s->score = 80 + i;

        if (linkque_enqueue(&queue, &s->node)) {
            printf("入队: id=%d, name=%s, age=%d, score=%d\n",
                   s->id, s->name, s->age, s->score);
        }
    }

    printf("开始出队...\n");

    // 出队
    while (!linkque_is_empty(&queue)) {
        linkque_node_t *node = linkque_dequeue(&queue);
        if (!node) break;

        // 通过 `offset_to_parent` 计算 `student_t*`
        student_t *s = linkque_node_parent(node, student_t, node);
        printf("出队: id=%d, name=%s, age=%d, score=%d\n",
               s->id, s->name, s->age, s->score);
        student_free(s);
    }
}