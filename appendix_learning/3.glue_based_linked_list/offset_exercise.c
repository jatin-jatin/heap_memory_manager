#include"glthread.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct emp_{
    char name[30];
    unsigned int salary;
    char destination[30];
    unsigned int emp_id;
    glthread_node_t glnode;
}emp_t;

void print_emp_details(glthread_node_t *glnode){
    int off = offsetof(emp_t,glnode);
    emp_t *obj = (emp_t*)((void*)glnode-off);
    printf("%s\n",obj->name);
    printf("%u\n",obj->salary);
    printf("%s\n",obj->destination);
}

int main(){
    emp_t *emp = (emp_t*)malloc(sizeof(emp_t));
    strcpy(emp->name,"Jatin");
    strcpy(emp->destination,"Engineer");
    emp->salary = 40000000;
    emp->emp_id = 7;
    print_emp_details(&emp->glnode);
}