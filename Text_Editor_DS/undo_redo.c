#include"text_editor.h"
Action undoStack[100];
Action redoStack[100];

int undoTop = -1;
int redoTop = -1;

void pushUndo(char *operation, char *text, int line, int pos)
{
    undoTop++;

    strcpy(undoStack[undoTop].operation, operation);
    strcpy(undoStack[undoTop].text, text);
    undoStack[undoTop].line = line;
    undoStack[undoTop].pos = pos;
}

void undo(TextEditor *editor)
{
    if(undoTop == -1)
    {
        printf("Nothing to undo.\n");
        return;
    }

    Action last = undoStack[undoTop];
    undoTop--;

    // push into redo stack
    redoTop++;
    redoStack[redoTop] = last;

    if(strcmp(last.operation,"insert") == 0)
    {
        //  remove inserted node

        Node *temp = editor->cursor;

        editor->cursor = temp->prev;

        if(temp->prev)
            temp->prev->next = temp->next;

        if(temp->next)
            temp->next->prev = temp->prev;

        free(temp);

        editor->cursorLine--;

        printf("Undo insert successful.\n");
    }

    else if(strcmp(last.operation,"delete") == 0)
    {
        strcpy(editor->cursor->line, last.text);

        printf("Undo delete successful.\n");
    }
}

void redo(TextEditor *editor)
{
    if(redoTop == -1)
    {
        printf("Nothing to redo.\n");
        return;
    }

    Action act = redoStack[redoTop];
    redoTop--;

    undoTop++;
    undoStack[undoTop] = act;

    if(strcmp(act.operation,"insert") == 0)
    {
        printf("Redo insert operation.\n");
    }

    else if(strcmp(act.operation,"delete") == 0)
    {
        editor->cursor->line[0] = '\0';

        printf("Redo delete operation.\n");
    }
}