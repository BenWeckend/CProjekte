#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "llist.h"

Node *free_list(Node *head){
    if(head == NULL) return NULL;
    while(head != NULL){
        Node *buffer = head;
        head = head->next;
        free(buffer);
    }
    return NULL;
}

void print_list(Node *head){
    while(head != NULL){
        printf("%lf\n", head->value);
        head = head->next;
    }
}

Node *insert_at_head(Node *head, double value){
    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = value;
    if (head == NULL) return new_node;
    else{
        new_node->next = head;
        return new_node;
    }
}

Node *insert_at_tail(Node *head, double value){
    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = value;
    Node *true_head = head;
    if (head == NULL) return new_node;
    else{
        while(head->next != NULL) head = head->next;
        head->next = new_node;
        return true_head;
    }
}

Node *delete_at_head(Node *head){
    if(head == NULL) return NULL;
    Node *true_head = head;
    free(true_head);

    return head->next;
}

Node *delete_at_tail(Node *head){
    if(head == NULL) return NULL;
    if(head->next == NULL){
        free(head); return NULL;
        }
    Node *true_head = head;
    while(head->next->next != NULL) head = head->next;
    Node *tofree = head->next;
    head->next = NULL;
    free(tofree);

    return true_head;
}

int count(Node *head, double value){
    if(head == NULL) return 0;
    else if(head->value == value) return 1 + count(head->next, value);
    else if(head->value != value) return count(head->next, value);
    else return 0;
}

int search_list(Node *head, double value){
   int i=0;
    if (head == NULL) return -1;
    while(head->value != value && head != NULL){
        head = head->next;
        i++;
    }
    if(head->value == value) return i;
    else return -1;
}

void replace(Node *head, double value_out, double value_in){
    if(head == NULL) return ;
    while(head->value != value_out){
        head = head->next;
    }
    head->value = value_in;
}

void swap_values(Node *value1, Node *value2){
    if(value1 != NULL && value2 != NULL){
        double buffer = value1->value;
        value1->value = value2->value;
        value2->value = buffer;
    }
}

int list_length(Node *head){
    if(head == NULL) return 0;
    if(head != NULL) return (1 + list_length(head->next))-1;
    else return 0;
}

int value_at_pos(Node *head, int position){
    for(int i=0; i<position; i++) head = head->next;
    return head->value;
}

Node *node_at_pos(Node *head, int position){
    for(int i=0; i<position; i++){
        head = head->next;
    }
    return head;
}

Node *copy_list(Node *head){
    if(head == NULL) return NULL;
    Node *new_head = calloc(1, sizeof(Node)), *head_node;
    new_head->value = head->value;
    head_node = new_head;
    head = head->next;

    while(head != NULL){
        Node *new_node = calloc(1, sizeof(Node));
        new_node->value = head->value;
        new_head->next = new_node;

        new_head = new_head->next;
        head = head->next;
    }
    return head_node;
}

void sort_q(Node *head){
    int lenght = list_length(head);
    srand(time(NULL));

    int partition(Node *head, int low, int high){
        double pivot_index = low + (rand() % (high - low));
        if(pivot_index != high) swap_values(node_at_pos(head, pivot_index), node_at_pos(head, high));
        
        double pivot_value = value_at_pos(head, high);
        double i = low;

        for(int j=low; j<high; j++){
            if(value_at_pos(head, j) <= pivot_value){
                swap_values(node_at_pos(head, i), node_at_pos(head, j));
                i++;
            }
        }
        swap_values(node_at_pos(head, i), node_at_pos(head, high));

        return i;
    }

    void quicksort_recursion(Node *head, int low, int high){
        if(low < high){
            int pivot_index = partition(head, low, high);
            quicksort_recursion(head, low, pivot_index - 1);
            quicksort_recursion(head, pivot_index + 1, high);
        }
    }

    quicksort_recursion(head, 0, lenght-1);
}

Node *delete_node(Node *head, int position){
    if(head == NULL) return NULL;
    if(position > list_length(head)) {return head; fprintf(stderr, "Error: position exceeds list");}
    if(position == 0){
        Node *true_head = head;
        free(true_head);
        return head->next;
    }

    Node *befor = NULL, *true_head = head;
    for(int current_pos=0; current_pos<position; current_pos++){
        befor = head;
        head = head->next;
    }
    befor->next = head->next;
    free(head);
    return true_head;
}

double value_node(Node *head, int position){
    if(head == NULL) fprintf(stderr, "Error: empty list");;
    if(position > list_length(head)) fprintf(stderr, "Error: position exceeds list");

    for(int current_pos=0; current_pos<position; current_pos++){
        head = head->next;
    }
    return head->value;
}

