
#include<stdio.h>
#define offset(object,field) \
    ((unsigned int)((char*)(&object.field) - (char*)(&object)))

typedef struct emp_{
    char name[30];
    unsigned int salary;
    char destination[30];
    unsigned int emp_id;
} emp_t;

int main(){
    emp_t obj;
    printf("%u\n", offset(obj, salary));
    return 0;
}
