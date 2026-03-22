#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"
#include "common.h"

/* Read and Validating the extensions */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    //checking for stego.bmp file
    if(argv[2] == NULL)
    {
        printf("stego.bmp is not present\n");
        return e_failure;
    }
    else if(strstr(argv[2],".bmp") != NULL)
    {
        printf("stego.bmp is present\n");
        decInfo->stego_image_fname = argv[2]; 
    }
    else
    {
        printf("INFO: Extension[.bmp] is required\n");
        return e_failure;
    }

    //check for output.txt file
    if(argv[3] == NULL)
    {
        printf("output.txt is created\n");
        strcpy(decInfo->output_fname,"output");
    }
    else if(strstr(argv[3],".txt") != NULL)
    {
        strcpy(decInfo->output_fname,strtok(argv[3],"."));
        printf("output.txt is present\n");   
    }

    return e_success;
}

/*Performing Decoding*/
Status do_decoding(DecodeInfo *decInfo)
{
    /* Checking for all files are opened or not*/
    if(open_files_for_decoding(decInfo) == e_success)
    {
        printf("-------------------------------------------------\n");
        printf("All files are opened successfully\n");
        printf("-------------------------------------------------\n");
        /*Decoding Magic string*/
        if(decode_magic_string(decInfo -> fptr_stego_image,decInfo) == e_success)
        {
            //compare magic string after decoding with entered magic string from user
            if(strcmp(decInfo -> magic_string,MAGIC_STRING) == 0)
            {
                printf("Decoding magic string is successfull\n");
                printf("-------------------------------------------------\n");
                printf("After decoding,the entered magic string is same.\n");
                printf("-------------------------------------------------\n");

                //decoding secret file extension
                if(decode_secret_file_extn(decInfo -> fptr_stego_image,decInfo) == e_success)
                {
                    printf("-------------------------------------------------\n");
                    printf("Decoding secret file extension is succesfull\n");

                    printf("Output file is now opened\n");
                    printf("-------------------------------------------------\n");

                    //decoding secret file size
                    if(decode_secret_file_size(decInfo -> fptr_stego_image,decInfo) == e_success)
                    {
                        printf("Decoding secret file size is successfull\n");
                        printf("-------------------------------------------------\n");
                        //Decoding secret file data
                        if(decode_secret_file_data(decInfo -> fptr_stego_image,decInfo) == e_success)
                        {
                            printf("Decoding secret message is successfull\n");
                            printf("-------------------------------------------------\n");
                        }
                        else
                        {
                            printf("Decoding secret message is un-successfull\n");
                        }
                    }
                    else
                    {
                        printf("Decoding secret file size is un-successfull\n");
                    }
                }
                else
                {
                   printf("Decoding secret file extension is un-succesfull\n"); 
                }
            }
            else
            {
                printf("Decoded magic string is not same as encooded magic string\n");
            }
        }
        else
        {
            printf("Decoding magic string is un-successfull\n");
        }
    }
    else
    {
        printf("All files are not opened successfully\n");
    }

    return e_success;
}

/*Opening required files for Decoding*/
Status open_files_for_decoding(DecodeInfo *decInfo)
{
    //opening sego.bmp file in read mode ?-> to fetch data
    decInfo -> fptr_stego_image = fopen(decInfo -> stego_image_fname,"r");

    if(decInfo -> fptr_stego_image == NULL)
    {
        printf("Stego file is not opened\n");
        return e_failure;
    }
    else
    {
        printf("Stego file is opened\n");
    } 

    return e_success;
}

/*Decoding Magic string and its size*/
Status decode_magic_string(FILE *fptr_stego_image,DecodeInfo *decInfo)
{
    /*taking 8 bytes from stego.bmp to decode*/
    char arr1[8];

    fseek(fptr_stego_image,54,SEEK_SET);

    /*taking 32 bytes from stego.bmp to decode size*/
    char arr[32];

    fread(arr,32,1,fptr_stego_image);

    /*Decoding magic string size and storing in variable*/
    decInfo -> magic_size = decode_size_from_lsb(arr);

    printf("--Size of magic string is %d\n",decInfo -> magic_size);

    for(int i=0;i<decInfo -> magic_size;i++)
    {
        fread(arr1,8,1,fptr_stego_image);

         /*Decoding magic string and storing in character array*/
        decInfo -> magic_string[i] = decode_byte_from_lsb(arr1);
    }

    decInfo -> magic_string[decInfo -> magic_size] = '\0';

    printf("--Magic string is %s\n",MAGIC_STRING);

    printf("--After decode magic string is %s\n",decInfo -> magic_string);

    return e_success;
}

/*Decoding Character from lsb*/
char decode_byte_from_lsb(char *image_buffer)
{
    char data = 0;

    //Decoding character from stego.bmp file by taking 8bytes
    for(int i=0;i<8;i++)
    {
        data = data | ((image_buffer[i] & 1) << i);
    }
    return data;
}

/*Decoding secret file extension and size*/
Status decode_secret_file_extn(FILE *fptr_stego_image, DecodeInfo *decInfo)
{
    char arr[32];

    fread(arr,32,1,fptr_stego_image);

    //Decoding secret file extension size
    decInfo -> secret_file_extn_size = decode_size_from_lsb(arr);

    printf("--Size of secret file extension %d\n",decInfo -> secret_file_extn_size);

    for(int i = 0 ; i <decInfo -> secret_file_extn_size; i++)
    {
        fread(arr,8,1,fptr_stego_image);

        //Decoding secret file extension
        decInfo -> secret_file_extn[i] = decode_byte_from_lsb(arr);
    }

    decInfo -> secret_file_extn[decInfo -> secret_file_extn_size] = '\0';

    printf("--After decode secret file extension is %s\n",decInfo -> secret_file_extn);

    //concatenation of output file
    strcat(decInfo->output_fname,decInfo -> secret_file_extn);

    //open output file in write mode
    decInfo -> fptr_output_file = fopen(decInfo->output_fname,"w");

    return e_success;
}

/*Decoding size from lsb*/
int decode_size_from_lsb(char *size_buffer)
{
    int size = 0;

    //Decoding integer(size) from stego.bmp file by taking 32 bytes
    for(int i=0;i<32;i++)
    {
        size = size | ((size_buffer[i] & 1) << i);
    }
    return size;
}

/*Decoding secret file size*/
Status decode_secret_file_size(FILE *fptr_stego_image, DecodeInfo *decInfo)
{
    char arr[32];

    fread(arr,32,1,fptr_stego_image);

    //Decoding secret file size and storing in variable
    decInfo -> secret_file_size = decode_size_from_lsb(arr);

    printf("--Size of secret file is %d\n",decInfo -> secret_file_size);

    return e_success;
}

/*Decoding secret file data*/
Status decode_secret_file_data(FILE *fptr_stego_image,DecodeInfo *decInfo)
{
    char arr[8];

    for(int i = 0 ; i <decInfo -> secret_file_size; i++)
    {
        fread(arr,8,1,fptr_stego_image);

        //decoding secret file data and storing in character array
        decInfo -> secret_data[i] = decode_byte_from_lsb(arr);
    }

    decInfo -> secret_data[decInfo -> secret_file_size] = '\0';

    //After complete Decoding secret data is written to output file
    fwrite(decInfo -> secret_data,decInfo -> secret_file_size,1,decInfo -> fptr_output_file);

    return e_success;
}