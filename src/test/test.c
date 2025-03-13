#include "test.h"
#define STUDENT_MAX_CNT 256
static student_t students[STUDENT_MAX_CNT];
student_t* student_alloc(){
    for (int i = 0; i < STUDENT_MAX_CNT; i++)
    {
        if(students[i].state==STUDENT_STATE_FREE){
            students[i].state = STUDENT_STATE_USE;
            return &students[i];
        }
    }
    
}

void student_free(student_t* student){
    student->state = STUDENT_STATE_FREE;
    return;
}