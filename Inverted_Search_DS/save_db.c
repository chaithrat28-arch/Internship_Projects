#include"head.h"

//saving database to output file
void save_db(hash_t *arr)
{
    //check if hash table is empty or not
    if (arr == NULL)
    {
        printf("INFO: Database is empty\n");
        return;
    }

    char output_fname[50];
    printf("Enter file name to save data base: ");
    scanf("%s",output_fname);

    //validate file name
    if(strstr(output_fname,".txt") != NULL)
    {
        printf("Validation of File %s is Successfull\n",output_fname);
    }
    else
    {
        printf("INFO: Invalid File %s(must be .txt extension)\n",output_fname);
        return;
    }

    FILE *fp = fopen(output_fname,"w");
    if(fp == NULL)
    {
        printf("File Not found\n");
        fclose(fp);
        return;
    }

    //save data to output file
    //index, word,file count, file name and word count
    for(int i=0;i<26;i++)
    {
        Main_node *temp = arr[i].h_main_link;

        while(temp!=NULL)
        {
            fprintf(fp,"#%d;",i);
        
            fprintf(fp,"%s;",temp->word);
            
            fprintf(fp,"%d;",temp->file_count);

            Sub_node *stemp = temp->main_sub_link;

            while(stemp!=NULL)
            {
                fprintf(fp, "%s;%d;", stemp->file_name, stemp->word_count);

                stemp = stemp->sub_link;
            }
            fprintf(fp,"#\n");

            temp = temp->main_link;
        }
    } 

    fclose(fp);

    printf("::DATA BASE SAVED TO %s SUCCESSFULLY::\n",output_fname);
    printf("---------------------------------------------------\n\n");   
}