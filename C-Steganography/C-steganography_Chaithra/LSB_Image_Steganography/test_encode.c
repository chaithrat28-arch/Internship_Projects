1/*
Name: CHAITHRA T
Date: 27/10/2025
Project: LSB Image Steaganography
*/

#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include "common.h"

/*for user input magic string*/
char MAGIC_STRING[10];

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Error: Invalid Input\n");
        printf("---------------------------------------------------------------------------------------------------------------\n");
        printf("For Encoding type this command: ./a.out -e <input_file_name>.bmp <secret_file_name>.txt <output_file_name>.bmp\n");
        printf("For Decoding type this command: ./a.out -d <output_file_name>.bmp <output_file_name>.txt\n");
        printf("---------------------------------------------------------------------------------------------------------------\n");
    }
    else{
    //Encoding startes here,  
    if(check_operation_type(argv) == e_encode)
    {
        //checking for arguments
        if(argc < 4)    
        {
           printf("It is unsupported, Arguments are missing.\n");
           printf("----------------------------------------------------------------------------------------------\n");
           printf("For Encoding: ./a.out -e <input_file_name>.bmp <secret_file_name>.txt [<output_file_name>.bmp]\n");
           printf("----------------------------------------------------------------------------------------------\n");
           return e_failure;
        }
        printf("================================================\n");
        printf("You have choosed ENCODING..!\n");
        printf("================================================\n");

        EncodeInfo encInfo;
        //Performing read and validate for arguments
        if(read_and_validate_encode_args(argv,&encInfo) == e_success)
        {
            //taking magic string input from user
            printf("------------------------------------------------\n");
            printf("Enter the Magic String: ");
            scanf("%s", MAGIC_STRING);
            printf("------------------------------------------------\n");
            
            printf("------------------------------------------------\n");
            printf("Read and Validate is successfull\n");
            printf("------------------------------------------------\n");
            //Starts Encoding...
            if(do_encoding(&encInfo) == e_success)
            {
                printf("================================================\n");
                printf("Encoding successful....\n");
                printf("================================================\n");
            }
            else
            {
                printf("Encoding un-successful\n");
            }
        }
        else
        {
            printf("Read and Validate is un-successfull\n");
            return e_failure;
        }
    }
    else if(check_operation_type(argv) == e_decode)
    {
        //check arguments
        if(argc<3)    
        {
           printf("It is unsupported, Arguments are missing.\n");
           printf("-----------------------------------------------------------------------------\n");
           printf("For Decoding: ./a.out -d <output_file_name>.bmp [<output_file_name>.txt] \n");
           printf("-----------------------------------------------------------------------------\n");
           return e_failure;
        }

        printf("================================================\n");
        printf("You have choosed DECODING..!\n");
        printf("================================================\n");

        //taking magic string input from user to verify after decoding
        printf("Enter the same Magic String you have entered for Encoding: ");
        scanf("%s", MAGIC_STRING);
        printf("------------------------------------------------\n");

        DecodeInfo decInfo;
        //Performing read and validate for arguments
        if(read_and_validate_decode_args(argv,&decInfo) == e_success)
        {
            printf("------------------------------------------------\n");
            printf("Read and Validate is successfull\n");
            printf("------------------------------------------------\n");
            //Starts Encoding...
            if(do_decoding(&decInfo) == e_success)
            {
                printf("================================================\n");
                printf("Decoding successful....\n");
                printf("================================================\n");
            }
            else
            {
                printf("Decoding un-successful\n");
            }
        }
        else
        {
            printf("Read and Validate is un-successfull\n");
        }
    }

    //if user enetered any other arguments,it is unsupported
    else 
    {
        printf("It is unsupported..\n");
        printf("For Encoding pass -e as argument\nFor Decoding pass -d as argument\n");
        return e_failure;
    }
    }
    return e_success;
}

/*Checking for which operation sholud be performed*/
OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1],"-e") == 0)
    {
        return e_encode; //-e, perform encoding
    }
    else if(strcmp(argv[1],"-d") == 0)
    {
        return e_decode;//-d, perform decoding
    }
    else
    {
        return e_unsupported;//others, unsupported
    }
}
