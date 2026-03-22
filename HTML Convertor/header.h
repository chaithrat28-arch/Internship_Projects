#ifndef SRC_TO_HTML
#define SRC_TO_HTML

#include<stdio.h>
#include <string.h>
#include <ctype.h>

enum ret_value
{
    KEYWORD, //blue
    IDENTIFIER, //white
    VALUE, //green
    STRING_LITERAL, //red
    COMMENTS, //green
    OPERATOR, //white
    SPECIAL_CHARACTER, //yellow
    PRE_PROCESSORS, //purple
};

int is_keyword(char *buf);

int is_operator(char ch);

void html_begin(FILE *html_file);

void html_end(FILE *html_file);

void html_body(FILE *html_file,char *word, int key);
#endif
