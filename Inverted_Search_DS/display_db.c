#include"head.h"

//displaying data base 
void display_db(hash_t *arr)
{
    printf("|----------------------------------------------------------------|\n");
    printf("| Index | Word        | File_Count | File_Name      | Word_Count |\n");
    printf("|----------------------------------------------------------------|\n");

    for (int i = 0; i < 26; i++)
    {
        Main_node *mtemp = arr[i].h_main_link;

        //traverse temp untill not equal to null
        while (mtemp != NULL)
        {
            //print subnode details
            Sub_node *stemp = mtemp->main_sub_link;
            int first = 1;

            while (stemp != NULL)
            {
                if (first)
                {
                    printf("| %-5d | %-11s | %-10d | %-14s | %-10d |\n",
                           i,
                           mtemp->word,
                           mtemp->file_count,
                           stemp->file_name,
                           stemp->word_count);
                    first = 0;
                }
                else
                {
                    printf("|       |             |            | %-14s | %-10d |\n",
                           stemp->file_name,
                           stemp->word_count);
                }
                stemp = stemp->sub_link;
            }

            mtemp = mtemp->main_link;
        }
    }
    printf("|----------------------------------------------------------------|\n\n");   
}