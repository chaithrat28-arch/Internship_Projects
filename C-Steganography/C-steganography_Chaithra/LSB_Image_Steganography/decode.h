#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include "types.h" // Contains user defined types
#include "common.h"

/* 
 * Structure to store information required for
 * Decoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
*/

#define MAX_FILE_SUFFIX 4
#define MAX_FILE_NAME 20
#define MAX_MAGIC_STRING 20

typedef struct _DecodeInfo
{
    /* Stego Image Info */
    char *stego_image_fname;
    FILE *fptr_stego_image;

    /* Output file Info*/
    char output_fname[MAX_FILE_NAME];
    char magic_string[MAX_MAGIC_STRING];
    int magic_size;

    int secret_file_extn_size;
    char secret_file_extn[MAX_FILE_SUFFIX];
    int secret_file_size;
    char secret_data[100];

    FILE *fptr_output_file;

} DecodeInfo;


/* Decoding function prototype */

/* Read and validate Encode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_files_for_decoding(DecodeInfo *decInfo);

/* Decoding Magic String */
Status decode_magic_string(FILE *fptr_stego_image,DecodeInfo *decInfo);

/* Decode a byte into LSB of image data array */
char decode_byte_from_lsb(char *image_buffer);

/* Decode secret file extenstion */
Status decode_secret_file_extn(FILE *fptr_stego_image, DecodeInfo *decInfo);

/*Decode size from lsb*/
int decode_size_from_lsb(char *size_buffer);

/* Decode secret file size */
Status decode_secret_file_size(FILE *fptr_stego_image, DecodeInfo *decInfo);

/* Decode secret file data*/
Status decode_secret_file_data(FILE *fptr_stego_image,DecodeInfo *decInfo);

#endif