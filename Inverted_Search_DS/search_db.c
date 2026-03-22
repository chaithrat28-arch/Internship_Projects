#include"head.h"

//to search in data base
void search_db(hash_t *arr)
{
    //reading word from user
    char user_word[50];
    printf("Enter word to search in data base: ");
    scanf("%s",user_word);

    int idx = char_idx(user_word[0]);

    Main_node *m_temp = arr[idx].h_main_link;

    while (m_temp != NULL)
    {
        //if word found printing file name and word count
        if (strcmp(m_temp->word, user_word) == 0)
        {
            printf("|-----------------------------------------------|\n");
            printf("|\tFile_Name\t|\tWord_Count\t|\n");
            printf("|-----------------------------------------------|\n");

            Sub_node *stemp = m_temp->main_sub_link;
            while (stemp != NULL)
            {
                printf("|\t%s\t|", stemp->file_name);
                printf("\t %d\t\t|\n", stemp->word_count);
                stemp = stemp->sub_link;
            }

            printf("|-----------------------------------------------|\n\n");
            return;   
        }
        m_temp = m_temp->main_link;   
    }
    
    printf("Entered Word is not present in Data Base..!!\n\n");
    
}