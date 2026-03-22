#include"head.h"

int update_flag;

//Updating database to output file
int update_db(hash_t *arr)
{
    /* update should work only once */
    if (update_flag == 1)
    {
        printf("INFO: Update already done once\n");
        return 3;
    }

    /* if create already done, update not allowed */
    if (create_flag == 1)
    {
        printf("INFO: Database is already updated\n");
        return 3;
    }

    update_flag = 0;

    char db_fname[50];
    printf("Enter database file name to update: ");
    scanf("%s", db_fname);

    FILE *fp = fopen(db_fname, "r");
    if (fp == NULL)
    {
        printf("ERROR: Unable to open file\n");
        return FAILURE;
    }

    char ch;
    fscanf(fp, "%c", &ch);
    if (ch != '#')
    {
        printf("ERROR: Invalid database file\n");
        fclose(fp);
        return FAILURE;
    }

    rewind(fp);

    int index, file_count, word_count;
    char word[50], fname[20];

    //reading index, word and filecount
    while (fscanf(fp, "#%d;%[^;];%d;", &index, word, &file_count) == 3)
    {
        //creating main node
        Main_node *mnew = malloc(sizeof(Main_node));
        mnew->word = malloc(strlen(word) + 1);
        strcpy(mnew->word, word);
        mnew->file_count = file_count;
        mnew->main_link = NULL;
        mnew->main_sub_link = NULL;

        if (arr[index].h_main_link == NULL)
        {
            arr[index].h_main_link = mnew;
        }
        else
        {
            Main_node *temp = arr[index].h_main_link;
            while (temp->main_link != NULL)
                temp = temp->main_link;
            temp->main_link = mnew;
        }

        //creating subnode, and accordingly reading data from saved file
        for (int i = 0; i < file_count; i++)
        {
            fscanf(fp, "%[^;];%d;", fname, &word_count);

            Sub_node *snew = malloc(sizeof(Sub_node));
            strcpy(snew->file_name, fname);
            snew->word_count = word_count;
            snew->sub_link = NULL;

            if (mnew->main_sub_link == NULL)
                mnew->main_sub_link = snew;
            else
            {
                Sub_node *stemp = mnew->main_sub_link;
                while (stemp->sub_link != NULL)
                    stemp = stemp->sub_link;
                stemp->sub_link = snew;
            }
        }

        fscanf(fp, "#\n");
    }

    fclose(fp);
    //updatig flag
    update_flag = 1;

    printf("::UPDATE OF DATA BASE IS SUCCESSFULL::\n");
    printf("--------------------------------------\n\n");

    return SUCCESS;
}
