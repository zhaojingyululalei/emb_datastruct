#include "tree/rb_tree.h"

#include "test.h"

/**
 * 比较 `student_t` 的 `score`
 */
static int student_compare(const void *a, const void *b)
{
    return ((student_t *)a)->score - ((student_t *)b)->score;
}

/**
 * 获取 `student_t` 的 `rb_node_t`
 */
rb_node_t *student_get_node(const void *data)
{
    return &((student_t *)data)->node;
}

student_t *node_get_student(rb_node_t *node)
{
    return rb_node_parent(node, student_t, node);
}

static  void student_print(student_t* s){
    printf("id=%d, score=%d\n",
               s->id, s->score);
}
void rbtree_test(void)
{
    rb_tree_t tree;
    student_t students[10];

    rb_tree_init(&tree, 10, (uintptr_t)student_compare, (uintptr_t)student_get_node,(uintptr_t)node_get_student);

    for (int i = 0; i < 5; i++)
    {
        students[i].id = i + 1;
        students[i].score = 90 - i;
        rb_tree_insert(&tree, &students[i]);
    }

    rb_tree_inorder(&tree, tree.root, student_print);
}