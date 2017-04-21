/*
group-63
Rahul Banerji 2014A7PS082P
Raghav Bhartia 2014A7PS742P
*/
#ifndef LEXER_H
#define LEXER_H
// your code
#include "alldef.h"
#include <stdio.h>
#include <stdlib.h>

int getliner(FILE* fp);

void lexical_error_function(int error,struct token* ptr);

int hashvalue(char* word);

void add_keywords();

void add_keyword(struct node* hashtable[],char* keyword,enum tokentype type);

int find(char* word);

void removeComments(char* testcasefile, char* cleanfile);

struct token* getNextToken();

void string_copy(char* dest,char* src,int begin,int end);

#endif
