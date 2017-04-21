#ifndef SEMANTIC_H
#define SEMANTOC_H
#include <stdio.h>
#include <stdlib.h>
#include "alldef.h"

void recsemantic(node_tree* astroot);

void semantic(node_tree* astroot,struct symboltablenode* root);

#endif






