
typedef struct node
{
    double value;
    struct node *next;
}Node;

Node *insert_at_head(Node *head, double value);
Node *insert_at_tail(Node *head, double value);
Node *delete_at_tail(Node *head);
Node *delete_at_head(Node *head);
Node *node_at_pos(Node *head, int position);
Node *free_list(Node *head);
Node *delete_node(Node *head, int position);
int value_at_pos(Node *head, int position);
int count(Node *head, double value);
int search_list(Node *head, double value);
int list_length(Node *head);
double value_node(Node *head, int position);
void print_list(Node *head);
void replace(Node *head, double value_out, double value_in);
void sort_q(Node *head);
void swap_values(Node *value1, Node *value2);
//void remove_dublicates(Node *head, double value);
//void insert_after_value();
//Node *copy_list();
//Node *reverse_list();
//Node *delete_first_match();
//Node *delete_last_match();
//Node *delete_all_matches();
//Node *append_list();
//Node *insert_at_value();
//Node *add_list_values();
//Node *copy_list();
//Node *merge_sort_lists();