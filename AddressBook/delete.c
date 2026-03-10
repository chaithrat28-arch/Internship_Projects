#include<stdio.h>
#include <string.h>
#include "validation.h" // for validating
#include "contact.h" // to get access to structure
#include "delete.h"

//Deleting menue
void deleting(AddressBook* addressBook)
{
    int n = addressBook->contactCount; // No. of contacts
    int ch;
        
    printf("\n:: List of Contacts ::\n");
    for(int i = 0;i < n;i++)
    {
        printf("\nContact details of %d:\n",i+1);
        printf("Name         : %s\n",addressBook->contacts[i].name); 
        printf("Phone Number : %s\n",addressBook->contacts[i].phone);
        printf("Email id     : %s\n",addressBook->contacts[i].email);     
    }
    do{
        printf("\nDelete by?\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email id\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        if((scanf("%d",&ch))!= 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();  // remove invalid input
            continue;            // restart loop
        }

        switch (ch) 
        {
            case 1:
                name_del(addressBook,n);
                break;
            case 2:
                number_del(addressBook,n);
                break;
            case 3:
                email_del(addressBook,n);
                break;
            case 4:
                printf("Deleted and Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            
        }
                
    }while (ch != 4);
}

//using name for deleting
void name_del(AddressBook * addressBook,int n)
{
    char del[30];
    int delete = 0;

    while(!delete)
    {
        int matches[20]; // if multiple names found, to store
        int count = 0;

        printf("Enter name: ");
        scanf(" %[^\n]",del);

        int nm = name_valid(del); // name validation
        if(nm == 0)
        {
            continue; // validation fails read data again
        }

        for(int i = 0;i < addressBook->contactCount;i++) //finding multiple same names
        {
            if( (strcmp(addressBook->contacts[i].name,del) == 0) )
            {
                matches[count++] = i;//found store index value in matches[]
            }
        }

        if(count == 0)// no match come out from the function
        {
            printf(":: No Matching contact found ::\n");
            return;
        }

        int idx = -1; // to delete particular data from the structure

        if(count == 1)//only one match
        {
            idx = matches[0];
            printf(":: Contact found ::\n");    
            printf("Name         : %s\n", addressBook->contacts[idx].name);
            printf("Phone Number : %s\n", addressBook->contacts[idx].phone);
            printf("Email id     : %s\n", addressBook->contacts[idx].email);
        }
        else
        {
            printf("\nMultiple contacts found:\n");
            for (int i = 0; i < count; i++) 
            {
                int k = matches[i];
                printf("%d. %s | %s | %s\n", i + 1,
                   addressBook->contacts[k].name,
                   addressBook->contacts[k].phone,
                   addressBook->contacts[k].email);
            }
            int choice;
            do // take user input, which contact wanted to display
            {
                printf("\nEnter your choice (1 to %d): ", count);
                if((scanf("%d",&choice))!= 1)
                {
                    printf("Invalid input. Please enter a number.\n");
                    clearInputBuffer();  // remove invalid input
                    continue;            // restart loop
                }
            } while (choice < 1 || choice > count);

            idx = matches[choice - 1];// ?choice-1, array indexing start from 0
        }

        for(int j = idx;j < addressBook->contactCount - 1; j++)
        {
            addressBook->contacts[j] = addressBook->contacts[j + 1]; // shift contacts left side
        }
        //That particular data will be lost

        addressBook->contactCount--; // after removing one data decrement contactCount, to manage exsist data
                
        printf(":: Deleted Successfully ::\n");
                
        delete = 1;  //After Deleting successfully, break the loop 
    }

}

// using Number for deleting
void number_del(AddressBook * addressBook,int n)
{
    char del[30];
    int delete = 0;

    while(!delete)
    {
        int found = 0;
        printf("Enter Phone number: ");
        scanf(" %[^\n]",del);

        int ph = number_valid(del); // number validation
        if(ph == 0)
        {
            continue; // validation fails read data again
        }

        for(int i = 0;i < addressBook->contactCount ; i++)
        {
            if((strcmp(addressBook->contacts[i].phone,del) == 0) ) //compare if entered number is found in contact
            {
                printf(":: Contact found ::\n");
                
                printf("Name         : %s\n", addressBook->contacts[i].name);
                printf("Phone Number : %s\n", addressBook->contacts[i].phone);
                printf("Email id     : %s\n", addressBook->contacts[i].email);

                for(int j = i;j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1]; // shift contacts left side
                }
                
                addressBook->contactCount--; // reduce addressBook->contactCount
                /* if n=4,deppak is in 3rd and chaithra is in 4th position, am deleting deepak then for 3rd position chaithra will be overwritten
                now, size shld be reduced bcz only 3 contact details present, so reduce n, it will be 3*/

                printf(":: Deleted Successfully ::\n");
                delete = 1; 
                found = 1;//check number present or not in contacts
                break;
            }
        }
        if(found == 0)
        {
            printf(":: No Matching contact found, try again ::\n");
        }
    }
}

//using email for deleting
void email_del(AddressBook * addressBook,int n)
{
    char del[30];
    int delete = 0;

    while(!delete)
    {
        int found = 0;
        printf("Enter email: ");
        scanf(" %[^\n]",del);

        int em = email_valid(del);//Email validation
        if(em == 0)
        {
            continue; // fails validation repeat again
        }

        for(int i = 0;i < addressBook->contactCount ; i++)
        {
            if((strcmp(addressBook->contacts[i].email,del) == 0) ) //compare if entered email is found in contact
            {
                printf(":: Contact found ::\n");
                printf("Name         : %s\n", addressBook->contacts[i].name);
                printf("Phone Number : %s\n", addressBook->contacts[i].phone);
                printf("Email id     : %s\n", addressBook->contacts[i].email);

                for(int j = i;j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1]; // shift contacts left side
                }
                
                addressBook->contactCount--;

                printf(":: Deleted Successfully ::\n");
                delete = 1; 
                found = 1;//check email present or not in contacts
                break;
            }
        }
        if(found == 0)
        {
            printf(":: No Matching contact found, try again ::\n");
        }
    }
}

//if user entered charcater of ctrl+d instead of integer, then end the loop 
void clearInputBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // flush input buffer
}
