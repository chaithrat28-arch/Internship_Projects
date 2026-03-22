/*******************************************************************************************************
NAME            : CHAITHRA T
DATE            : 29/11/2025 - 08/12/2025
PROJECT TITLE   : ARBITRARY PRECISION CALCULATOR (APC)
DESCRIPTION     : Implementation of a calculator that handles very large integers using 
                  Doubly Linked Lists (DLL). Supports +, -, x, / operations for numbers 
                  beyond normal integer limits.
PRE-REQUISITE   : Understanding of linked lists, dynamic memory allocation, and sign handling.
*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// ./a.out(0) 123(1->op1) +(2->operator) 123(3-> op2)

int main(int argc, char *argv[])
{

    //Validate command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./a.out <operand1> <operator: +,-,x,/> <operand2>\n");
        return FAILURE;
    }

    char operator = argv[2];
    char *operand1 = argv[1];
    char *operand2 = argv[3];

    printf("     -:ARBITRARY PRECISION CALCULATOR:-\n");

    //Create DLLs for operands
    DLL *head1 = NULL, *tail1 = NULL;   // Operand1 list
    DLL *head2 = NULL, *tail2 = NULL;   // Operand2 list
    DLL *head3 = NULL, *tail3 = NULL;   // Result list

    /* Store original strings to detect sign */
    char *original_operand1 = operand1;
    char *original_operand2 = operand2;

    //to Check signs and determine operation type
    int sign_result = check_sign(operator, operand1, operand2);

   // Skip negative signs when creating linked lists
    if (original_operand1[0] == '-')
        operand1 = original_operand1 + 1;

    if (original_operand2[0] == '-')
        operand2 = original_operand2 + 1;

        int i=0,j=0;
    // Create linked lists (skip negative signs) 
    while(operand1[i] != '\0') 
    { 
        int data1 = string_to_int(operand1[i]); 
        if(insert_at_last(&head1,&tail1,data1) != SUCCESS) 
        { 
            printf("ERROR: inserting to first linked list\n"); 
        } 
        i++; 
    } 
    while(operand2[j] != '\0') 
    { 
        int data2 = string_to_int(operand2[j]); 
        if(insert_at_last(&head2,&tail2,data2) != SUCCESS) 
        { 
            printf("ERROR: inserting to second linked list\n"); 
        } 
        j++; 
    }

    list_leading_zeros(&head1, &tail1);
    list_leading_zeros(&head2, &tail2);

    // performing operations based on sign result
    switch (operator)
    {
        case '+':
            printf("---------------------------------------------\n");
            printf("    -:Performing Addition Operation:-\n");
            printf("---------------------------------------------\n");
            print(head1, head2);

            if (sign_result == 3)
            {
                // (-a) + (-b) = -(a + b)
                perform_addition(head1, tail1, head2, tail2, &head3, &tail3);
                printf("Result  : -");
                print_data(head3);
            }
            else if (sign_result == 2)
            {
                // (-a) + b or a + (-b) = subtraction
                if (original_operand1[0] == '-')
                {
                    // (-a) + b = b - a
                    if (is_smaller(head1, head2))
                    {
                        perform_subtraction(head2, tail2, head1, tail1, &head3, &tail3);
                        printf("Result  :  ");
                    }
                    else
                    {
                        perform_subtraction(head1, tail1, head2, tail2, &head3, &tail3);
                        printf("Result  : -");
                    }
                }
                else
                {
                    // a + (-b) = a - b
                    if (is_smaller(head2, head1))
                    {
                        perform_subtraction(head1, tail1, head2, tail2, &head3, &tail3);
                        printf("Result  :  ");
                    }
                    else
                    {
                        perform_subtraction(head2, tail2, head1, tail1, &head3, &tail3);
                        printf("Result  : -");
                    }
                }
                print_data(head3);
            }
            else
            {
                // Normal addition: a + b
                perform_addition(head1, tail1, head2, tail2, &head3, &tail3);
                printf("Result  :  ");
                print_data(head3);
            }
            printf("---------------------------------------------\n");
            break;

        case '-':
            printf("---------------------------------------------\n");
            printf("    -: Performing Subtraction Operation:-\n");
            printf("---------------------------------------------\n");
            print(head1, head2);

            if (sign_result == 3)
            {
                // (-a) - b = -(a + b)
                perform_addition(head1, tail1, head2, tail2, &head3, &tail3);
                printf("Result : -");
                print_data(head3);
            }
            else if (sign_result == 2)
            {
                // (-a) - (-b) = b - a
                if (is_smaller(head1, head2))
                {
                    perform_subtraction(head2, tail2, head1, tail1, &head3, &tail3);
                    printf("Result :  ");
                }
                else
                {
                    perform_subtraction(head1, tail1, head2, tail2, &head3, &tail3);
                    printf("Result : -");
                }
                print_data(head3);
            }
            else if (sign_result == 0)
            {
                // a - (-b) = a + b
                perform_addition(head1, tail1, head2, tail2, &head3, &tail3);
                printf("Result : ");
                print_data(head3);
            }
            else
            {
                // Normal subtraction -> a - b
                int negative = 0;

                // If a < b -> result is negative, subtract in reverse
                if (is_smaller(head1, head2))
                {
                    negative = 1;
                    perform_subtraction(head2, tail2, head1, tail1, &head3, &tail3);
                }
                else
                {
                    perform_subtraction(head1, tail1, head2, tail2, &head3, &tail3);
                }

                printf("Result : ");
                if (negative) printf("-");
                print_data(head3);
            }

            printf("---------------------------------------------\n");
            break;

        case '/':
            printf("---------------------------------------------\n");
            printf("    -:Performing Division Operation:-\n");
            printf("---------------------------------------------\n");
            print(head1, head2);

            perform_division(head1, tail1, head2, tail2, &head3, &tail3);

            if (sign_result == 4)
                printf("Result  : -");
            else
                printf("Result  :  ");

            print_data(head3);
            printf("---------------------------------------------\n");
            break;

        case 'x':
        case 'X':
            printf("---------------------------------------------\n");
            printf("    -:Performing Multiplication Operation:-\n");
            printf("---------------------------------------------\n");
            print(head1, head2);

            perform_multiplication(head1, tail1, head2, tail2, &head3, &tail3);

            if (sign_result == 1)
                printf("Result  : -");
            else
                printf("Result  :  ");

            print_data(head3);
            printf("---------------------------------------------\n");
            break;

        default:
            printf("Invalid operator: %c\n", operator);
            break;
    }

    //Free all allocated memory
    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&head3, &tail3);

    return SUCCESS;
}
