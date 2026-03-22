#include<stdio.h>
#include <stdlib.h>
#include "header.h"

/*coverting character to integer*/
int string_to_int(char ch)
{
    return ch - '0';
}

/*performing insert at first for linked list*/
int insert_at_first(DLL **head, DLL **tail, int data)
{
    DLL *new = malloc(sizeof(DLL));
    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)   // empty list
    {
        *head = new;
        *tail = new;
    }
    else                 // non-empty list
    {
        new->next = *head;
        (*head)->prev = new; 
        *head = new;
    }

    return SUCCESS;
}

/*performing insert at last for linked list*/
int insert_at_last(DLL **head,DLL **tail,int data)
{
    DLL *new = malloc(sizeof(DLL));

    if(new == NULL)
    {
        return FAILURE;
    }

    new->data = data;

    new->prev = NULL;

    new->next = NULL;

    if(*head == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;

    return SUCCESS;

}

/*printing datas of linked list*/
void print_data(DLL *head)
{
    if(head == NULL)
    {
        printf("List is empty");
    }

    DLL *temp = head;
    while(temp)
    {
        printf("%d  ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/*printing datas of linked lists*/
void print(DLL *head1,DLL *head2)
{
    printf("Operand1:  ");
    print_data(head1);
    
    printf("Operand2:  ");
    print_data(head2);
    printf("---------------------------------------------\n");
}

/*to remove extra leading zero in linked list*/
void remove_extra_zeros(DLL **head, DLL **tail)
{
    DLL *current = *head;
    
    // Remove leading zeros until we find a non-zero digit or only one digit remains
    while(current != NULL && current->data == 0 && current->next != NULL)
    {
        DLL *zero = current;
        current = current->next;
        current->prev = NULL;
        *head = current;
        free(zero);
    }
}

/*to check list having only one data that is zero*/
int is_zero(DLL *head)
{
    DLL *temp = head;

    while (temp)
    {
        if (temp->data != 0)
            return 0;   // NOT zero
        temp = temp->next;
    }
    return 1;   // all digits were zero
}

/*to free linked list*/
void free_list(DLL **head, DLL **tail)
{
    DLL *current = *head;
    DLL *next_node;
    
    while(current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    
    *head = NULL;
    *tail = NULL;
}

/* Function to check if first number is smaller than second number*/
int is_smaller(DLL *head1, DLL *head2)
{
    // Count the length of both numbers
    int len1 = 0, len2 = 0;
    DLL *t;

    t = head1;
    while (t) { len1++; t = t->next; }

    t = head2;
    while (t) { len2++; t = t->next; }

    
    // If lengths are different, the shorter number is smaller
    if (len1 < len2) {
        return 1;  // head1 is smaller
    }
    if (len1 > len2) {
        return 0;  // head1 is larger
    }
    
      // Same length -> compare digits from left
   while (head1 && head2)
    {
        if (head1->data < head2->data) return 1;
        if (head1->data > head2->data) return 0;

        head1 = head1->next;
        head2 = head2->next;
    }
    
    return 0;  // Numbers are equal
}

/*to check sign of entered number*/
int check_sign(char operator, char *operand1, char *operand2)
{
    int sign1 = (operand1[0] == '-') ? 1 : 0;
    int sign2 = (operand2[0] == '-') ? 1 : 0;
    
    switch(operator)
    {
        case '*': 
        case 'x': 
        case 'X':
            // Multiplication: negative if signs are different
            return (sign1 != sign2) ? 1 : 0;
            
        case '+':
            // Addition:
            if (sign1 && sign2) 
                return 3;      // (-a) + (-b) = -(a+b)
            else if (sign1 != sign2) 
                return 2;      // (-a) + b or a + (-b) = subtraction according greater number
            else 
                return 0;      // a + b = addition
            
        case '-':
            // Subtraction:
            if (sign1 && sign2) 
                return 2;      // (-a) - (-b) = b - a  
            else if (sign1) 
                return 3;      // (-a) - b = -(a + b)
            else if (sign2) 
                return 0;      // a - (-b) = a + b
            else 
                return -1;      // a - b = subtraction
            
        case '/':
            // Division: negative if signs are different
            return (sign1 != sign2) ? 4 : 0;
            
        default:
            return 0;
    }
}

void list_leading_zeros(DLL **head, DLL **tail)
{
    while (*head && (*head)->data == 0 && (*head)->next)
    {
        DLL *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}
