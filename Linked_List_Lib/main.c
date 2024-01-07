#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"

int main(int argv, char *argc){
    Node *list1 = NULL, *list2 = NULL;

    
    list2 = copy_list(list1);
    print_list(list2);
    return 0;
}