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
#include <stdio.h>
#include <stdbool.h>
#include "alldef.h"
#include "symboltable.h"

int offset;

char tokens3[115][100]={
"program","moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1","output_plist","N2","dataType","type","moduleDef","statements","statement","ioStmt","var","whichId","simpleStmt","assignmentStmt","whichStmt",
"lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional","idlist","N3","expression","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term","N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt",
"caseStmts","N9","value","default1","iterativeStmt","range","INTEGER","REAL","BOOLEAN","OF",
"ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR","FOR",
"IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF","ENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK","NUM","RNUM","ERR",
"ID","DRIVERDEF","DRIVERENDDEF","dollar","epsilon"};


struct symboltablenode* createsymboltablenode()
{
	struct symboltablenode* ptr= (struct symboltablenode*) malloc(sizeof (struct symboltablenode));
	ptr->count=0;
	ptr->entries=0;
	ptr->inputparam=0;
	ptr->outputparam=0;
	ptr->isFnode=FALSE;
    ptr->traversed=0;
    ptr->parent=NULL;
	memset(ptr->hashtable,NULL,sizeof(ptr->hashtable));
	int i;
	for(i=0;i<(sizeof(ptr->input)/sizeof(ptr->input[0])) ; i++ )
	{
		ptr->input[i].isvisited=false;
	}
	for(i=0;i<(sizeof(ptr->output)/sizeof(ptr->output[0])) ; i++ )
	{
		ptr->output[i].isvisited=false;
	}
	return ptr;
}

void inserttableentry(struct symboltablenode* tnode,struct symboltableentry tentry)
{
    //tnode->arrayofentries[tnode->count++] = tentry;
}


