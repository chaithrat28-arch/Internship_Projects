/*******************************************************************************************************
NAME : CHAITHRA T
DATE : FROM 5/12/2025 TO 15/12/2025
PROJECT TITLE : INVERTED SEACRH
DESCRIPTION : The purpose of storing an index is to optimize speed and performance in finding relevant 
documents for a search query. Without an index, the search engine would scan every document in the corpus, 
which would require considerable time and computing power.
PRE-REQUISITE : Hashing and Single linked list.
**********************************************************************************************************/
#include"head.h"

int main(int argc, char *argv[])
{
    //validate number of command line arguments
    if (argc == 1)
    {
        printf("Usage: ./a.out <file01_name.txt> <file02_name.txt> <file03_name.txt> ....\n");
        return FAILURE;
    }

    //checking for .txt extension and if any duplicate file exist
    for(int i=1;i<argc;i++)
    {
        if(strstr(argv[i],".txt") == NULL)
        {
            printf("ERROR: Invalid extension,must be (.txt)!!!\n");
            return 0;
        }
            
        for(int j=i+1;j<argc;j++)
        {
            if(strcmp(argv[i],argv[j]) == 0)
            {
                printf("ERROR: Duplicate files found for %s !!!\n",argv[i]); 
                return 0;
            }
        }
        
    }

    //creating linked list fir storing file names
    file_list *f_head = NULL;

    for(int i=1;i<argc;i++)
    {
        char *fname = argv[i];

        int res = file_name_validation(fname,&f_head);
        if(res == EMPTY)
        {
            printf("INFO: File %s is Empty\n",fname);
            return FAILURE;
        }
        else if(res == SUCCESS)
        {
            printf("Validation of File %s is Successfull\n",fname);
        }
        else
        {
            printf("ERROR: Failed to insert files into linked list\n");
        }
    }
    printf("-------------------------------------------------------\n");

    int op=0;

   //creating hash table for data base
    hash_t arr[26] = {0};
    create_HT(arr, 26);

    while(op != 6)
    {
        printf("-:INVERTED SEARCH MENUE:-\n");
        printf("1.Create Data Base\n");
        printf("2.Search Data Base\n");
        printf("3.Display Data Base\n");
        printf("4.Update Data Base\n");
        printf("5.Save data base\n");
        printf("6.EXIT\n");
        printf("Enter Option:");
        scanf("%d",&op);

        switch (op)
        {
            case 1:
            //creating database
                int res = create_db(arr,f_head);
                if(res == 3)
                {
                    printf("ERROR: Only One time u can Create Data Base..!!\n");
                    printf("Exiting from Program...\n");
                    return 0;
                }
                break;
        
            case 2:
            //to search in data base
                search_db(arr);
                break;

            case 3:
            //displaying data base 
                display_db(arr);
                break;

            case 4:
            //Updating database to output file
            int res1 = update_db(arr);
                if(res1 == FAILURE)
                {
                    printf("ERROR: Failed to Update data base..!!!\n");
                }
                else if(res1 == 3)
                {
                    printf("ERROR: Only One time u can Update Data Base..!!\n\n");
                    printf("Exiting from Program...\n");
                    return 0;
                }
                
                break;

            case 5:
            //saving database to output file
                save_db(arr);
                break;

            case 6:
                printf("Exiting....\n");
                exit(0);

            default:
                printf("Invalid input\n");
                break;
        }
    }

}