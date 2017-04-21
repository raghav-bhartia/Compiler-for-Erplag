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
#include "typecheck.h"
#include "parser.h"
#include "symboltable.h"
#include "ast.h"
#include "semantic.h"
#include "codegenerator.h"

FILE* filep;

char tokens1[115][100]={
"program","moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1","output_plist","N2","dataType","type","moduleDef","statements","statement","ioStmt","var","whichId","simpleStmt","assignmentStmt","whichStmt",
"lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional","idlist","N3","expression","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term","N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt",
"caseStmts","N9","value","default1","iterativeStmt","range","INTEGER","REAL","BOOLEAN","OF",
"ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR","FOR",
"IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF","ENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK","NUM","RNUM","ERR",
"ID","DRIVERDEF","DRIVERENDDEF","dollar","epsilon"};

int main(int argc,char* argv[])
{
    add_keywords();
    printf("(LEVEL 4:Symbol table/ AST/ Type checking/ Semantic Rules/Code generation modules work.\n");
    printf("Please input case number and input in strict order starting from 1 till 7\n");
    //int choice,c=0;
    node_tree* ans;
   // while(1)
    {
        //c++;
        //printf("input choice- ");
      //  scanf("%d",&choice);
        
        //if(choice==1)
        {
            removeComments(argv[1],"TheFile.txt");
            FILE* cmt=fopen("TheFile.txt","r");
            char ans[1000000]={0};
            if(cmt==NULL)
            {
                printf("error opening file - check permissions\n");
                return 0;
            }
            int sz=fread(ans,1,sizeof ans,cmt);
            if(sz==sizeof(ans))
            {
                printf("entire file not read\n");
            }
            puts(ans);
            fclose(cmt);

        }

        
        //if(choice==2)
        {
            FILE* fpx=fopen("TheFile.txt","r");
           
            //FILE *fp3 = fopen("tokendata.txt", "w");
            int lexerr=0;
            int tokenarrIndex=0;
            while(getliner(fpx))
            {
                line_number++;
                while(i<strlen(buf1))
                {

                    struct token* newToken= getNextToken();
                    arrtoken[tokenarrIndex++]=newToken;
                    if(error_encountered>=0)
                    {
                        lexical_error_function(error_encountered,newToken);
                        lexerr=1;
                        break;
                    }
                    printf("%s %s %d\n",tokens1[newToken->type],newToken->value,newToken->line);
                    //fprintf(fp3,"%d %s %s %d\n",newToken->type,tokens1[newToken->type],newToken->value,newToken->line);
                    //fprintf(fp2,"%d\n", newToken->type);
                    //printf("arrtoken-%s\n",arrtoken[tokenarrIndex-1]->type );
                }
            }
            count_tokens=tokenarrIndex;
            fclose(fpx);
           
            //fclose(fp3);
            if(lexerr==1)
            return 0;
        }
        

         
        for(i=0;i<=count_tokens-2;i++)
        {
            int j;
            if(arrtoken[i]->type==ASSIGNOP&&arrtoken[i+1]->type==MINUS)
            {

                for(j=count_tokens-1;j>=i+1;j--)
                {
                    arrtoken[j+1]=arrtoken[j];
                }
                count_tokens++;
                
                arrtoken[i+1]=(struct token*)malloc(sizeof (struct token));
                arrtoken[i+1]->type=NUM;
                arrtoken[i+1]->line=arrtoken[i]->line;
                arrtoken[i+1]->value=(char*)malloc(2*sizeof (char));
                arrtoken[i+1]->value[0]='0';
                arrtoken[i+1]->value[1]=0;

                
            }


        }
        FILE *fp2 = fopen("tokens.txt", "w");
        for(i=0;i<=count_tokens-1;i++)
        {
            fprintf(fp2,"%d\n",arrtoken[i]->type);


        }
         fclose(fp2);
        //if(choice==3)
        {
            getgrammar();
            int i,j;
            ComputeFirstAndFollowSets();
            createparsetable();
            ans = parseInputSourceCode("tokens.txt");
            if(ans==NULL)
                return;
        }
        //if(choice==4)

numofastnodes=0;
 numofptreenodes=0;

        {
            printParseTree(ans,"parsetree.txt");
            printf("\nCheck generated first and follow set in first_set.txt and follow_set.txt\n");
            //return 0;
        }
        
        
         struct symboltablenode* symtable;
        {
            //printf("INFUNCTION\n"); 
            symtable= createsymboltable();
            printf("done symbol table\n");
            //printsymtable(symtable);
        }

        
        	
            printf("STARTING AST\n");
            createAST(ans);
            printf("ASTDONE\n");
            FILE* astdoc=fopen("ast.txt","w");
            printasttree(ans,astdoc);
            fclose(astdoc);
            printf("ALL DONE with ast\n");
        

        
        int sptree=numofptreenodes*sizeof(node_tree);
        int sast=numofastnodes*sizeof(node_tree);
        printf("Parsetree :\n\tNum of nodes- %d\n\tBytes taken - %d\n",numofptreenodes,sptree);
        printf("AST       :\n\tNum of nodes- %d\n\tBytes taken - %d\n",numofastnodes,sast);
        printf("Compression percentage: %f percent\n",100*((sptree-sast)/((float)sptree)) );

        
            int i,j;
            for(i=0;i<symtable->count;i++)
            {
                printf("%d %s\n",i,symtable->children[i]->name);
            }
            printf("typecheck starting\n");
            typecheck(symtable,ans);
            printf("typecheck done\n");
            printf("Semantic start\n");
            semantic(ans,symtable);
            printf("\nSemantic done !!!\n");

       
       filep=fopen("table.txt","w");
        fprintf(filep,"lexeme            type              module            lines             level             width             offset\n");
       	printsymboltable(ans);
        fclose(filep);
        printf("symbol table printed in table.txt with offsets\n");
       	improve(ans);
        printf("improvement done\n");
       	FILE* astdoc2=fopen("ast2.txt","w");
       	numofastnodes=0;
        printasttree(ans,astdoc2);
        fclose(astdoc2);
        printf("print astlevel 2 improvement done\nCheck out modified ast2 in ast2.txt in parsetree format\n");
        
        sast=numofastnodes*sizeof(node_tree);
        sptree=numofptreenodes*sizeof(node_tree);
        
  		printf("Parsetree :\n\tNum of nodes- %d\n\tBytes taken - %d\n",numofptreenodes,sptree);
        printf("AST       :\n\tNum of nodes- %d\n\tBytes taken - %d\n",numofastnodes,sast);
        printf("Compression percentage: %f percent\n",100*((sptree-sast)/((float)sptree)) );

       printf("Starting code generation\n");
	   FILE* fp11=freopen(argv[2],"w",stdout);
       printf("global main\n");
       printf("extern printf\nextern atoi\nextern scanf\n");
       printf("extern puts\n");
       printf("section .data\n");
       printf("arr: times %d db 0\n",current_offset);
       char str[3]="%d";
       printf( "men:  db \"the number is %s \",10,0\n",str);
       printf("LC5:    db  \"%s\",0\n",str);
       printf("choice: dw 0\n");
       printf("section .text\n");
       printf("main:\n");
       	codegen(ans);
        fclose(fp11);

        freopen("/dev//tty","a",stdout);
        printf("Code compiled successfully\n");
        return 0;
    }
    return 0;
}

