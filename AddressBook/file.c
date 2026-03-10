#include <stdio.h>
#include "file.h"
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr; // creating file pointer

    if((fptr = fopen("Contacts.csv","w")) == NULL)// opening csv file in write mode,if exsist store data
    {
        printf("File not found\n");
        return;
    }

    fprintf(fptr,"%d\n",addressBook->contactCount);//printing contactcount value in contacts.csv file

    for(int i = 0; i < addressBook->contactCount;i++)
    {
        fprintf(fptr,"%d,%s,%s,%s\n",i + 1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fptr);// closing the file

    printf(":: Contacts saved successfully ::\n");
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr; // creating file pointer

    fptr = fopen("Contacts.csv","r"); // opening file in reading mode

    if(fptr == NULL)
    {
        printf("File not found\n");
        addressBook->contactCount = 0; // if contact.csv file is not found, then ,make contact count 0
        return;
    }

    fscanf(fptr, "%d\n", &addressBook->contactCount); // read contact count

    for(int i=0; i< addressBook->contactCount;i++)
    {
        int j; //to store the index value

        fscanf(fptr,"%d,%[^,],%[^,],%[^,\n]",&j,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fptr);// closng the file
}
