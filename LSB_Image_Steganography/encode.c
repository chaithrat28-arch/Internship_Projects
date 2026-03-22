#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Read and Validating the extensions */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    //checking for .bmp file
    if(strstr(argv[2],".bmp") != NULL)
    {
        encInfo->src_image_fname = argv[2];
        printf("beautiful.bmp is present\n");
    }
    else
    {
        printf("beautiful.bmp is not present\n");
        printf("INFO: Extension[.bmp] is required...!!!\n");
        return e_failure;
    }
    //check for secret.txt file
    if(strstr(argv[3],".txt") != NULL)
    {
        encInfo->secret_fname = argv[3];
        printf("secret.txt is present\n");
    }
    else
    {
        printf("INFO: Extension[.txt] is required...!!!\n");
        printf("secret.txt is not present\n");
        
        return e_failure;
    }
    //check for stego.bmp file
    if(argv[4] == NULL)
    {
        //if NULL, create new stego.bmp file
        printf("Stego.bmp file created successfully\n");
        encInfo->stego_image_fname = "stego.bmp";
        
    }
    else if(strstr(argv[4],".bmp") != NULL)
    {
        printf("stego.bmp is present\n");
        encInfo->stego_image_fname = argv[4]; 
    }
    else
    {
        printf("INFO: Extension[.bmp] is required... !!!\n"); 
        return e_failure;
    }

    return e_success;
}

/* Performing Encoding*/
Status do_encoding(EncodeInfo *encInfo)
{
    /* Checking for all files are opened or not*/
    if(open_files(encInfo) == e_success)
    {
        printf("------------------------------------------------\n");
        printf("All files are opened successfully\n");
        printf("------------------------------------------------\n");
    }
    else
    {
        printf("All files are not opened successfully\n");
        return e_failure;
    }
    /* Checking for image capcity which can hold entire encoding bytes*/
    if(check_capacity(encInfo) == e_success)
    {
        printf("------------------------------------------------\n");
        printf("Image having Sufficient size\n");
        printf("------------------------------------------------\n");
        /* Copying header (54bytes fixed) to destination file (stego.bmp)*/
        if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image))
        {
            printf("Header file is copied successfull\n");
            printf("------------------------------------------------\n");
            /*Encoding Magic string*/
            if(encode_magic_string(MAGIC_STRING,encInfo))
            {
                printf("Encoding magic string is successfull\n");
                printf("------------------------------------------------\n");
                /*Encoding secret file extension and size of that extension (.txt->4 bytes )*/
                if(encode_secret_file_extn(strstr(encInfo->secret_fname,".txt"),encInfo))
                {
                    printf("Encoding secret file extension is succesfull\n");
                    printf("------------------------------------------------\n");
                    /*Encoding secret file size(a password)*/
                    if(encode_secret_file_size(encInfo->size_secret_file,encInfo))
                    {
                        printf("Encoding secret file size is successfull\n");
                        printf("------------------------------------------------\n");
                        /* Encoding secret message data*/
                        if(encode_secret_file_data(encInfo))
                        {
                            printf("Encoding secret message is successfull\n");
                            printf("------------------------------------------------\n");
                            /*Copying remaining dta left in beautiful.bmp file*/
                            if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image) == e_success)
                            {
                                printf("Remaining data copied to output file is successfull\n");
                                printf("------------------------------------------------\n");
                            }
                            else
                            {
                                printf("Remaining data copied to output file is un-successfull\n");
                            }
                        }
                        else
                        {
                           printf("Encoding secret message is un-successfull\n"); 
                        }
                    }
                    else
                    {
                        printf("Encoding secret file size is un-successfull\n");
                    }
                }
                else
                {
                    printf("Encoding secret file extension is un-succesfull\n");
                }
            }
            else
            {
                printf("Encoding magic string is un-successfull\n");
            }
        }
        else
        {
            printf("Copied header file is un-successfull\n");
        }
    }
    else
    {
        printf("No Sufficient size\n");
    }

    return e_success;
}

/*Opening required files for Encoding*/
Status open_files(EncodeInfo *encInfo)
{
    //opening beautiful.bmp file in read mode ?-> to fetch data
    encInfo -> fptr_src_image = fopen(encInfo -> src_image_fname,"r");

    if(encInfo->fptr_src_image == NULL)
    {
        printf("Source file is not opened\n");
        return e_failure;
    }
    else
    {
        printf("Source file is opened\n");
    }
    //opening secret.txt file in read mode ?-> to fetch data
    encInfo -> fptr_secret = fopen(encInfo -> secret_fname,"r");
    
    if(encInfo->fptr_secret == NULL)
    {
        printf("Secret file is not opened\n");
        return e_failure;
    }
    else
    {
        printf("Secret file is opened\n");
    }
    //opening stego.bmp file in write mode ?-> to write encoding data into o/p file
    encInfo -> fptr_stego_image = fopen(encInfo -> stego_image_fname,"w");
    
    if(encInfo->fptr_stego_image == NULL)
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

/* Checking the status of image campacity*/
Status check_capacity(EncodeInfo *encInfo)
{
    // getting image size (beautiful.bmp)
    encInfo -> image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);

    if( encInfo -> image_capacity != 0)
    {
        printf("Found Image size\n");
    }
    else
    {
        return e_failure;
    }
    // getting secret file size(password)
    encInfo -> size_secret_file = get_file_size(encInfo->fptr_secret);

    if(encInfo -> size_secret_file != 0)
    {
        printf("Found Secret file size\n");
    }
    else
    {
        return e_failure;
    }
    //checking for our o/p file has the capcity to hold all Encoded data
    if(encInfo -> image_capacity < (54 * ( (strlen(MAGIC_STRING) + 4 + 4 + 4) * (encInfo -> size_secret_file)* 8)))
    {
        return e_failure;
    }

    return e_success;
}

