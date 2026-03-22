#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include <ctype.h>
#include <string.h>

//chcek for KEYWORD or IDENTIFIER
int is_keyword(char *);

//chcek for OPERATORS
int is_operator(char);

//to handler header
void handle_header(FILE *fp);

//to handle strings
void handle_string(FILE *fp);

//to handle comments
void handle_comment(FILE *fp);

//to handle identifier and keywords
void handle_identifier(FILE *fp,char ch);

//to check for INTEGER or FLOAT CONSTANTS
void digits(FILE *fp,char ch);

//chcek for OPERATORS
void handle_operator(FILE *fp,char ch);
#endif