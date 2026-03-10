/*
NAME: CHAITHRA T
PROJECT: ADDRESSBOOK
This project is an Address Book made in C to save, search, edit, and delete contacts.
It also keeps contacts safe by saving them in a file.
DATE: 01/09/2025 to 23/09/2025
*/
#include<stdio.h>
#include <ctype.h>
#include "contact.h"
#include "validation.h"

int main() {
    int choice;
    AddressBook addressBook;//creating variable for Addressbook structure
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n"); 
        printf("2. Search contact\n");
        printf("3. Edit contact\n"); 
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if((scanf("%d",&choice))!= 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();  // remove invalid input
            continue;            // restart loop
        }
        switch (choice) {
            case 1:
                char ch;
                do {
                    createContact(&addressBook);  // add one contact
                    printf("\nDo you want to add another contact? (y/n): ");
                    scanf(" %c", &ch); // ask for more than one contact
                } while (ch == 'y' || ch == 'Y');
                break;
            case 2:
                searchContact(&addressBook); //function call for searchContact
                break;
            case 3:
                editContact(&addressBook); //function call for editContact
                break;
            case 4:
                deleteContact(&addressBook); //function call for deleteContact
                break;
            case 5:          
                listContacts(&addressBook); //function call for listContacts
                break;
            case 6:
                saveContactsToFile(&addressBook); //function call for saveContactsToFile
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
    return 0;
}
