
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

char tokens5[115][100]={
"program","moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1","output_plist","N2","dataType","type","moduleDef","statements","statement","ioStmt","var","whichId","simpleStmt","assignmentStmt","whichStmt",
"lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional","idlist","N3","expression","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term","N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt",
"caseStmts","N9","value","default1","iterativeStmt","range","INTEGER","REAL","BOOLEAN","OF",
"ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR","FOR",
"IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF","ENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK","NUM","RNUM","ERR",
"ID","DRIVERDEF","DRIVERENDDEF","dollar","epsilon"};


typedef struct nodetree node_tree;

/********check find in symbol table***************/

void typecheck(struct symboltablenode* symroot, node_tree* astroot)

{
	if(astroot!=NULL)
	//printf("%s\n",tokens5[astroot->item]);
	//("1\n");

    if(astroot==NULL||astroot->item==epsilon||astroot->item==moduleDeclaration)
        return;
    int i,j,k;
    if(astroot->item==module)
    {
    	//("2\n");
        typecheck(symroot,astroot->child[11]);

    }
    else if(astroot->item==expression)
    {
    	//("16\n");
    	if(astroot->children==1)
    	{
    		typecheck(symroot,astroot->child[0]);
        	astroot->typeofdata=astroot->child[0]->typeofdata;
    	}
        else if(astroot->children==4)
        {
        	typecheck(symroot,astroot->child[2]);
        	astroot->typeofdata=astroot->child[2]->typeofdata;
        }
        else
        {
        	printf("ERROR expression\n");
        	exit(EXIT_FAILURE);
        }
    }
    else if(astroot->item==moduleReuseStmt)
    {
    	//("3\n");
        struct symboltablenode* temp=symroot;
        typecheck(symroot,astroot->child[0]);
        typecheck(symroot,astroot->child[6]);
        while(symroot->parent!=NULL)
        {
            symroot=symroot->parent;
        }
        //("Symroot data - count %d entry %d\n",symroot->count,symroot->entries );
        for(i=0;i<symroot->count;i++)
        {
        	//printf("%s compare %s\n", symroot->children[i]->name,astroot->child[3]->tokendata->value);
            if(strcmp(symroot->children[i]->name,astroot->child[3]->tokendata->value)==0)
            {
                astroot->child[3]->symnode=symroot->children[i];
                astroot->child[3]->typeofdata=-2;
                int i;
                if(astroot->child[0]->child[0]->item==epsilon && astroot->child[3]->symnode->outputparam==0)
                    return;
                if(astroot->child[0]->child[(astroot->child[0]->children)-1]->item==epsilon)
                    astroot->child[0]->children-=1;
                if(astroot->child[0]->children!=astroot->child[3]->symnode->outputparam)
                {
                    printf("number of parameters dont match in output %d %d %s\n",astroot->child[0]->children,astroot->child[3]->symnode->outputparam,tokens5[astroot->child[0]->child[1]->item]);
                    exit(EXIT_FAILURE);
                }
                for(i=0;i<astroot->child[0]->children;i++)
                {

                    if(astroot->child[0]->child[i]->typeofdata!= astroot->child[3]->symnode->output[i].type)
                    {
                        printf("data types dont match in function in output\n");
                        exit(EXIT_FAILURE);
                    }
                }

                if(astroot->child[6]->child[(astroot->child[6]->children)-1]->item==epsilon)
                    astroot->child[6]->children-=1;
                if(astroot->child[6]->children!=astroot->child[3]->symnode->inputparam)
                {
                    printf("number of parameters dont match in input");
                    exit(EXIT_FAILURE);
                }
                for(i=0;i<astroot->child[6]->children;i++)
                {

                    if(astroot->child[6]->child[i]->typeofdata!= astroot->child[3]->symnode->input[i].type)
                    {
                        printf("data types dont match in function input\n");
                        exit(EXIT_FAILURE);
                    }
                }
                return;
                
            }
        }
        symroot=temp;
        astroot->child[3]->typeofdata=-2;
        printf("Error in module name call\n");
        exit(EXIT_FAILURE);


    }
    else if(astroot->item==moduleDef)
    {
    	//("4\n");
        symroot=symroot->children[(symroot->traversed)++];
        for(i=0;i<astroot->children;i++)
        {
            typecheck(symroot,astroot->child[i]);
        }
        symroot=symroot->parent;
    }
    else if(astroot->item==condionalStmt)
    {
    	//("5\n");
        typecheck(symroot,astroot->child[2]);
        symroot=symroot->children[(symroot->traversed)++];
        typecheck(symroot,astroot->child[5]);
        typecheck(symroot,astroot->child[6]);
        symroot=symroot->parent;
    }
    else if(astroot->item==iterativeStmt)
    {
    	//("6\n");
        typecheck(symroot,astroot->child[2]);
        symroot=symroot->children[(symroot->traversed)++];
        if(astroot->child[0]->item==FOR)
        {
            typecheck(symroot,astroot->child[7]);
            struct symboltableentry* temp = findentry(astroot->child[2]->tokendata->value,symroot);
            if(temp!=NULL)
            {
                printf("Error - Redeclaration of variable in for loop that is iterating over the range at line %d\n",temp->linenumber);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            typecheck(symroot,astroot->child[5]);
            if(astroot->child[2]->typeofdata!=BOOLEAN)
            {
                printf("Error - While can only have boolean type in loop condition\n");
                exit(EXIT_FAILURE);
            }
        }
        symroot=symroot->parent;
    }
    else
    {
    	//("7\n");
            for(i=0;i<astroot->children;i++)
            {
                typecheck(symroot,astroot->child[i]);
            }
    }
    if(astroot->item==PLUS||astroot->item==MINUS||astroot->item==MUL||astroot->item==DIV)
    {
    	//("8\n");
        if(astroot->child[0]->typeofdata!=astroot->child[1]->typeofdata)
        {
             printf("8a error in type left=%d and right=%d at symbol %s at line %d\n",astroot->child[0]->typeofdata,astroot->child[1]->typeofdata,tokens5[astroot->item],astroot->tokendata->line);
            exit(EXIT_FAILURE);
        }
        else if(astroot->child[0]->typeofdata==INTEGER||astroot->child[0]->typeofdata==REAL)
        {
            astroot->typeofdata=astroot->child[0]->typeofdata;
        }
        else
        {
            printf("8b error in type left=%d and right=%d at symbol %s at line %d\n",astroot->child[0]->typeofdata,astroot->child[1]->typeofdata,tokens5[astroot->item],astroot->tokendata->line);
            exit(EXIT_FAILURE);
        }
    }
    else if(astroot->item==GE||astroot->item==GT||astroot->item==LE||astroot->item==LT||astroot->item==EQ||astroot->item==NE)
    {
    	//("9\n");
        if(astroot->child[0]->typeofdata!=astroot->child[1]->typeofdata)
        {
            printf("error in type left=%d and right=%d\n at line %d",astroot->child[0]->typeofdata,astroot->child[1]->typeofdata,astroot->tokendata->line);
            exit(EXIT_FAILURE);
        }
        else if(astroot->child[0]->typeofdata==INTEGER||astroot->child[0]->typeofdata==REAL)
        {
            astroot->typeofdata=BOOLEAN;
        }
        else
        {
            printf("error in type left=%d and right=%d at line %d\n",astroot->child[0]->typeofdata,astroot->child[1]->typeofdata,astroot->tokendata->line);
            exit(EXIT_FAILURE);
        }
    }
    else if(astroot->item==AND||astroot->item==OR)
    {
    	//("10\n");
        if(astroot->child[0]->typeofdata!=astroot->child[1]->typeofdata)
        {
            printf("error in type left=%d and right=%d at line %d\n",astroot->child[0]->typeofdata,astroot->child[1]->typeofdata,astroot->tokendata->line);
            exit(EXIT_FAILURE);
        }
        else if(astroot->child[0]->typeofdata==BOOLEAN)
        {
            astroot->typeofdata=BOOLEAN;

        }
        else
        {
            printf("error in type left=%s and right=%d at line %d\n",tokens5[astroot->child[0]->typeofdata],astroot->child[1]->typeofdata,astroot->tokendata->line);
            exit(1);
        }
    }
    else if(astroot->item==TRUE||astroot->item==FALSE)
    {
    	//("11\n");
        astroot->typeofdata=BOOLEAN;
    }
    else if(astroot->item==NUM||astroot->item==INTEGER)
    {
    	//("12\n");
        astroot->typeofdata=INTEGER;
    }
    else if(astroot->item==RNUM||astroot->item==REAL)
    {
    	//("13\n");
        astroot->typeofdata=REAL;
    }
    else if(astroot->item==ID)
    {
    	//("14\n");
        struct symboltablenode* temp=symroot;
        while(symroot!=NULL)
        {
            struct symboltableentry* entry=findentry(astroot->tokendata->value,symroot);
            if(entry!=NULL)
            {
                astroot->typeofdata=entry->type;
                symroot=temp;
                break;
            }
            symroot=symroot->parent;

        }
        if(symroot==NULL)
        {
            
            printf("error undeclared variable %s",astroot->tokendata->value);
            symroot=temp;
            exit(EXIT_FAILURE);
        }
        astroot->symnode=symroot;
    }
    else if(astroot->item==lvalueIDStmt)
    {
    	//("15\n");
        astroot->typeofdata=astroot->child[1]->typeofdata;
    }
     else if(astroot->item==lvalueARRStmt)
    {
    	//("90\n");
        astroot->typeofdata=astroot->child[4]->typeofdata;
    }
    else if(astroot->item==var)
    {
    	//("15\n");
        astroot->typeofdata=astroot->child[0]->typeofdata;
    }
    else if(astroot->item==assignmentStmt)
    {
    	
        if(astroot->child[0]->typeofdata!=astroot->child[1]->typeofdata)
        {
            //("17\n");
            printf("error in type left=%d and right=%d at line %d\n",astroot->child[0]->typeofdata,astroot->child[1]->typeofdata,astroot->child[0]->tokendata->line);
            exit(EXIT_FAILURE);
        }
    }
}
