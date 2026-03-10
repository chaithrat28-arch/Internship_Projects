#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "validation.h"
#include "contact.h"

/*
::VALIDATION::
Name Validation:
    1.Include upper and lower case alphabets (CORRECT)
    2.Space and '.' allowed (CORRECT)
    3.No Digits
    4.No punctuations
Phone Number Validation:
    1.Only Digits (CORRECT)
    2.Contain 10 digits (CORRECT)
    3.Unique Number (CORRECT)
    4.Characters are not allowed
Email Validation:
    1.chaithra12@gmail.com (CORRECT)
    2.ravi@123.com (INVALID)
    3.@gmail.com (INVALID)
    4.abc@ (INVALID)
    5.abc@gmail (INVALID)
    6.abc@gmail.comcom (INVALID)
    7.abc@@gmail.com (INVALID)
    8.abc..123@gmail.com (INVALID)
*/

/*
::VARIABLES::
>'valid' variable is for if validation done store the data to structure, if not retrun 0 to function call,
    ask the user to re-enter the details[for all data members]
>'i' variable for running loop for specified condition 
*/

//Name validation
int name_valid(const char name[])
{
    int valid=1,i=0; 
    while (name[i] != '\0')
    {
        if(i == 0)
        {
            if(name[i] >= 'A' && name[i] <= 'Z')// Starting letter shld be Capital letter
            {
                i++;
                continue;
            }
            else
            {
                printf("ERROR: Name should starts with capital letter\n");
                valid = 0;//not found, come out from current running loop
                break;
            }
        }
        else if(isalpha(name[i]) || name[i] == ' ' || name[i] == '.') //checking for alphabets,' ',and '.'
        {
            i++; // found,increment
            continue;  //continue till null character  
        }
        else
        {
            printf("ERROR: Name should contain only characters.\n");
            valid = 0;//not found, come out from current running loop
            break;
        }
    } 
    if(valid == 1)
    {
        // Name validation is success, return 1 to the function call
        return 1;
    }
    else
    {
        // Name validation is fails, return 0 to the function call
        printf("INFO: Validation not done, Enter Valid Name [Example: Chaithra T]\n");
        return 0;
    }
}

//Phone number Validation
int number_valid(const char phone[])
{
    int valid1 = 1,count = 0,i=0;
    //'count' is used to verify that entered number exactly 10 or not. 
    while (phone[i] != '\0')
    {
        if(isdigit(phone[i]))//includes only digits
        {
            count++; // count no. of digits
            i++;// if found increment
            continue; // continue till null character 
        }  
        else
        {
            printf("ERROR: Phone Number should contain only digits.\n");
            valid1 = 0; //not found, come out from current running loop
            break;
        }
    } 
    // checking for 10 digits
    if(count != 10)
    {
        printf("ERROR: Phone number should contain 10 digits.\n");
        valid1 = 0;
    } 
    if(valid1 == 1)
    {
        // Number validation is success, return 1 to the function call
        return 1;
    }
    else
    {
        // Number validation is fails, return 0 to the function call
        printf("INFO: Validation not done, Enter valid Phone Number [Example: 1234567890]\n");
        return 0;
    }
}

//Email id Validation
int email_valid(const char email[])
{
    int valid2 = 0,i = 0;
    int at = 0,dot = 0;// to chcek, at for @ and dot for '.' 
    while (email[i] != '\0')
    {
        if(i == 0)//check first character encountered with @ || . || digits
        {
            if(email[i] == '@' || email[i] == '.' || isdigit(email[i])) // this is not valid
            {
                valid2 = 0;
                break;
            }
        }
        
        if(islower(email[i])|| email[i] == '.' || email[i]== '_' || email[i] == '@' || isdigit(email[i]) || email[i] == '-')
        {
            if(email[i] == '@') // Check more than 1 times '@' occures
            {
                at++;
            }
            if(email[i] == '.') // Check more than 1 times '.' occures
            {
                dot++;
            }

            i++;
            valid2 = 1;
            continue;
        }
        else
        {
            valid2 = 0;
            break;
        }
    } 

    char *atptr = strchr(email,'@');//find @,index
    char *dotcom = strstr(email, ".com" ); // find .com

    int len = strlen(email);// length of the email

    if (at == 1 && (dotcom == email + len - 4) && valid2 && dot == 1)
    {
        if(atptr != NULL && dotcom > atptr + 1)
        {
            int domainRange = dotcom - (atptr + 1);// range between before .com and @
            if(domainRange > 0)
            {
                for(int k = 0; k < domainRange; k++)
                {
                    if(!isalpha(atptr[1+k]))
                    {
                        printf("INFO: Invalid email. Enter valid email [Example: chaithra12@gmail.com]\n");
                        return 0;
                    }
                }
                return 1;
                // Email validation is success, return 1 to the function call
            }
            else
            {
                printf("INFO: Invalid email. Enter valid email [Example: chaithra12@gmail.com]\n");
                return 0;
            }
        }
        else
        {
            printf("INFO: Invalid email. Enter valid email [Example: chaithra12@gmail.com]\n");
            return 0;
        } 
    }
    //email + len - 4 --> points to the last 4 chars of the string. Ensures .com starts exactly 4 characters before the null.
    //email -> base address,means 0 or location
    else
    {
        printf("ERROR: Email should contain '@' and '.com' once.\n");
        printf("INFO: Invalid email. Enter valid email [Example: chaithra12@gmail.com]\n");
        return 0;
    }
}