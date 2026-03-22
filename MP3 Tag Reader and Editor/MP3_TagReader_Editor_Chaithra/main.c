/*
Name : Chaithra T
Date: 28/10/25 - 6/11/25
Description: A C-based MP3 tag editor that allows viewing and modifying ID3 metadata
               such as Title, Artist, Album, Year, Genre, and Comments
*/
#include<stdio.h>
#include<string.h>
#include "tag_reader.h"
#include "types.h"

int main(int argc,char *argv[])
{
    /*Cheking for arguments count*/
    if(argc < 2)
    {
        printf("ERROR: Invalid Argument..!!\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("                              -:USAGE:-\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("To View please pass: ./a.out -v mp3filename\n");
        printf("To Edit please pass: ./a.out -e -t/-a/-A/-y/-m/-c changing_text mp3filename\n");
        printf("To get Help please pass: ./a.out --help\n");
        printf("-----------------------------------------------------------------------------\n");
    }

    else{

        /*Checking for operation type, for view*/
    if(check_operation_type(argv) == mp3_view)
    {
        //checking arguments for view
        if(argc < 3)    
        {
           printf("It is unsupported, Arguments are missing.\n");
           printf("----------------------------------------------------------------------------------------------\n");
           printf("To View pass: ./a.out -v mp3filename\n");
           printf("----------------------------------------------------------------------------------------------\n");
           return mp3_failure;
        }
        printf("==============================================================================\n");
        printf("                        -:SELECTED VIEW DETAILS:-\n");
        printf("==============================================================================\n");

        TagReader tagreader;

        //performing read and validation for view
        if(read_and_validate(argv,&tagreader) != mp3_success)
        {
            printf("ERROR: Validation of mp3 file is not done..!!\n");
            printf("--------------------------------------------------------\n");
        }
        
        //opeining files for view operation
        if(open_files(&tagreader) != mp3_success)
        {
            printf("ERROR: Failed to Open .mp3 file..!!\n");
            printf("--------------------------------------------------------\n");
        }
        
        //checking version for .mp3 file
        if(check_version(&tagreader)!= mp3_success)
        {
            printf("ERROR: Validation of mp3 file Tag version is not done..!!\n");
            printf("----------------------------------------------------------\n");
        }

        printf("                    -:MP3 TAG READER AND EDITOR FOR ID3V2:-\n");
        printf("------------------------------------------------------------------------------\n");

        //Performing view operation for .mp3 file
        if(sample_mp3_view(&tagreader) == mp3_success)
        {
            printf("==============================================================================\n");
            printf("                      -:DETAILS DISPLAYED SUCCESSFULLY:-\n");
            printf("==============================================================================\n");
        }
        else
        {
            printf("ERROR: Having Issue with displaying information of .mp3 file\n");
            printf("------------------------------------------------------------\n");
        }

    }
    /*Checking for operation type, for view*/
    else if(check_operation_type(argv) == mp3_edit)
    {
        //checking arguments for edit
        if(argc < 5)    
        {
           printf("It is unsupported, Arguments are missing.\n");
           printf("----------------------------------------------------------------------------------------------\n");
           printf("To Edit pass: ./a.out -e -t/-a/-A/-y/-m/-c changing_text mp3filename\n");
           printf("----------------------------------------------------------------------------------------------\n");
           return mp3_failure;
        }

        printf("===============================================================================\n");
        printf("                        -:SELECTED EDIT DETAILS:-\n");
        printf("===============================================================================\n");
    
        TagReader tagreader;

        //performing read and validation for edit
        if(read_and_validate_for_edit(argc,argv,&tagreader) != mp3_success)
        {
            printf("ERROR: Validation of mp3 file is not done..!!\n");
            printf("--------------------------------------------------------\n");
            return mp3_failure;
        }

        //opeining files for edit operation
        if(open_files_for_edit(&tagreader) != mp3_success)
        {
            printf("ERROR: Failed to Open .mp3 file..!!\n");
            printf("--------------------------------------------------------\n");
            return mp3_failure;
        }

        //Performing edit operation for .mp3 file
        if(sample_mp3_edit(&tagreader) == mp3_success)
        {
            printf("===============================================================================\n");
            printf("                  -:%s CHANGED SUCCESSFULLY:-\n",tagreader.frame_id);
            printf("===============================================================================\n");
        }
        else
        {
            printf("ERROR: Having Issue with Editing information of .mp3 file\n");
            printf("------------------------------------------------------------\n");
            return mp3_failure;
        }
   
    }
    /*Pring help message for incorrect input*/
    else if(check_operation_type(argv) == mp3_help)
    {
        printf("-----------------------------------------------------------------------------\n");
        printf("                              -:HELP MENUE:-\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("1. -v -> to edit mp3 file\n");
        printf("2. -e -> to edit mp3 file\n");
        printf("    2.1. -t ->to edit song title\n");
        printf("    2.2. -a ->to edit artist name\n");
        printf("    2.3. -A ->to edit album name\n");
        printf("    2.4. -y ->to edit year\n");
        printf("    2.5. -m ->to edit content\n");
        printf("    2.6. -c ->to edit comment\n");
        printf("-----------------------------------------------------------------------------\n");
    }
    else
    {
        printf("It is unsupported..!!!\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("To View pass: -v \n");
        printf("To Edit pass: -e \n");
        printf("To get Help pass: --help\n");
        printf("-----------------------------------------------------------------------------\n");
        return mp3_failure;
    }
    }
    return mp3_success;
}

/*Checking for which operation sholud be performed*/
OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1],"-v") == 0)
    {
        return mp3_view; //-v, to view mp3 file
    }
    else if(strcmp(argv[1],"-e") == 0)
    {
        return mp3_edit;//-e, to edit mp3 file
    }
    else if(strcmp(argv[1],"--help") == 0)
    {
        return mp3_help; //--help, to display usage message
    }
    else
    {
        return mp3_unsupported;//others, unsupported
    }
}