struct symboltablenode* createsymboltable()
{
        int i,j,k;
        struct symboltablenode* root=createsymboltablenode();
        root->nestinglevel=0;
        int numofdef=0;
        //printf("%d\n",count_tokens );
        for(i=0;i<count_tokens;i++)
        {
            if(arrtoken[i]->type==DEF)
              {
              	//printf("seen def at %d\n",i);
                root->children[numofdef]=(struct symboltablenode*) malloc(sizeof (struct symboltablenode));
                root->children[numofdef]->isFnode=TRUE;
                root->children[numofdef]->parent=root;
                numofdef++;
              }
            else if(arrtoken[i]->type==DRIVERDEF)
            {
            	//printf("seen driverdef at %d\n",i );
               root->children[numofdef]=(struct symboltablenode*) malloc(sizeof (struct symboltablenode));
                root->children[numofdef]->isFnode=TRUE;
                root->children[numofdef]->parent=root;
                strcpy(root->children[numofdef]->name,"driver");
                numofdef++;
            }
        }
       // printf("2\n");
        root->parent=NULL;
        root->count=numofdef;
        numofdef=0;
        for(i=0;i<count_tokens;i++)
        {
        	//printf("%d\n",i );
            if(arrtoken[i]->type==DECLARE && arrtoken[i+1]->type==MODULE)
            {
                i++;
                continue;
            }
            if(arrtoken[i]->type==DEF)
            {
                current_offset=0;
                strcpy(root->children[numofdef]->name,arrtoken[i+2]->value);
                int a;
                for(a=0;a<numofdef;a++)
                {
                	if(strcmp(root->children[numofdef]->name,root->children[a]->name)==0)
                	{
                		printf("Error - Multiple defination of same function is not allowed\n");
                		exit(EXIT_FAILURE);
                	}
                }
                i+=4;
                //printf("%d\n",i );
                if(arrtoken[i]->type==TAKES)
                {
                    i+=3;
                    //printf("%d\n",i );
                    while(arrtoken[i]->type!=SEMICOL)
                    {
                        if(arrtoken[i+2]->type!=ARRAY)
                        {
                            struct symboltableentry entry;
                            entry.linenumber=arrtoken[i]->line;
                            entry.type=arrtoken[i+2]->type;
                            strcpy(entry.value,arrtoken[i]->value);
                            if(entry.type==INTEGER)
                                offset=2;
                            if(entry.type==REAL)
                                offset=4;
                            if(entry.type==BOOLEAN)
                                offset=1;
                            entry.width=offset;
                             entry.offset=current_offset;
                            current_offset+=offset;
                            root->children[numofdef]->input[(root->children[numofdef]->inputparam)] = entry;
                            (root->children[numofdef]->inputparam)+=1;
                            i+=4;
                        }
                        else if(arrtoken[i+2]->type==ARRAY)
                        {
                            struct symboltableentry entry;
                            entry.linenumber=arrtoken[i]->line;
                            entry.type=arrtoken[i+9]->type;
                            strcpy(entry.value,arrtoken[i]->value);
                           offset=atoi(arrtoken[i+6]->value);
                            if(entry.type==INTEGER)
                                offset*=2;
                            if(entry.type==REAL)
                                offset*=4;
                            if(entry.type==BOOLEAN)
                                offset*=1;
                            entry.width=offset;
                            entry.offset=current_offset;
                            current_offset+=offset;
                            root->children[numofdef]->input[(root->children[numofdef]->inputparam)] = entry;
                             (root->children[numofdef]->inputparam)+=1;
                            i+=11;
                        }
                    }
                    i++;
                }
                if(arrtoken[i]->type==RETURNS)
                {
                    i+=2;
                    while(arrtoken[i]->type!=SEMICOL)
                    {
                        if(arrtoken[i+2]->type!=ARRAY)
                        {
                            struct symboltableentry entry;
                          //  entry.linenumber=arrtoken[i]->linenumber;
                            entry.type=arrtoken[i+2]->type;
                             if(entry.type==INTEGER)
                                offset=2;
                            if(entry.type==REAL)
                                offset=4;
                            if(entry.type==BOOLEAN)
                                offset=1;
                            strcpy(entry.value,arrtoken[i]->value);
                            entry.width=offset;
                            entry.offset=current_offset;
                            current_offset+=offset;
                            strcpy(entry.value,arrtoken[i]->value);
                            
                            root->children[numofdef]->output[root->children[numofdef]->outputparam] = entry;
                            i+=4;
                             (root->children[numofdef]->outputparam)+=1;
                            continue;
                        }
                        else if(arrtoken[i+2]->type==ARRAY)
                        {
                            struct symboltableentry entry;
                           // entry.linenumber=arrtoken[i]->linenumber;
                            entry.type=arrtoken[i+9]->type;
                            strcpy(entry.value,arrtoken[i]->value);
                            offset=atoi(arrtoken[i+6]->value);
                            
                             if(entry.type==INTEGER)
                                offset*=2;
                            if(entry.type==REAL)
                                offset*=4;
                            if(entry.type==BOOLEAN)
                                offset*=1;
                            strcpy(entry.value,arrtoken[i]->value);
                            entry.offset=current_offset;
                            entry.width=offset;
                            current_offset+=offset;
                            root->children[numofdef]->output[root->children[numofdef]->outputparam] = entry;
                             (root->children[numofdef]->outputparam)+=1;
                            i+=11;
                        }
                    }
                    i++;
                }
                i++;
                /**Call rec func**/
                recst(&i,root->children[numofdef]);
                //printf("EXIT REC FINAL 2\n");
                i--;
                numofdef++;
            }
            if(arrtoken[i]->type==DRIVERDEF)
            {
                i+=5;
                /**Call rec func**/
                //printf("%d\n",i );
                current_offset=0;
                recst(&i,root->children[numofdef]);
                numofdef++;
                //printf("EXIT REC FINAL\n");
                i--;
            }
        }
       // printf("exit for return root\n");

   return root;
}


