#ifndef Validation_h
#define Validation_h
#include "contact.h"
#include <stdio.h>

int name_valid(const char name[]);
int number_valid(const char phnum[]);
int email_valid(const char email[]);

void clearInputBuffer();

#endif