/* To get the size of image file(beautiful.bmp)*/
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // 18th byte of .bmp file
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width of .bmp file (int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height of .bmp file (int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* To get secret file size( character count-->password)*/
uint get_file_size(FILE *fptr)
{
    fseek(fptr,0,SEEK_END);
    //to get file size make file ponting to end

    printf("size of secret file = %lu\n",ftell(fptr));

    //return secret file data size
    return ftell(fptr);
}

/* Copying Header file to stego.bmp file(O/p file)*/
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_stego_image)
{
    int arr[54];

    //making pointer at the begining of the file
    fseek(fptr_src_image,0,SEEK_SET);

    //reading starting 54 bytes of data from .bmp file in one go
    fread(arr,54,1,fptr_src_image);

    //writing 54 bytes into o/p file in one go
    fwrite(arr,54,1,fptr_stego_image);
}

/* Encoding magic string*/
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    int size_magic = strlen(MAGIC_STRING);

    char arr[32];

    //fetch 32 bytes if buffer bytes fom source 
    fread(arr,32,1,encInfo->fptr_src_image);

    //perform encode byte to lsb(integer value encoding)
    encode_size_to_lsb(size_magic,arr);

    fwrite(arr,32,1,encInfo->fptr_stego_image);

    encode_data_to_image(MAGIC_STRING,size_magic,encInfo->fptr_src_image,encInfo->fptr_stego_image);
}

/*Encoding for each character of given input*/
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char arr[8];
    // for encofing 1byte of data we required 8bytes of data from source file
    for(int i=0;i<size;i++)
    {
        //size-->how many charcaters
        fread(arr,8,1,fptr_src_image);

        encode_byte_to_lsb(data[i],arr);

        fwrite(arr,8,1,fptr_stego_image);
    }
}

/*Encoding character to lsb*/
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    for(int i = 0;i<8;i++)
    {
        image_buffer[i] = (image_buffer[i] & (~1)) | ((data & (1<<i)) >> i); 
        //encoding each bit using buffer of 8bytes
    }
}

/* Enconding Secret file extension*/
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    //length of the extension(.txt or .jpeg or etc)
    int size = strlen(file_extn);

    char arr[32];

    for(int i=0;i<size;i++)    
    {
        encInfo->extn_secret_file[i] = file_extn[i];
    }

    //fetch 32 bytes if buffer bytes fom source 
    fread(arr,32,1,encInfo->fptr_src_image);

    //perform encode byte to lsb(integer value encoding)
    encode_size_to_lsb(size,arr);

    fwrite(arr,32,1,encInfo->fptr_stego_image);

    //encoding the extension(.txt)
    encode_data_to_image(encInfo->extn_secret_file,size,encInfo->fptr_src_image,encInfo->fptr_stego_image);

}

/* Encoding size to lsb (integer encoding -> 32 bits)*/
Status encode_size_to_lsb(int size, char *size_buffer)
{
    for(int i = 0;i<32;i++)
    {
        size_buffer[i] = (size_buffer[i] & (~1)) | ((size & (1<<i)) >> i); 
        //encoding size at lsb
    }
}

/*Encoding secret file size(pasword length)*/
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char arr[32];

    //fetching 32 bits from source file(.bmp)
    fread(arr,32,1,encInfo->fptr_src_image);

    //encoding size to lsb 
    encode_size_to_lsb(file_size,arr);

    //after writing to stego.bmp file
    fwrite(arr,32,1,encInfo->fptr_stego_image);

}

/*Encoding secret file data(password)*/
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    int size = encInfo -> size_secret_file;//storing extension size of secret file
    
    fseek(encInfo->fptr_secret,0,SEEK_SET);
    
    char ch,data[100];
    int i = 0;
    while((ch = fgetc(encInfo->fptr_secret)) != EOF)
    {
        data[i++] = ch;
    }
    //character encoding of secret msg data
    encode_data_to_image(data,size,encInfo->fptr_src_image,encInfo->fptr_stego_image);
}

/* Copying Remainging data*/
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch;

    if (fptr_src == NULL || fptr_dest == NULL)
        return e_failure;

    //reading remaining bytes from beautiful.bmp file
    while(fread(&ch,1,1,fptr_src) > 0) 
    {
        //writing remaining bytes into o/p file in one go
        fwrite(&ch,1,1,fptr_dest);
    }

    return e_success;
}