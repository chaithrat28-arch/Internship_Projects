#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#define MAX_ACTIONS 100

/* Node for storing text line */
typedef struct Node
{
    char line[200];
    struct Node *prev;
    struct Node *next;
} Node;

/* Editor structure */
typedef struct
{
    Node *head; //points to first line
    Node *tail; //points to last line
    Node *cursor; //points to current line
    int cursorLine; //line number of cursor
    int cursorPos; //column position cursor
} TextEditor;

/* Stack structure for undo/redo */
typedef struct
{
    char operation[20]; //opn. type "insert" or "delete"
    char text[200]; //test
    int line; //line number
    int pos; //column position
} Action;

/* stack declarations */
extern Action undoStack[MAX_ACTIONS];
extern Action redoStack[MAX_ACTIONS];

extern int undoTop;
extern int redoTop;

/* Function prototypes */

void process_commands(TextEditor *editor, char *text);

void insertText(TextEditor *editor, char *text);
void deleteText(TextEditor *editor, int n);

void redo(TextEditor *editor);
void undo(TextEditor *editor);

void displayText(TextEditor *editor);
void pushUndo(char *operation, char *text, int line, int pos);


void openFile(TextEditor *editor, char *filename);
void saveFile(TextEditor *editor, char *filename);
void closeFile(TextEditor *editor);

#endif