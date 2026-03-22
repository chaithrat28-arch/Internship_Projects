#include"head.h"

int create_flag;

//creating database
int create_db(hash_t *arr, file_list *f_head)
{
    /* if database already created, do not allow again */
    if (create_flag == 1)
    {
        printf("ERROR: Database already created\n");
        return 3;
    }

    /* update must be done before create */
    // if (update_flag == 1)
    // {
    //     printf("ERROR: Update DB first, then Create DB\n");
    //     return FAILURE;
    // }

    create_flag = 0;

    int idx;
    file_list *f = f_head;

    /* traverse through all input files */
    while (f != NULL)
    {
        /* open file */
        FILE *fp = fopen(f->filename, "r");
        if (fp == NULL)
        {
            printf("File not found: %s\n", f->filename);
            return FAILURE;
        }

        char word[100];

        /* read each word from file */
        while (fscanf(fp, "%99s", word) == 1)
        {
            /* find hash index */
            idx = char_idx(word[0]);

            Main_node *temp = arr[idx].h_main_link;
            Main_node *prev = NULL;

            /* check if word already exists in hash table */
            while (temp != NULL)
            {
                if (strcmp(temp->word, word) == 0)
                    break;

                prev = temp;
                temp = temp->main_link;
            }

            /* CASE 1: word not found */
            if (temp == NULL)
            {
                /* create main node */
                Main_node *mnew = malloc(sizeof(Main_node));
                Sub_node *snew = malloc(sizeof(Sub_node));

                mnew->word = malloc(strlen(word) + 1);
                strcpy(mnew->word, word);
                mnew->file_count = 1;
                mnew->main_link = NULL;
                mnew->main_sub_link = snew;

                /* update sub node */
                strcpy(snew->file_name, f->filename);
                snew->word_count = 1;
                snew->sub_link = NULL;

                /* insert main node into hash table */
                if (arr[idx].h_main_link == NULL)
                    arr[idx].h_main_link = mnew;
                else
                    prev->main_link = mnew;
            }
            /* CASE 2: word already exists */
            else
            {
                Sub_node *stemp = temp->main_sub_link;

                /* check if file entry already exists */
                while (stemp != NULL)
                {
                    if (strcmp(stemp->file_name, f->filename) == 0)
                    {
                        stemp->word_count++;
                        break;
                    }
                    stemp = stemp->sub_link;
                }

                /* if file entry not found, create new sub node */
                if (stemp == NULL)
                {
                    Sub_node *snew = malloc(sizeof(Sub_node));
                    strcpy(snew->file_name, f->filename);
                    snew->word_count = 1;
                    snew->sub_link = temp->main_sub_link;
                    temp->main_sub_link = snew;
                    temp->file_count++;
                }
            }
        }

        /* close file */
        fclose(fp);
        f = f->link;
    }

    /* mark database as created */
    create_flag = 1;

    printf("::CREATION OF DATA BASE IS SUCCESSFULL::\n");
    printf("----------------------------------------\n\n");

    return SUCCESS;
}

//creating hash table for data base
void create_HT(hash_t *arr, int size)
{
    for(int i=0;i<size;i++)
    {
        arr[i].key = i;
        arr[i].h_main_link = NULL;
    }
}

//to find index of that character
int char_idx(char ch)
{
    char c = tolower(ch);
    int index = c - 'a';
    return index;
}