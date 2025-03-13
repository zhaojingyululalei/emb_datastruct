#include "hash/hash_table.h"
#include "test.h"

/**
 * 哈希函数（基于 `id`）
 */
static int student_hash(const void *data) {
    return ((student_t*)data)->id;
}

/**
 * 比较 `student_t` 的 `id`
 */
static int student_compare(const void *a, const void *b) {
    return ((student_t*)a)->id - ((student_t*)b)->id;
}

/**
 * 获取 `student_t` 的 `hash_node_t`
 */
static hash_node_t* student_get_node(const void *data) {
    return &((student_t*)data)->node;
}

/**
 * 获取 `hash_node_t` 对应的 `student_t`
 */
static void* node_get_student(hash_node_t *node) {
    return hash_node_parent(node,student_t,node);
}

void hash_table_test() {
    hash_table_t table;
    student_t students[10];

    hash_table_init(&table, (uintptr_t)student_hash, (uintptr_t)student_compare, 
                    (uintptr_t)student_get_node, (uintptr_t)node_get_student);

    // 插入学生
    for (int i = 0; i < 5; i++) {
        students[i].id = i + 1;
        students[i].score = 90 - i;
        hash_table_insert(&table, &students[i]);
    }

    // 查找学生
    int search_id = 3;
    student_t key = {.id = search_id};
    student_t *found = hash_table_find(&table, &key);
    if (found) {
        printf("找到学生: id=%d, score=%d\n", found->id, found->score);
    } else {
        printf("未找到学生: id=%d\n", search_id);
    }

    // 删除学生
    if (hash_table_remove(&table, &key)) {
        printf("删除成功: id=%d\n", search_id);
    } else {
        printf("删除失败: id=%d\n", search_id);
    }

    // 再次查找
    found = hash_table_find(&table, &key);
    if (found) {
        printf("删除失败，仍然找到: id=%d\n", found->id);
    } else {
        printf("删除成功，未找到: id=%d\n", search_id);
    }
}
