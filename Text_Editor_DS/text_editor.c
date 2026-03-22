/*******************************************************************************************************
NAME            : CHAITHRA T
DATE            : 10-Mar-2026 to 12-Mar-2026
PROJECT TITLE   : Console Based Text Editor Using Data Structures in C
DESCRIPTION     : The system allows the user to insert text, delete text, move the cursor, search text,
                  and save or open files using a command-line interface.
PRE-REQUISITE   : Understanding of linked lists, dynamic memory allocation, and basic Knowledge of Data 
                  Structure.
*******************************************************************************************************/
#include"text_editor.h"

int main()
{
    TextEditor editor;

    editor.head = NULL;
    editor.tail = NULL;
    editor.cursor = NULL;
    editor.cursorLine = 0;
    editor.cursorPos = 0;

    char choice[200];

    while(1)
    {
        printf("\n=====================================================\n");
        printf("                  TEXT EDITOR\n");
        printf("=====================================================\n");
        printf("Text Editor Commands:\n");
        printf("1.insert <text>\n");
        printf("2.delete <num_chars>\n");
        printf("3.undo\n");
        printf("4.redo\n");
        printf("5.print\n");
        printf("6.open <file_name>\n");
        printf("7.save <file_name>\n");
        printf("8.close\n");
        // printf("9.replace <old_filename> <new_filename>\n");
        printf("9.exit\n");
        printf("=====================================================\n");

        printf("\nEnter command: ");
        fgets(choice,200,stdin);
        choice[strcspn(choice,"\n")] = '\0'; //remove \n

        process_commands(&editor,choice);

    }
    return 0;
}