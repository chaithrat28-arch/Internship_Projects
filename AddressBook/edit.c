#include <stdio.h>
#include <string.h>
#include "validation.h"
#include "edit.h"
#include "contact.h"

//Edit menue
void edit(AddressBook* addressBook)
{
    int n = addressBook->contactCount;
    int ch;
        
    printf("\n:: List of Contacts ::\n");
    for(int i = 0;i < n;i++)
    {
        printf("\nContact details of %d:\n",i+1);
        printf("Name         : %s\n",addressBook->contacts[i].name); 
        printf("Phone Number : %s\n",addressBook->contacts[i].phone);
        printf("Email id     : %s\n",addressBook->contacts[i].email);     
    }

    char org[50];
    printf("\nEnter Your Name to edit contact: ");
    scanf(" %[^\n]",org);

    int matches[20];
    int count = 0;

    for(int i = 0; i < n;i++)
    {
        if(strcasecmp(addressBook->contacts[i].name,org) == 0)
        {
           matches[count++] = i;
        }
    }

    if(count == 0)
    {
        printf(":: Contact not found ::\n");
        return;
    }

    int indx = -1;

    if(count == 1)
    {
        indx = matches[0];// only one match found
    }
    else
    {
        char ph[20];
        printf("\nMultiple contacts found with the same name:\n");
        printf("Enter phone number of the contact to edit: ");
        scanf(" %[^\n]",ph);

        for(int i = 0; i<count;i++)
        {
            if(strcmp(addressBook->contacts[matches[i]].phone,ph) == 0)
            {
                indx = matches[i];
                printf(":: Contact Found ::\n");
                break;
            }
        }

        if(indx == -1)
        {
            printf("No contact with that phone number found.\n");
            return;
        }
    }

    //Now,display menue to edit the choosen contact 
    do
    {
        printf("\nWhat do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email id\n");
        printf("4. Save and Exit\n");
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
                name_edit(addressBook->contacts[indx].name);
                break;
            case 2:
                number_edit(addressBook->contacts[indx].phone);
                break;
            case 3:
                email_edit(addressBook->contacts[indx].email);
                break;
            case 4:
                printf("Saved and Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while (ch != 4);  

}

// Name Editing
void name_edit(char name[]) 
{
    int valid = 0;
    do{
        char namecpy[50];

        printf("Enter New Name: ");
        scanf(" %[^\n]",namecpy);

        int nm = name_valid(namecpy); // name validation
        if(nm == 0)
        {
            continue; // validation fails read data again
        }

        if(strcmp(name,namecpy) == 0) //if entered name is same
        {
            printf("Entered Name is already exsist.\n");
            continue;
        }
        
        strcpy(name,namecpy); // entered name is valid then copy to structure
        printf(":: Name Updated Successfully::\n");
        valid = 1;

    }while (!valid);
}

// Phone Number Editing
void number_edit(char phone[])
{
    int valid = 0;
    do
    {
        char phnum[20];
        printf("Enter New Phone number: ");
        scanf(" %[^\n]",phnum);

        int ph = number_valid(phnum);// phone number validation
        if(ph == 0)
        {
            continue; // invalid -> repeat
        }

        if(strcmp(phone,phnum) == 0)//if entered number is same
        {
            printf("Entered Phone number is already exsist.\n");
            continue;
        }

        strcpy(phone,phnum);// entered phone number is valid then copy to structure
        printf(":: Phone number Updated Successfully ::\n");
        valid = 1;

    }while (!valid);
}

// Email Editing
void email_edit(char email[])
{
    int valid = 0;
    do
    {
        char emailcpy[50];
        printf("Enter new Email-id: ");
        scanf(" %[^\n]",emailcpy);

        int em = email_valid(emailcpy);//Email validation
        if(em == 0)
        {
            continue;
        }

        if(strcmp(email,emailcpy) == 0)//if entered email is same
        {
            printf("Entered email is already exsist.\n");
            continue;
        }
    
        strcpy(email,emailcpy);// entered email is valid then copy to structure
        printf(":: Email Updated Successfully::\n");
        valid = 1;

    }while (!valid);
}