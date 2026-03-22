#include<stdio.h>
#include <stdlib.h>
#include "header.h"

/*To perform addition operation*/
void perform_addition(DLL *head1,DLL *tail1,DLL *head2,DLL *tail2,DLL **head3,DLL **tail3)
{
    //Variables to perform addition
    int sum = 0;
    int carry = 0;
    int op1 = 0, op2 = 0;
    int data = 0;

    //temporary variables to traverse through the list
    DLL *temp1 = tail1;
    DLL *temp2 = tail2;

    while(temp1 != NULL || temp2 != NULL || carry!= 0)
    {
        if(temp1 == NULL)
        {
            op1 = 0;
        }
        else
        {
            op1 = temp1->data;
        }

        if(temp2 == NULL)
        {
            op2 = 0;
        }
        else
        {
            op2 = temp2->data;
        }

        sum = op1 + op2 + carry;
        //printf("sum->%d\n",sum);

        if(sum > 9)
        {
            carry = sum / 10;
            data = sum % 10;
        }
        else
        {
            carry = 0;
            data = sum;
        }

        //printf("data for result->%d\n",data);

        if(insert_at_first(head3,tail3,data)!= SUCCESS)
        {
            printf("ERROR:inserting data to result linked list\n");
        }

        if(temp1)
        {
            temp1 = temp1->prev;
        }
        if(temp2)
        {
            temp2 = temp2->prev;
        }
    }
    if(carry >= 1)
    {
        insert_at_first(head3,tail3,carry);
    } 

    //remove any extra leading zero in the list
    remove_extra_zeros(head3, tail3);
    
}

/*To perform_subtraction operation*/
void perform_subtraction(DLL *head01,DLL *tail01,DLL *head02,DLL *tail02,DLL **head3,DLL **tail3)
{
    //Variables to perform subtraction
    int sub = 0;
    int borrow = 0;
    int op1 = 0,op2 = 0;

    //temporary variables to traverse through the list
    DLL *temp1 = tail01;
    DLL *temp2 = tail02;

    while(temp1 != NULL || temp2 != NULL)
    {
        if(temp1 == NULL)
        {
            op1 = 0;
        }
        else
        {
            op1 = temp1->data;
        }

        if(temp2 == NULL)
        {
            op2 = 0;
        }
        else
        {
            op2 = temp2->data;
        }

        op1 = op1 - borrow;
        borrow = 0;

        if(op2 > op1)
        {
            op1 = op1 + 10;
            borrow = 1;
        }

        sub = op1 - op2;
        //printf("sub->%d\n",sub);

        if(insert_at_first(head3,tail3,sub)!= SUCCESS)
        {
            printf("ERROR:inserting data to result linked list\n");
        }

        if(temp1)
        {
            temp1 = temp1->prev;
        }
        if(temp2)
        {
            temp2 = temp2->prev;
        }
    }

    //remove any extra leading zero in the list
    remove_extra_zeros(head3, tail3);

    if(*head3 == NULL)
    {
        insert_at_first(head3,tail3,0);
    }
}

/*To perform_multiplication operation*/
void perform_multiplication(DLL *head1,DLL *tail1,DLL *head2,DLL *tail2,DLL **head3,DLL **tail3)
{
    if(is_zero(head1) || is_zero(head2))
    {
        insert_at_first(head3,tail3,0);
        return;
    }

    int position = 0;
    int product = 0;
    int data = 0;
    
    DLL *temp2 = tail2;
    
    DLL *res_final_head = NULL, *res_final_tail = NULL;

    //initialise result linked list with zero
    insert_at_first(&res_final_head,&res_final_tail,0);

    while(temp2 != NULL)
    {
        int carry = 0;
        DLL *head_res1 = NULL, *tail_res1 = NULL;
        DLL *temp1 = tail1;

        while(temp1 != NULL)
        {
            product = (temp1->data * temp2->data) + carry;

            if(product > 9)
            {
                carry = product / 10;
                data = product % 10;
            }
            else
            {
                carry = 0;
                data = product;
            }
            
            insert_at_first(&head_res1,&tail_res1,data);

            temp1 = temp1->prev;
        }
        
        //add last data to list using carry
        if(carry > 0)
        {
            insert_at_first(&head_res1,&tail_res1,carry);
        }
        //add zeros at the end, when temp is shifted
        for(int i = 0; i < position; i++)
        {
            insert_at_last(&head_res1,&tail_res1,0);
        }

        DLL *sum_head = NULL, *sum_tail = NULL;

        // printf("first product:");
        // print_data(head_res1);

        // printf("res1:");
        // print_data(res_final_head);

        //add first product to list
        perform_addition(res_final_head,res_final_tail,head_res1,tail_res1,&sum_head,&sum_tail);

        // printf("first sum:");
        // print_data(sum_head);

        //to free result
        free_list(&head_res1,&tail_res1);
        free_list(&res_final_head,&res_final_tail);

        //update result linked list for every addition
        res_final_head = sum_head;
        res_final_tail = sum_tail;

        temp2 = temp2->prev;
        position++;
    }
    *head3 = res_final_head;
    *tail3 = res_final_tail;     
}

/*To perform_division operation*/
void perform_division(DLL *head1, DLL *tail1, DLL *head2, DLL *tail2, DLL **head3, DLL **tail3)
{
    // Check for division by zero
    if (is_zero(head2))
    {
        printf("ERROR: Division by zero\n");
        return;
    }
    
    // If dividend is zero, result is zero
    if (is_zero(head1))
    {
        insert_at_first(head3, tail3, 0);
        return;
    }
    
    // If dividend < divisor, result is zero
    if (is_smaller(head1, head2))
    {
        insert_at_first(head3, tail3, 0);
        return;
    }
    
    // Start with quotient = 0
    insert_at_first(head3, tail3, 0);
    
    // Make a copy of dividend to work with
    DLL *work_head = NULL, *work_tail = NULL;
    DLL *temp = head1;

    while (temp != NULL)
    {
        insert_at_last(&work_head, &work_tail, temp->data);
        temp = temp->next;
    }
    
    //Keep subtracting until work < divisor
    while (1)
    {
        // Check if we can still subtract
        if (is_smaller(work_head, head2)) 
        {
            break;  // Stop when work becomes smaller than divisor
        }
        
        // Subtract divisor from work
        DLL *new_work_head = NULL, *new_work_tail = NULL;
        perform_subtraction(work_head, work_tail, head2, tail2, &new_work_head, &new_work_tail);
        
        // Update work
        free_list(&work_head, &work_tail);
        work_head = new_work_head;
        work_tail = new_work_tail;
        
        // Add 1 to quotient
        DLL *one_head = NULL, *one_tail = NULL;
        insert_at_first(&one_head, &one_tail, 1);
        
        //acts like count, increment for evert subtraction
        DLL *new_quotient_head = NULL, *new_quotient_tail = NULL;
        perform_addition(*head3, *tail3, one_head, one_tail, &new_quotient_head, &new_quotient_tail);
        
        // Update quotient
        free_list(head3, tail3);
        free_list(&one_head, &one_tail);
        *head3 = new_quotient_head;
        *tail3 = new_quotient_tail;
    }
    free_list(&work_head, &work_tail);
}