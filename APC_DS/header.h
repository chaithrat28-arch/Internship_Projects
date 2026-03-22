#ifndef Header_h
#define Header_h

/* Structure for Doubly Linked List*/
typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}DLL;

/*Enumeration for return status of function*/
typedef enum 
{
    SUCCESS,FAILURE,EMPTY,FULL
}status;

/*To perform insert at first to the linked list*/
int insert_at_first(DLL **,DLL **,int );

/*To perform insert at last to the linked list*/
int insert_at_last(DLL **,DLL **,int);

/*For printing Linked list data*/
void print_data(DLL *);
void print(DLL *,DLL *);

/*To perform addition operation*/
void perform_addition(DLL *,DLL *,DLL *,DLL *,DLL **,DLL **);

/*To perform_subtraction operation*/
void perform_subtraction(DLL *,DLL *,DLL *,DLL *,DLL **,DLL **);

/*To perform_division operation*/
void perform_division(DLL *,DLL *,DLL *,DLL *,DLL **,DLL **);

/*To perform_multiplication operation*/
void perform_multiplication(DLL *,DLL *,DLL *,DLL *,DLL **,DLL **);

/*To convert character data into integer*/
int string_to_int(char ch);

/*To remove leading or extra zeros in linked list*/
void remove_extra_zeros(DLL **, DLL **);

/*To check the data is zero or not*/
int is_zero(DLL *);

/*to free the list*/
void free_list(DLL **, DLL **);

/*to check sign of operands*/
int check_sign(char ,char *,char *);

/*to check is small or not*/
int is_smaller(DLL *, DLL *);

/*to remove extra zeros*/
void list_leading_zeros(DLL **, DLL **);

#endif