void recst(int *i,struct symboltablenode* curr)
{
	//printf("INRECURSION\n");
	curr->nestinglevel=(curr->parent->nestinglevel)+1;
    curr->startline=arrtoken[(*i)-1]->line;

	//printf("First in rec-%s\n",tokens3[arrtoken[*i]->type] );
    struct symboltablenode* temp=curr;
    while(arrtoken[*i]->type!=END)
    {
    	if(arrtoken[*i]->type==ID && arrtoken[(*i)-1]->type!=MODULE)
    	{
    		struct symboltableentry* entry=NULL;
    		while(curr!=NULL)
    		{
    			entry=findentry(arrtoken[*i]->value,curr);
    			if(entry!=NULL)
    			{
    				break;
    			}
    			curr=curr->parent;	
    		}
    		if(entry==NULL)
    		{
    			printf("ERROR- %s undeclared at line %d\n",arrtoken[*i]->value,arrtoken[*i]->line );
    			exit(EXIT_FAILURE);
    		}
    		
    	}
        curr=temp;
    	//printf("IN END LOOP\n");
    	//printf("%d\n", *i);
        if(arrtoken[*i]->type==START)
        {	//printf("START-%d\n",*i );
            curr->children[curr->count]=createsymboltablenode();
            *i+=1;
            curr->children[curr->count]->parent=curr;
            recst(i,curr->children[curr->count]);
            curr->count++;
            continue;
        }
        else if(arrtoken[*i]->type==DECLARE)
        {
        	//printf("1\n");
        	//struct symboltableentry* ent=(struct symboltableentry*) malloc(sizeof (struct symboltableentry));
            int j=0;*i+=1;
            int oldi=*i;
            int type,offset;
            while(arrtoken[*i]->type!=COLON)
            {
                *i+=1;
            }
            *i+=1;
           // printf("2\n");
            if(arrtoken[*i]->type==ARRAY)
            {	type=arrtoken[*i+7]->type;
            	offset=atoi(arrtoken[*i+4]->value);
                if(type==INTEGER)
                    offset*=2;
                if(type==REAL)
                    offset*=4;
                if(type==BOOLEAN)
                    offset*=1;
            	*i=oldi;

            	while(arrtoken[*i]->type!=SEMICOL)
            	{
	            	if(arrtoken[*i]->type==ID)
	            	{

	            		struct symboltableentry* entry=findentry(arrtoken[*i]->value,curr);
	            		if(entry!=NULL)
	            		{
	            			printf("Error: Double declaration at line %d\n",entry->linenumber);
	            			exit(EXIT_FAILURE);
	            		}
		                addentry(curr->hashtable,arrtoken[*i],type,current_offset,offset);
                        current_offset+=offset;


	            	}
            	*i+=1;
            	}
            *i+=1;
            }
            else
            {	type=arrtoken[*i]->type;
            	if(type==INTEGER)
                    offset=2;
                if(type==REAL)
                    offset=4;
                if(type==BOOLEAN)
                    offset=1;
                *i=oldi;
            	while(arrtoken[*i]->type!=SEMICOL)
            	{
	            	if(arrtoken[*i]->type==ID)
	            	{
	            		struct symboltableentry* entry=findentry(arrtoken[*i]->value,curr);
	            		if(entry!=NULL)
	            		{
	            			printf("Error: Double declaration at line %d\n",entry->linenumber);
	            			exit(EXIT_FAILURE);
	            		}

		                addentry(curr->hashtable,arrtoken[*i],type,current_offset,offset);
                        current_offset+=offset;

	            	}
            	*i+=1;
            	}
            	*i+=1;
            }
        }
        else
            *i+=1;
    }
    curr->endline=arrtoken[(*i)]->line;
    *i+=1;
   // printf("EXIT REC\n");
    return;
}



int hashvalueentry(char* word)
{
	int len=strlen(word),i,hash=0;
	for (i=0;i<len;i++)
	{
	    hash+=((int)word[i])%20;
	}
	    return hash%20;
}

void addentry(struct symboltableentry* hashtable[],struct token* tokennode,int type,int offset,int width)
{
    int hash=hashvalueentry(tokennode->value);
    struct symboltableentry* new_node= (struct symboltableentry *)malloc(sizeof (struct symboltableentry));
    new_node->next=hashtable[hash];
    new_node->type=type;
    strcpy(new_node->value,tokennode->value);
    new_node->offset=offset;
    new_node->width=width;
    new_node->linenumber=tokennode->line;
    hashtable[hash]=new_node;
}

//changed
struct symboltableentry* findentry(char* word,struct symboltablenode* node)
{
	int hash = hashvalueentry(word);
	struct symboltableentry* ptr=node->hashtable[hash];
	while(ptr!=NULL)
	{
	    if(strcmp(word,ptr->value)==0)
	        return ptr;
	    ptr=ptr->next;
	}
    if(ptr==NULL && node->isFnode)
    {
        int i;
        for(i=0;i<node->inputparam;i++)
        {
            if(strcmp(word,node->input[i].value)==0)
                return &(node->input[i]);

        }

        for(i=0;i<node->outputparam;i++)
        {
            if(strcmp(word,node->output[i].value)==0)
                return &(node->output[i]);

        }

    }
	return NULL;
}

struct symboltableentry* findentrytillparent(char* word,struct symboltablenode* node)
{
    struct symboltableentry* entry=NULL;
    while(node->parent!=NULL)
    {
        if((entry=findentry(word,node))!=NULL)
            return entry;
        node=node->parent;
    }
    return NULL;
}
