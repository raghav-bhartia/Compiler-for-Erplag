/*
group-63
Rahul Banerji 2014A7PS082P
Raghav Bhartia 2014A7PS742P
*/

#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include "alldef.h"

void push( node_tree* item);

node_tree* pop();

node_tree* create_node_tree(int item);

void printParseTree(node_tree*  PT, char *outfile);

void inorder(node_tree* ptr,FILE* fp);

void getgrammar();

int isterm(int i);

int isepsilonthereg(int x);

void ffirst(int x);

int isepsilontherefst(int x);

int present (int item,int j);

void follow_compute();

void ComputeFirstAndFollowSets();

void createparsetable();

node_tree*  parseInputSourceCode(char *testcaseFile);

#endif

