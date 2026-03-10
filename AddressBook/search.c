#include<stdio.h>
#include <string.h>
#include "validation.h" // for validating
#include "contact.h" // to get access to structure
#include "search.h"

//Search menue
void search(AddressBook * addressBook)
{
    int n = addressBook->contactCount; // No. of contacts
    int ch;

    do{
        printf("\nSearch by?\n");
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
                name_sr(addressBook,n);
                break;
            case 2:
                number_sr(addressBook,n);
                break;
            case 3:
                email_sr(addressBook,n);
                break;
            case 4:
                printf("Saved and Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n"); 
                break;
        }
                
    }while (ch != 4);

}

void name_sr(AddressBook * addressBook,int n)//Search by name
{
    char srch[30];
    int count = 0;
    int matches[20]; // stores matching names indexs

    printf("Enter Name: ");
    scanf(" %[^\n]",srch);
    
    for(int i=0;i<n;i++) //finding matches
    {
        if( (strcmp(addressBook->contacts[i].name,srch) == 0) )
        {
            matches[count++] = i;// if matching names found store that index number in match array
        }
    }

    if(count == 0)// no match come out from the function
    {
        printf(":: No Matching contact found ::\n");
        return;
    }

    if (count > 1) 
    {
        printf("\nMultiple contacts found:\n");//Ask user to which data they need to search

        for (int i = 0; i < count; i++) {

            int idx = matches[i];// through matches[i], go to that particular index data in structure,then print data

            printf("%d. %s | %s | %s\n", i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }

        int choice;
        do // take user input, which contact they wanted to display
        {
            printf("Enter your choice (1 to %d): ", count);
            if((scanf("%d",&choice))!= 1)
                {
                    printf("Invalid input. Please enter a number.\n");
                    clearInputBuffer();  // remove invalid input
                    continue;            // restart loop
                }
        } while (choice < 1 || choice > count); 
        // Why 1? repeat asking until the user enters a number between 1 and count

        int indx = matches[choice - 1];//? choice-1, array indexing start from 0
        printf("\n:: Contact selected ::\n");
        printf("Name         : %s\n", addressBook->contacts[indx].name);
        printf("Phone Number : %s\n", addressBook->contacts[indx].phone);
        printf("Email id     : %s\n", addressBook->contacts[indx].email);
    }
    else { // if only 1 match
        int indx = matches[0];//?0, for unique name
        printf("\n:: Contact found ::\n");
        printf("Name         : %s\n", addressBook->contacts[indx].name);
        printf("Phone Number : %s\n", addressBook->contacts[indx].phone);
        printf("Email id     : %s\n", addressBook->contacts[indx].email);
    }

}

void number_sr(AddressBook * addressBook,int n) // Search by Phone number
{
    char srch[30];
    int found = 0;

    printf("Enter Phone number: ");
    scanf(" %[^\n]",srch);

    for(int i=0;i<n;i++)
    {
        if((strcmp(addressBook->contacts[i].phone,srch) == 0) ) //compare if entered number is found in contact
        {
            printf("\n:: Contact found ::\n");
            printf("Name         : %s\n",addressBook->contacts[i].name); 
            printf("Phone Number : %s\n",addressBook->contacts[i].phone); 
            printf("Email id     : %s\n",addressBook->contacts[i].email); 
            found = 1;//if number found in contacts
        }
    }
        
    if(found == 0)//if number not found in contacts
    {
        printf(":: No Matching contact found ::\n");
    }
}

void email_sr(AddressBook * addressBook,int n) // Search by Email
{
    char srch[30];
    int found = 0;
    
    printf("Enter email: ");
    scanf(" %[^\n]",srch);

    for(int i=0;i<n;i++)
    {
        if((strcmp(addressBook->contacts[i].email,srch) == 0) ) //compare if entered number is found in contact
        {
            printf("\n:: Contact found ::\n");
            printf("Name         : %s\n",addressBook->contacts[i].name); 
            printf("Phone Number : %s\n",addressBook->contacts[i].phone); 
            printf("Email id     : %s\n",addressBook->contacts[i].email); 
            found = 1;
        }
    }
        
    if(found == 0)
    {
        printf(":: No Matching contact found ::\n");
    }
}