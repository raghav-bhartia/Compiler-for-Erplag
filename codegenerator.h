#ifndef CODEGENERATORDEF_H
#define CODEGENERATORDEF_H

#include <stdio.h>
#include <stdlib.h>
#include "alldef.h"

void putvarinreg(char* reg,node_tree* variable);
void putreginmem(node_tree* variable,char* reg);
void codegen(node_tree* astroot);

#endif