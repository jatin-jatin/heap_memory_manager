#include<unistd.h>
#include<stdio.h>

typedef struct blob{
    int x;
    int y;
    int z;
} blob;

int main(){
    // using simply sbrk was also an option
    blob*addr = sbrk(0);
    if(addr==NULL){
        printf("sbrk failed");
        return 1;
    }
    int status=brk(addr+1);
    if(status!=0){
        printf("brk failed");
        return 1;
    }
    addr->x = 15;
    addr->y = 25;
    addr->z = 44;
    printf("%d %d %d\n",addr->x,addr->y,addr->z);
}