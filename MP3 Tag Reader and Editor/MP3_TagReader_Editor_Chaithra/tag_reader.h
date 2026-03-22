#ifndef TAG_READER_H
#define TAG_READER_H

#include<stdio.h>
#include "types.h"

typedef struct _TagReader
{
    //source file information
    FILE *mp3_fptr;
    char *mp3_fname;

    //to check version tag
    char tag[4];
    char tag_version[2];

    //output mp3 file
    char *output_fname;
    FILE *output_mp3_fptr;
    char changing_data[30];
    char frame_id[5];
    char header[10];

}TagReader;

/*To check which operation should be performed*/
OperationType check_operation_type(char *argv[]);

/*Read and validating the arguments*/
Status read_and_validate(char *argv[], TagReader *tagreader);

/*Read and validating the arguments for edit*/
Status read_and_validate_for_edit(int argc,char *argv[], TagReader *tagreader);

/* Get File pointers for i/p and o/p files */
Status open_files(TagReader *tagreader);

/* Get File pointers for i/p and o/p files for editing */
Status open_files_for_edit(TagReader *tagreader);

/*To check version of mp3 file*/
Status check_version(TagReader *tagreader);

/*To display information of mp3 file*/
Status sample_mp3_view(TagReader *tagreader);

/*To edit information of mp3 file*/
Status sample_mp3_edit(TagReader *tagreader);

#endif