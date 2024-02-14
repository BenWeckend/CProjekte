#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

int main(void){
    int testMatrix[3][3] = {{0,0,1},{0,1,0},{1,0,0}};
    if(istSymmetrisch(testMatrix, 3)) printf("Ist symmetrisch.\n");
    else printf("Nicht symmetrisch");
    return 0;
}