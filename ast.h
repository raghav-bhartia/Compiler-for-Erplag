#ifndef ASTDEF_H
#define ASTDEF_H

#include <stdio.h>
#include <stdlib.h>
#include "alldef.h"


void createAST(node_tree* proot);

void copynode(node_tree* root,node_tree* child);

void isnull(node_tree* root);

void printast(node_tree*  PT);

void inorderast(node_tree* root );

void printasttree(node_tree* ptr, FILE* fp );

#endif