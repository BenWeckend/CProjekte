#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"

int main(int argv, char *argc){
    Node *list1 = NULL;

    list1 = insert_at_head(list1, -3);
    list1 = insert_at_head(list1, 7);
    list1 = insert_at_head(list1, 6);
    list1 = insert_at_head(list1, 1);
    list1 = insert_at_head(list1, -2);
 
    
    print_list(list1);
    printf("\n");
    printf("%lf\n", value_node(list1, 67));
    print_list(list1);
    return 0;
}