void improve(node_tree* astroot)
{
    int i;
    //printf("improve: %s\n",tokens1[astroot->item]);
    if(astroot->item==var)
    {
        if(astroot->children==1)
        {
            if(astroot->child[0]->item==NUM)
                {
                    astroot->b_offset=-2;
                    astroot->tokendata=astroot->child[0]->tokendata;
                }
            else if(astroot->child[0]->item==RNUM)
                {
                    astroot->b_offset=-3;
                    astroot->tokendata=astroot->child[0]->tokendata;
                }
        }
        else
        {
            if(astroot->child[1]->children==1)
            {
                astroot->typeofdata=astroot->child[0]->typeofdata;
                astroot->tokendata=astroot->child[0]->tokendata;
                astroot->a_offset=findentrytillparent(astroot->child[0]->tokendata->value,astroot->child[0]->symnode)->offset;
                astroot->b_offset=-1;
               
                
            }
            else

            {   
                astroot->typeofdata=astroot->child[0]->typeofdata;
                astroot->tokendata=astroot->child[0]->tokendata;
                astroot->a_offset=findentrytillparent(astroot->child[0]->tokendata->value,astroot->child[0]->symnode)->offset;
                astroot->b_offset=findentrytillparent(astroot->child[1]->child[1]->tokendata->value,astroot->child[1]->child[1]->symnode)->offset;
                
            }


        }
        astroot->child[0]=NULL;
        astroot->children=0;

    }
    else if(astroot->item==assignmentStmt)
    {
        //improve(astroot->child[0]);
        improve(astroot->child[1]);
      
        if(astroot->child[1]->item==lvalueIDStmt)
        {
            astroot->child[1]=astroot->child[1]->child[1];
            //astroot->child[1]->child[1]->parent=astroot;
            astroot->child[0]->b_offset=-1;
            astroot->child[0]->a_offset=findentrytillparent(astroot->child[0]->tokendata->value,astroot->child[0]->symnode)->offset;

        }
        else if(astroot->child[1]->item==lvalueARRStmt)
        {
            astroot->child[0]->a_offset=findentrytillparent(astroot->child[0]->tokendata->value,astroot->child[0]->symnode)->offset;
            astroot->child[0]->tokendata=astroot->child[1]->child[1]->child[0]->tokendata;
            if(astroot->child[1]->child[1]->child[0]->item==NUM)
            {
                astroot->child[0]->b_offset=-2;
            }
            else//id
            {
                astroot->child[0]->b_offset=findentrytillparent(astroot->child[1]->child[1]->child[0]->tokendata->value,astroot->child[1]->child[1]->child[0]->symnode)->offset;
            }
             astroot->child[1]=astroot->child[1]->child[4];
             //astroot->child[1]->child[4]->parent=astroot;
        }

    }

    else if(astroot->item==ID)
    {
        astroot->b_offset=-1;
        astroot->a_offset=findentrytillparent(astroot->tokendata->value,astroot->symnode)->offset;
    }


    else
    { 
        for(i=0;i<astroot->children;i++)
        {
            improve(astroot->child[i]);
        }
    }


}




