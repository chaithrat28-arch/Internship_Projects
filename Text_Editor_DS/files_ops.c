#include"text_editor.h"

void openFile(TextEditor *editor, char *filename)
{
    FILE *fp = fopen(filename,"r");

    if(fp == NULL)
    {
        printf("Error: File not found.\n");
        return;
    }

    char line[200];

    while(fgets(line,sizeof(line),fp))
    {
        line[strcspn(line,"\n")] = '\0';

        Node *newNode = malloc(sizeof(Node));

        strcpy(newNode->line,line);
        newNode->prev = editor->tail;
        newNode->next = NULL;

        if(editor->head == NULL)
        {
            editor->head = newNode;
            editor->tail = newNode;
        }
        else
        {
            editor->tail->next = newNode;
            editor->tail = newNode;
        }
    }

    editor->cursor = editor->tail;

    fclose(fp);

    printf("File opened successfully.\n");
}

void saveFile(TextEditor *editor, char *filename)
{
    FILE *fp = fopen(filename,"w");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Node *temp = editor->head;

    while(temp != NULL)
    {
        fprintf(fp,"%s\n",temp->line);
        temp = temp->next;
    }

    fclose(fp);

    printf("File saved successfully.\n");
}

void closeFile(TextEditor *editor)
{
    Node *temp;

    while(editor->head != NULL)
    {
        temp = editor->head;
        editor->head = editor->head->next;
        free(temp);
    }

    editor->tail = NULL;
    editor->cursor = NULL;
    editor->cursorLine = 0;
    editor->cursorPos = 0;

    printf("Editor cleared.\n");
}