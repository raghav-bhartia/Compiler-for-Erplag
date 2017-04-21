
/*
group-63
Rahul Banerji 2014A7PS082P
Raghav Bhartia 2014A7PS742P
*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "alldef.h"
#include "lexer.h"
#include "parser.h"
#include "symboltable.h"
#include "ast.h"

typedef struct nodetree node_tree;

char moduledecname[100][20];

void recsemantic(node_tree* astroot)
{
    int i,j;
    if(astroot==NULL||astroot->item==epsilon)
        return;
    /*handle declarations*/
    if(astroot->item==moduleDeclarations && astroot->child[0]->item!=epsilon)
    {
        for(i=0;i<astroot->children;i++)
        {
            strcpy(moduledecname[i],astroot->child[i]->child[2]->tokendata->value);
        }

    }
    /*handle declarations end*/
    for(i=0;i<astroot->children;i++)
    {
        recsemantic(astroot->child[i]);
    }

    struct symboltablenode* ptr=NULL;
    struct symboltableentry* ptr2=NULL;
    if(astroot->item==assignmentStmt)
    {
        ptr=astroot->child[0]->symnode;
        while(ptr!=NULL)
        {
            ptr2=findentry(astroot->child[0]->tokendata->value,ptr);
            if(ptr2!=NULL)
                break;
                
            ptr=ptr->parent;
        }
        if(ptr==NULL)
        {
            //printf("Entry is null\n");
            exit(EXIT_FAILURE);
        }
        ptr2->isvisited=true;

    }
    else if(astroot->item==moduleReuseStmt)
    {
        struct symboltablenode* node=astroot->child[6]->child[0]->symnode;
        while(node->parent->parent!=NULL)
        {
            node=node->parent;
        }
        if(node==NULL)
        {
            //printf("IS NULL node\n");
        }
        if(strcmp(astroot->child[3]->tokendata->value,node->name)==0)
        {
            //("%s %s\n",astroot->child[3]->tokendata->value,node->name );
            printf("Error - recursive function not allowed\n");
            exit(EXIT_FAILURE);
        }
        /*handle declarations*/
        int i,j,k;
        char str[20]={0};
        strcpy(str,astroot->child[3]->tokendata->value);
        //printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA %s\n",str);
        for(i=0;moduledecname[i][0]!=0;i++)
        {
            //printf("%s\n",moduledecname[i] );
            if(strcmp(str,moduledecname[i])==0)
                return;
            //printf("1-%s %s %d\n",moduledecname[i],str,strcmp(str,moduledecname) );
        }
        struct symboltablenode* root = node->parent;
        i=0;
        //printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB %s\n",node->name);
        while(root->children[i]!=node)
        {

            //printf("%s\n",root->children[i]->name );
            if(strcmp(str,root->children[i]->name)==0)
                return;
            i++;
        }
        printf("The function is being called before being declared or defined at line %d\n",astroot->child[3]->tokendata->line );
        exit(EXIT_FAILURE);
        /*end handle declarations*/
    }
    else if(astroot->item==condionalStmt)
    {
        if(astroot->child[2]->typeofdata==REAL)
        {
            printf("Error - Switch cannot have real type\n");
            exit(EXIT_FAILURE);
        }
        else if(astroot->child[2]->typeofdata==INTEGER && astroot->child[5]->typeofdata==NUM && astroot->child[6]->children!=1 )
            return;
        else if(astroot->child[2]->typeofdata==BOOLEAN && ( astroot->child[5]->typeofdata==TRUE || astroot->child[5]->typeofdata==FALSE) && astroot->child[6]->children==1 )
            return;
        else
        {
            //("%d %d \n",astroot->child[5]->typeofdata, astroot->child[6]->children);
            if(astroot->child[2]->typeofdata==INTEGER)
                printf("A switch statement with an integer typed identifier associated with it, can have case statement with case keyword followed by an integer only and the case statements must be followed by a default statement\n");
            else if(astroot->child[2]->typeofdata==BOOLEAN)
                printf("A switch statement with a boolean type identifier can have the case statements with labels true and false only. The switch statement then should not have a default statement\n");
            exit(EXIT_FAILURE);
        }
    }

}

void semantic(node_tree* astroot,struct symboltablenode* root)
{
    memset(moduledecname,'\0',sizeof(moduledecname));
    recsemantic(astroot);
    int i,j,k;
    for(i=0;i<root->count;i++)
    {
        struct symboltablenode* entry = root->children[i];
        int i;
        for(i=0;i<entry->outputparam;i++)
        {
            if(entry->output[i].isvisited==false)
            {
                printf("Parameters returned by a function must be assigned a value\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
}

