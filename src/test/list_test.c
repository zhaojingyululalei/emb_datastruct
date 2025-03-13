#include "list/list.h"
#include "test.h"



static list_t list;

void print_list(void){
    //查
    list_node_t* cur_node = list.first;
    while (cur_node)
    {   
        list_node_t* next_node = cur_node->next;
        student_t* stu = list_node_parent(cur_node,student_t,node);
        printf("student id = %d\r\n",stu->id);
        cur_node = next_node;
    }
}
void list_func(void){
    student_t *student_a = student_alloc(); student_a->id = 1;
    list_insert_last(&list,&student_a->node);
    list_node_t* cur_node = list.first;
    student_t* stu = offset_to_parent(cur_node,student_t,node);
    printf("student id = %d\r\n",stu->id);
}
void list_test(void){
    list_func();
    // list_init(&list);
    // student_t *student_a = student_alloc(); student_a->id = 1;
    // student_t *student_b = student_alloc(); student_b->id = 2;
    // student_t *student_c = student_alloc(); student_c->id = 3;
    // //增
    // list_insert_last(&list,&student_a->node);
    // list_insert_last(&list,&student_b->node);
    // list_insert_last(&list,&student_c->node);
    // //查
    // print_list();
    // //删
    // list_remove(&list,&student_a->node);
    // list_remove(&list,&student_b->node);
    // //查
    // print_list();
    
    
}