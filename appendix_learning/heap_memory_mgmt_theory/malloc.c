#include<stdlib.h>
#include<stdio.h>

typedef struct Coordinates{
    int x;
    int y;
} Coordinates;

int main(){
    Coordinates* c = (Coordinates*)malloc(sizeof(Coordinates));
    c->x =20;
    c->y =50;
    printf("%d and %d\n",c->x,c->y);
}