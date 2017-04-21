/*
group-63
Rahul Banerji 2014A7PS082P
Raghav Bhartia 2014A7PS742P
*/

#ifndef LEXERDEF_H
#define LEXERDEF_H

#include <stdio.h>
#include <stdlib.h>


enum errors{
    ERROR_1,ERROR_2,ERROR_3,ERROR_4,ERROR_5
};


enum tokentype{
program,moduleDeclarations,moduleDeclaration,otherModules,driverModule,module,ret,input_plist,N1,output_plist,N2,dataType,type,moduleDef,statements,statement,ioStmt,var,whichId,simpleStmt,assignmentStmt,whichStmt,
lvalueIDStmt,lvalueARRStmt,index1,moduleReuseStmt,optional,idlist,N3,expression,arithmeticOrBooleanExpr,N7,AnyTerm,N8,arithmeticExpr,N4,term,N5,factor,op1,op2,logicalOp,relationalOp,declareStmt,condionalStmt,caseStmts
,N9,value,default1,iterativeStmt,range,INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,
WHILE,PLUS,MINUS,MUL,DIV,LT,LE,GE,GT,EQ,NE,DEF,ENDDEF,COLON,RANGEOP,SEMICOL,COMMA,ASSIGNOP,SQBO,SQBC,BO,BC,COMMENTMARK,NUM,RNUM,ERR,ID,DRIVERDEF,DRIVERENDDEF,dollar,epsilon
};


struct node
{
 char string[11];
 enum tokentype type;
 struct node* next;

};


struct token
{

    int line;
    enum tokentype type;
    char* value;
};


struct nodetree
{
    int item;
    struct nodetree* child[200];
    int children;
    struct nodetree* parent;
    struct token* tokendata;
    int typeofdata;
    struct symboltablenode * symnode;
    int a_offset;
    int b_offset;
    int tag;

} ;

struct ptnode
{
    int rule;
    int pos;
};

struct symboltableentry
{
	int linenumber;
	enum tokentype type;
	char value[25];
	int offset;
	int width;
	struct symboltableentry* next;
	bool isvisited;     //for parameters being returned by a function must be assigned a value
};

struct symboltablenode
{
	struct symboltableentry arrayofentries[100];
	struct symboltableentry* hashtable[20];
	int entries;
	int count;
	struct symboltablenode* children[20];
	struct symboltablenode* parent;
	char name[25];
	bool isFnode;
	int inputparam;
	int outputparam;
	int traversed;
	int startline;
	int endline;
	int nestinglevel;
	struct symboltableentry input[15];
	struct symboltableentry output[15];
};




typedef struct nodetree node_tree;
typedef struct token* typedeftoken;
typedef struct ptnode* pnode;

int line_number;
int current_offset;
int error_encountered;
 
char buf1[1000];
typedeftoken arrtoken[10000];
struct node* hashtable[191]; 
int i;
int follow[200][200];
int indexes[200];
int s;
node_tree* stack[1000];
int stack_index;
int baccha_number;
int fst[120][400];
int g[120][400];
pnode ptable[150][150];
int count_tokens;
int numofastnodes;
int numofptreenodes;

#endif
