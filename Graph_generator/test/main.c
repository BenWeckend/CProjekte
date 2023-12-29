#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char d;
    char a;
    int b;
} Point;

int main(){
    printf("%d", sizeof(Point));

    return 0;
}
 