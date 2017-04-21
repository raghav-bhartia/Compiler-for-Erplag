/*
group-63
Rahul Banerji 2014A7PS082P
Raghav Bhartia 2014A7PS742P
*/

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <stdio.h>
#include <stdlib.h>
#include "alldef.h"

struct symboltablenode* createsymboltablenode();

void inserttableentry(struct symboltablenode* tnode,struct symboltableentry tentry);

struct symboltablenode* createsymboltable();

void recst(int *i,struct symboltablenode* curr);

void printsymtable(struct symboltablenode* root);

void printentry(struct symboltableentry* node);

int hashvalueentry(char* word);

void addentry(struct symboltableentry* hashtable[],struct token* tokennode,int type,int offset,int width);

struct symboltableentry* findentry(char* word,struct symboltablenode* node);

struct symboltableentry* findentrytillparent(char* word,struct symboltablenode* node);

#endif

