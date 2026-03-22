/*******************************************************************************************************
NAME : CHAITHRA T
DATE : 01/01/2026 – 04/01/2026
PROJECT TITLE : Lexical Analyzer
DESCRIPTION : This project implements a simple lexical analyzer in C. The program reads a C source file character
by character and identifies different tokens such as keywords, identifiers, operators, special
characters, constants, and string literals. It ignores header files, whitespace, and preprocessor
directives.
PRE-REQUISITE : C programming, file handling, strings, and basic knowledge of tokens.
**********************************************************************************************************/
#include"analyser.h"

int main(int argc, char *argv[])
{
    //check for argument count
    if(argc != 2)
    {
        printf("Invalid Argumens\n");
        printf("USAGE: ./a.out <file_name>\n");
        return 0;
    }

    //open file in read mode
    FILE *fp = fopen(argv[1],"r");

    if(fp == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    char ch;

    //start reading character by character from file
    while( (ch = fgetc(fp)) != EOF )
    {
        //skip header files
        if (ch == '#')
        {
            handle_header(fp);
        }

        //check for string literal 
        if (ch == '"')
        {
            handle_string(fp);
        }

        //skip comments
        if (ch == '/')
        {
            char next = fgetc(fp);

            if(next == '/' || next == '*')
            {
                ungetc(next, fp);
                handle_comment(fp);
                continue;
            }
            else
            {
                ungetc(next, fp);
                handle_operator(fp, ch);
                continue;
            }
        }

        //skip (\n \t ' ') white spaces
        if (isspace(ch))
            continue;

        //chcek for KEYWORD or IDENTIFIER
        else if(isalpha(ch) || ch == '_')
        {
            handle_identifier(fp,ch);
        }

        //check for special character
        else if(ch == '{' || ch == '}' || ch == ')' || ch == '(' || ch == '[' || ch == ']' || ch == ';' || ch ==',')
        {
            printf("SPECIAL CHARACTER : %c\n",ch);
        }

        //check for INTEGER or FLOAT CONSTANTS
        else if(isdigit(ch))
        {
            digits(fp,ch);
        }

        //chcek for OPERATORS
        else if(is_operator(ch))
        {
            handle_operator(fp,ch);
            
        }
    }
    
    fclose(fp);

    return 0;
    
}