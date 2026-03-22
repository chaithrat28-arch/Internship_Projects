#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

extern int update_flag;
extern int create_flag;

//structure for holding file name
typedef struct node
{
    char filename[20];
    struct node *link;
}file_list;

//structure for holding Sub node information
typedef struct sub_node
{
    char file_name[20];
    int word_count;
    struct sub_node *sub_link;
}Sub_node;

//structure for holding Main node information
typedef struct main_node
{
    char *word;
    int file_count;
    struct main_node *main_link;
    struct sub_node *main_sub_link;
}Main_node;

//structure for hash table
typedef struct hnode
{
    int key;
    struct main_node *h_main_link;
}hash_t;

//enums for return value from function
typedef enum 
{
    SUCCESS,FAILURE,EMPTY
}Status;

//fil name validation
int file_name_validation(char *,file_list **);

//to check file is empty or not
int is_empty_file(char *);

//to check file reached end of the file
int is_eof(FILE *);

//inserting file name to linked list
int insert_fname(file_list **,char *);

//creating database
int create_db(hash_t *,file_list *);

//creating hash table for data base
void create_HT(hash_t *, int );

//displaying data base 
void display_db(hash_t *);

//to search in data base
void search_db(hash_t *);

//saving database to output file
void save_db(hash_t *);

//Updating database to output file
int update_db(hash_t *);

//to find index of that character
int char_idx(char);

#endif