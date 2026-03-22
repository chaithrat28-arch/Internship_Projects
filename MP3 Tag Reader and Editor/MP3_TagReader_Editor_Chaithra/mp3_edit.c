#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tag_reader.h"
#include "types.h"

/*Read and validating input .mp3 file*/
Status read_and_validate_for_edit(int argc, char *argv[], TagReader *tagreader)
{
    // Checking for .mp3 file
    if (strstr(argv[4], ".mp3") != NULL)
    {
        tagreader->mp3_fname = argv[4];
    }
    else
    {
        printf("sample.mp3 audio file is not present\n");
        printf("INFO: Extension[.mp3] is required...!!!\n");
        return mp3_failure;
    }

    //copying changing data into string
    strcpy(tagreader->changing_data, argv[3]);

    //checking for respective edit option
    if (strcmp(argv[2], "-t") == 0)
    {
        printf("                    -:SELECTED TITLE CHANGE OPTION:-\n");
        strcpy(tagreader->frame_id, "TIT2");
    }
    else if (strcmp(argv[2], "-a") == 0)
    {
        printf("                    -:SELECTED ARTIST CHANGE OPTION:-\n");
        strcpy(tagreader->frame_id, "TPE1");
    }
    else if (strcmp(argv[2], "-A") == 0)
    {
        printf("                    -:SELECTED ALBUM CHANGE OPTION:-\n");
        strcpy(tagreader->frame_id, "TALB");
    }
    else if (strcmp(argv[2], "-m") == 0)
    {
        printf("                    -:SELECTED CONTENT CHANGE OPTION:-\n");
        strcpy(tagreader->frame_id, "TCON");
    }
    else if (strcmp(argv[2], "-y") == 0)
    {
        printf("                    -:SELECTED YEAR CHANGE OPTION:-\n");
        strcpy(tagreader->frame_id, "TYER");
    }
    else if (strcmp(argv[2], "-c") == 0)
    {
        printf("                    -:SELECTED COMMENT CHANGE OPTION:-\n");
        strcpy(tagreader->frame_id, "COMM");
    }
    else
    {
        printf("ERROR: Invalid Entry .....!!\n");
        printf("--------------------------------------------------------\n");
        printf("Enter -t ->to edit song title\n");
        printf("Enter -a ->to edit artist name\n");
        printf("Enter -A ->to edit album name\n");
        printf("Enter -y ->to edit year\n");
        printf("Enter -m ->to edit content\n");
        printf("Enter -c ->to edit comment\n");
        return mp3_failure;
    }
    return mp3_success;
}

/*Opening .mp3 file for edit*/
Status open_files_for_edit(TagReader *tagreader)
{
    //creating new fille for output after modification
    tagreader->output_fname = "output.mp3";

    // Open input and output files
    tagreader->mp3_fptr = fopen(tagreader->mp3_fname, "rb");
    tagreader->output_mp3_fptr = fopen(tagreader->output_fname, "wb");

    //if file pointer is null, print error
    if (tagreader->mp3_fptr == NULL)
    {
        printf("Sample.mp3 file is not opened\n");
        return mp3_failure;
    }

    if (tagreader->output_mp3_fptr == NULL)
    {
        printf("Output.mp3 file is not opened\n");
        return mp3_failure;
    }

    return mp3_success;
}

/*Performing edit operation for .mp3 file*/
Status sample_mp3_edit(TagReader *tagreader)
{
    char org_frame_id[5] = {0}; // storing origanal frame id,initialised with 0
    char *org_data;//to store originala frame content
    int size, new_size;
    unsigned char size_bytes[4];//converting big to little enidan
    unsigned char new_size_bytes[4];//converting little to big enidan
    unsigned char flag[2];//for flag bits

    //cheking for file pointer is null
    if (tagreader->mp3_fptr == NULL || tagreader->output_mp3_fptr == NULL)
    {
        printf("Input or output file not opened\n");
        return mp3_failure;
    }

    //making file pointer pointing at beginging
    fseek(tagreader->mp3_fptr, 0, SEEK_SET);
    fseek(tagreader->output_mp3_fptr, 0, SEEK_SET);

    //reading 10 header bytes and writing into output file
    fread(tagreader->header, 10, 1, tagreader->mp3_fptr);
    fwrite(tagreader->header, 10, 1, tagreader->output_mp3_fptr);

    for (int f = 1; f < 7; f++)
    {
        /*Reading original data from .mp3 file*/
        fread(org_frame_id, 4, 1, tagreader->mp3_fptr);
        org_frame_id[4] = '\0'; // adding null character

        fread(size_bytes, 4, 1, tagreader->mp3_fptr);
        size = (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8) | size_bytes[3];

        fread(flag, 2, 1, tagreader->mp3_fptr);

        org_data = malloc(size + 1);
        fread(org_data, size, 1, tagreader->mp3_fptr);
        org_data[size] = '\0'; // adding null character

        // compare original frame with new frame
        if (strcmp(tagreader->frame_id, org_frame_id) == 0)
        {
            /* writeing new data into output file*/
            fwrite(tagreader->frame_id, 4, 1, tagreader->output_mp3_fptr);

            // calculate new frame size 
            new_size = strlen(tagreader->changing_data);

            // convert size to big-endian
            new_size_bytes[0] = (new_size >> 24) & 0xFF;
            new_size_bytes[1] = (new_size >> 16) & 0xFF;
            new_size_bytes[2] = (new_size >> 8) & 0xFF;
            new_size_bytes[3] = new_size & 0xFF;

            fwrite(new_size_bytes, 4, 1, tagreader->output_mp3_fptr);

            fwrite(flag, 2, 1, tagreader->output_mp3_fptr);

            fwrite(tagreader->changing_data, new_size, 1, tagreader->output_mp3_fptr);
        }
        else
        {
            // writing original data into output file
            fwrite(org_frame_id, 4, 1, tagreader->output_mp3_fptr);
            fwrite(size_bytes, 4, 1, tagreader->output_mp3_fptr);
            fwrite(flag, 2, 1, tagreader->output_mp3_fptr);
            fwrite(org_data, size, 1, tagreader->output_mp3_fptr);
        }

        free(org_data);
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("               %s     :       %s\n", tagreader->frame_id, tagreader->changing_data);

    char ch;
    while (fread(&ch, 1, 1, tagreader->mp3_fptr) > 0)
    {
        fwrite(&ch, 1, 1, tagreader->output_mp3_fptr);
    }

    fclose(tagreader->mp3_fptr);
    fclose(tagreader->output_mp3_fptr);

    remove(tagreader->mp3_fname);                // delete old file
    rename(tagreader->output_fname, tagreader->mp3_fname); // rename output file as original file

    return mp3_success;
}
