#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tag_reader.h"
#include "types.h"

/*Read and validating input .mp3 file*/
Status read_and_validate(char *argv[], TagReader *tagreader)
{
    //checking for .mp3 file
    if(strstr(argv[2],".mp3") != NULL)
    {
        tagreader->mp3_fname = argv[2];
        //printf("sample.mp3 audio file is present\n");
    }
    else
    {
        printf("sample.mp3 audio file is not present\n");
        printf("INFO: Extension[.mp3] is required...!!!\n");
        return mp3_failure;
    }
    return mp3_success;
}

/*Opening .mp3 file for view*/
Status open_files(TagReader *tagreader)
{
    //opening .mp3 file in read mode
    tagreader -> mp3_fptr = fopen(tagreader->mp3_fname,"r");

    if(tagreader->mp3_fptr == NULL)
    {
        //if null, return error
        printf("Sample.mp3 file is not opened\n");
        return mp3_failure;
    }
    return mp3_success;
}

/*Verifying version of mp3 file*/
Status check_version(TagReader *tagreader)
{
    fseek(tagreader -> mp3_fptr, 0, SEEK_SET);

    //reading 3 bytes to check version name ID3
    fread(tagreader -> tag,3,1,tagreader -> mp3_fptr);

    tagreader -> tag[3] = '\0';

    if(strcmp(tagreader -> tag,"ID3") != 0)
    {
        printf("ERROR: Not a valid ID3 tag!\n");
        return mp3_failure;
    }
    //printf("tag -> %s\n",tagreader -> tag);

    //reading 2 bytes for checking version of ID3
    fread(tagreader->tag_version,2,1,tagreader -> mp3_fptr);

    tagreader->tag_version[2] = '\0';

    //printf("tag version -> %X %X\n", tagreader->tag_version[0],tagreader->tag_version[1]);

    if(tagreader->tag_version[0] != 3 || tagreader->tag_version[1] != 0)
    {
        return mp3_failure;
    }
    
    return mp3_success;
}

/*Performing view operation for .mp3 file*/
Status sample_mp3_view(TagReader *tagreader)
{
    char frame_id[4];
    uint size;
    unsigned char size_bytes[4];

    //skip header bytes
    fseek(tagreader -> mp3_fptr,10,SEEK_SET);

    for(int f = 1; f < 7; f++)
    {
        /*Read frame id*/
        fread(frame_id,4,1,tagreader -> mp3_fptr);

        /*read size of particular tag*/
        fread(size_bytes,4,1,tagreader -> mp3_fptr);

        //convert bigg endian system to little endian system bytes
        size = (size_bytes[0]<<24) | (size_bytes[1]<<16) | (size_bytes[2]<<8) | (size_bytes[3]);
        
        //skip 2 bytes for flag
        fseek(tagreader -> mp3_fptr,2,SEEK_CUR);

        /*Read data upto size rom sample.mp3 file*/
        char *data = malloc(size); //pointer to store data

        //read data upto size 
        fread(data,size,1,tagreader -> mp3_fptr);

        printf("    %s",frame_id);

        printf("     :   ");
        for(int i=0;i<size;i++)
        {
            printf("%c",data[i]);
        }
        printf("\n");
    
        free(data);
    }
    return mp3_success;
}