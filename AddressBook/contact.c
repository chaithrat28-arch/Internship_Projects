#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validation.h"
#include "search.h"
#include "edit.h"
#include "delete.h"

void listContacts(AddressBook *addressBook) 
{
    int n = addressBook->contactCount; // No. of contacts
    if(addressBook->contactCount == 0) // check for exsisting contacts
    {
        printf(":: No Contacts found ::\n");
    }
    else// contacts exsist
    {
        printf(":: List of Contacts ::\n"); // Displaying Contacts
        for(int i = 0; i < n; i++)
        {
            printf("Contact details of %d:\n",i+1);
            printf("Name         : %s\n",(*addressBook).contacts[i].name); //printing name
            printf("Phone Number : %s\n",addressBook->contacts[i].phone); //printing phone number
            printf("Email id     : %s\n",addressBook->contacts[i].email); //printing email
        }
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
    Contact c;
    char namescpy[30]; // temporary strings to store data
    char phnumcpy[10];
    char mailcpy[30];
    int valid;//validation done properly, this variable break the loop
    printf("\n:: Enter Contact details ::\n");
    //---Name Validation---
    do
    {
        printf("\nEnter Your Name:");
        scanf(" %[^\n]",namescpy);
        valid = name_valid(namescpy);//Perform validation

        if(valid == 1)//validation done
        {
            strcpy(c.name,namescpy); // After validation name is stored in structure
        }
    } while (!valid);

    //---Phone Number Validation---
    do   
    {
        int exsist = 0;// If the entered number is exsist in other contacts
        printf("Enter Your Phone Number:");
        scanf(" %[^\n]",phnumcpy);   
        valid = number_valid(phnumcpy); //Perform validation
       
        if(valid == 1)//validation dane
        {
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if((strcmp(addressBook->contacts[i].phone,phnumcpy) == 0)) //if entered name is same
                {
                    exsist = 1;
                    printf("Entered Number is already exsist in other contact. Phone Number should be unique.\n");
                    break;
                }
            }
            if(exsist == 1)
            {
                valid = 0;
                continue;
            }
            else
            {
                strcpy(c.phone,phnumcpy);// After validation phone number is stored in structure
            }
 
        }
        
    } while (!valid);

    //---Email id validation---
    do
    {
        int exsist = 0;
        printf("Enter Your Email-id:");
        scanf(" %[^\n]",mailcpy);   
        valid = email_valid(mailcpy); //Perform validation
        if(valid == 1)// validation done
        {
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if((strcmp(addressBook->contacts[i].email,mailcpy) == 0)) //if entered name is same
                {
                    exsist = 1;
                    printf("Entered Email-id is already exsist in other contact. Email-id should be unique.\n");
                    break;
                }
            }
            if(exsist == 1)
            {
                valid = 0;
                continue;
            }
            else
            {
                strcpy(c.email,mailcpy);// After validation email is stored in structure
            }
        }

    } while (!valid);
    
    addressBook->contacts[addressBook->contactCount++] = c; // every data members are stored to AddressBook structure

    printf(":: Contact Added Successfully ::\n");
    
    // addressBook-> variable of AddressBook structure & contacts-> variable of Contacts structure
    // addressBook->contacts : first addressBook then goto contacts,
    // addressBook->contactCount++ : in addressBook, increase contactcount[no. of contacts]
    
}

void searchContact(AddressBook *addressBook) 
{
    if(addressBook->contactCount == 0) // check for exsisting contacts
    {
        printf(":: No Contacts found to search ::\n");
    }
    else
    {
        search(addressBook);//function call for search
    }  
}

void editContact(AddressBook *addressBook)
{
    int valid = 0;
    if(addressBook->contactCount == 0) // check for exsisting contacts
    {
        printf(":: No Contacts found to edit ::\n");
    }
    else
    {
        edit(addressBook); //function call for edit    
    } 
}

void deleteContact(AddressBook *addressBook)
{
	int valid = 0;
    if(addressBook->contactCount == 0)// check for exsisting contacts
    {
        printf(":: No Contacts found to edit ::\n");
    }
    else
    {
        deleting(addressBook); //function call for delete    
    } 
}
