#ifndef __TEST_H
#define __TEST_H
#include "list/list.h"
#include "tree/rb_tree.h"
typedef struct _student_t{
    enum{
        STUDENT_STATE_FREE,
        STUDENT_STATE_USE
    }state;
    int id;
    char name[16];
    int age;
    int score;
    //list_node_t node;
    rb_node_t node;  // 作为红黑树的节点
}student_t;


student_t* student_alloc();

void student_free(student_t* student);


void list_test(void);
void fixque_test(void);
void linkque_test(void) ;
void heap_test(void) ;
void rbtree_test(void);
void hash_table_test() ;
#endif