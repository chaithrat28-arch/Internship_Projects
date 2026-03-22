#include"head.h"

//fil name validation
int file_name_validation(char *fname,file_list **f_head)
{
    //checking file is empty or not
    if(is_empty_file(fname) == SUCCESS)
        {
            //inserting file name to linked list
            if(insert_fname(f_head,fname) == SUCCESS)
            {
                return SUCCESS;
            }
            else
            {
                return FAILURE;
            }
        }
        else
        {
            return EMPTY;
        }    
    
}

//to check file is empty or not
int is_empty_file(char *fname)
{
    FILE *fp;
    fp = fopen(fname,"r");
    if(fp == NULL)
    {
        //printf("File can not found\n");
        return 1;
    }
    fseek(fp , 0, SEEK_END);
    int size = ftell(fp);
    if(size==0)
    {
        //file empty
        return FAILURE;
    }
    else
    {
        //not empty
        return SUCCESS;
    }
}

//inserting file name to linked list
int insert_fname(file_list **f_head,char *fname)
{
    file_list *new = malloc(sizeof(file_list));

    if(new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->filename,fname);
    new->link = NULL;

    if(*f_head == NULL)
    {
        *f_head = new;
        return SUCCESS;
    }

    file_list *temp = *f_head;

    while(temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new;
    return SUCCESS;
}

//to check file reached end of the file
int is_eof(FILE *fp)
{
    int ch = fgetc(fp); //get the character from the file
    if(ch == EOF)
    {
        return 0;
    }
    ungetc(ch,fp); //put the character back to the file
    return 1;
}