void printsymboltable(node_tree* root)
{
    //printf("yo\n");
    int i;
    if(root==NULL)
        return ;
    printsymboltable(root->child[0]);

    if(root->item==ID&& root->parent->parent->item==declareStmt)
        printsymentry(root);

    for(i=1;i<root->children;i++)
        printsymboltable(root->child[i]);


}

int elements(struct symboltableentry* entry)
{
    if(entry->type==INTEGER)
        return (entry->width/2);

    if(entry->type==REAL)
        return (entry->width/4);

    if(entry->type==BOOLEAN)
        return (entry->width/1);


}

void printsymentry(node_tree* root)
{
    int pad=18;
    char buffer[200];
    memset(buffer,' ',sizeof(buffer));
    struct symboltablenode * scopenode=root->symnode;
    int nestinglevel=scopenode->nestinglevel;
    struct symboltableentry* entry= findentry(root->tokendata->value,scopenode);
    while(scopenode->parent->parent!=NULL)
        scopenode=scopenode->parent;

    sprintf(buffer+(0*pad),"%s",root->tokendata->value);
    if(elements(entry)>1)
    {sprintf(buffer+(1*pad),"array(%d,%s)",elements(entry),tokens1[entry->type]);}
    else
    sprintf(buffer+(1*pad),"%s",tokens1[entry->type]);
    sprintf(buffer+(2*pad),"%s",scopenode->name);
    sprintf(buffer+(3*pad),"%d to %d",scopenode->startline,scopenode->endline);
    sprintf(buffer+(4*pad),"%d",nestinglevel);
    sprintf(buffer+(5*pad),"%d",entry->width);
    sprintf(buffer+(6*pad),"%d\n",entry->offset);

    for(i=0;i<200&& buffer[i]!='\n';i++)
    {
        if(buffer[i]==0)
            buffer[i]=' ';
    }
    buffer[i+1]=0;

    fprintf(filep,"%s",buffer);



}