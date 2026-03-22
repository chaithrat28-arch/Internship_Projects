#include"text_editor.h"

void process_commands(TextEditor *editor, char *text)
{
    if(strncmp(text,"insert",6) == 0)
    {
        //insert
        insertText(editor, text);
    }

    else if(strncmp(text,"delete",6) == 0)
    {
        //delete
        int n = atoi(text + 7);
        // printf("%d=>n\n",n);
        deleteText(editor,n);
    }

    else if(strncmp(text,"undo",4) == 0)
    {
        //undo
        undo(editor);
    }

    else if(strncmp(text,"redo",4) == 0)
    {
        //redo
        redo(editor);
    }
    
    else if(strncmp(text,"print",5) == 0)
    {
        //print or display
        displayText(editor);
    }

    else if(strncmp(text,"exit",4) == 0)
    {
        printf("Goodbye! Thank you for using Text Editor.\n");
        printf("Exiting.....\n");
        exit(0);
    }

    else if(strncmp(text,"open",4) == 0)
    {
        //to open file
        char filename[100];
        strcpy(filename,text+5);
        openFile(editor,filename);
    }

    else if(strncmp(text,"save",4) == 0)
    {
        //save file
        char filename[100];
        strcpy(filename,text+5);
        saveFile(editor,filename);
    }

    else if(strncmp(text,"close",5) == 0)
    {
        //close file
        closeFile(editor);
    }

    else
    {
        printf("Invalid Command\n");
    }
}

void insertText(TextEditor *editor, char *text)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    char line[200];
    strcpy(line, text + 7);
    line[strcspn(line,"\n")] = '\0';

    if(strlen(line) == 0)
    {
        printf("Empty text cannot be inserted.\n");
        return;
    }

    //update new node deatils
    strcpy(newNode->line,line);
    newNode->prev = NULL;
    newNode->next = NULL;

    //if list is empty
    if(editor->head == NULL)
    {
        editor->head = newNode;
        editor->tail = newNode;
        editor->cursor = newNode;
        editor->cursorLine = 1;
        editor->cursorPos = strlen(line);

        printf("Text inserted successfully.\n");

        return;
    }

    //insert next node
    newNode->prev = editor->cursor;
    newNode->next = editor->cursor->next;

    //for cursor movement
    if(editor->cursor->next == NULL)
    {
        editor->tail = newNode;    
    }
    else
    {
        editor->cursor->next->prev = newNode;   
    }

    editor->cursor->next = newNode;
    editor->cursor = newNode;

    //updating line and column
    editor->cursorLine++;
    editor->cursorPos = strlen(line);

    pushUndo("insert", line, editor->cursorLine, editor->cursorPos);

    printf("Text inserted successfully.\n");
}

void displayText(TextEditor *editor)
{
    if(editor->head == NULL)
    {
        printf("Text Editor is Empty.\n");
        return;
    }

    Node *temp = editor->head;
    int lineNo = 1;

    printf("---------------------------------------------------------------------\n");

    while(temp != NULL)
    {
        printf("|   Line %d : %s                                            |\n", lineNo, temp->line);

        temp = temp->next;
        lineNo++;
    }

    printf("|   Cursor position: Line %d, Column %d                              |\n",editor->cursorLine,editor->cursorPos);
    printf("---------------------------------------------------------------------\n");
}

void deleteText(TextEditor *editor, int num)
{
    if(editor->cursor == NULL)
    {
        printf("Text is Empty, Nothing to delete.\n");
        return;
    }

    pushUndo("delete", editor->cursor->line, editor->cursorLine, editor->cursorPos);

    int len = strlen(editor->cursor->line);

    if(num > len)
    {
        printf("Error: Cannot delete %d characters. Only %d available.\n", num, len);
        return;
    }

    // delete characters from end of line
    editor->cursor->line[len - num] = '\0';

    editor->cursorPos = strlen(editor->cursor->line);

    printf("Deleted %d characters successfully.\n", num);
}