
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

char tokens6[115][100]={
"program","moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1","output_plist","N2","dataType","type","moduleDef","statements","statement","ioStmt","var","whichId","simpleStmt","assignmentStmt","whichStmt",
"lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional","idlist","N3","expression","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term","N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt",
"caseStmts","N9","value","default1","iterativeStmt","range","INTEGER","REAL","BOOLEAN","OF",
"ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR","FOR",
"IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF","ENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK","NUM","RNUM","ERR",
"ID","DRIVERDEF","DRIVERENDDEF","dollar","epsilon"};





int label,end;

node_tree* idtemp;

void putvarinreg(char* reg,node_tree* variable)
{
    char newreg[10];
    strcpy(newreg,reg);
    reg=newreg;
    //printf("yo\n");

    if(variable->typeofdata==INTEGER)
    {
        if(variable->b_offset==-2)
        {
           // printf("1\n");
            printf("mov %s,%d\n",reg,atoi(variable->tokendata->value));

        }
        else if(variable->b_offset==-1)
        {
            printf("mov %s,word[arr+%d]\n",reg,variable->a_offset);
           // printf("%s\n",variable->tokendata->value);
        }
        else
        {
            printf("MOV ESI,0\n");
            printf("mov SI,word[arr+%d]\n",variable->b_offset);
            printf("mov %s,word[arr+2*ESI+%d]\n",reg,variable->a_offset);
        }
    }
    else if (variable->typeofdata==BOOLEAN)
    {
        printf("MOV %s,0\n");

        if(variable->b_offset==-1)
        {

            //printf("mov %s,0",reg);
            char newreg[10];
            reg[strlen(reg)-1]='L';
            //printf("yo\n");
            printf("mov %s,byte[arr+%d]\n",reg,variable->a_offset);
        }
        else
        {
            printf("MOV ESI,0\n");
            reg[strlen(reg)-1]='L';
            printf("mov SI,word[arr+%d]\n",variable->b_offset);
            //printf("mov %s,0",reg);
            printf("mov %s,byte[arr+ESI+%d]\n",reg,variable->a_offset);
        }
    }
}

void putreginmem(node_tree* variable,char* reg)

{

    char newreg[10];
    strcpy(newreg,reg);
    reg=newreg;
    if(variable->typeofdata==INTEGER)
    {
        if(variable->b_offset==-1)
        {
            printf("mov word[arr+%d],%s\n",variable->a_offset,reg);
        }
        else if(variable->b_offset==-2)
        {
            printf("MOV ESI,0\n");
            printf("mov SI,%d\n",atoi(variable->tokendata->value));
            printf("mov word[arr+2*ESI+%d],%s\n",variable->a_offset,reg);

        }
        else{
            printf("MOV ESI,0\n");
            printf("mov SI,word[arr+%d]\n",variable->b_offset);
            printf("mov word[arr+2*ESI+%d],%s\n",variable->a_offset,reg);

        }
    }

    if(variable->typeofdata==BOOLEAN)
    {
        reg[strlen(reg)-1]='L';
        if(variable->b_offset==-1)
        {
            printf("mov byte[arr+%d],%s\n",variable->a_offset,reg);
        }
        else if(variable->b_offset==-2)
        {
            printf("MOV EDI,0\n");
            printf("mov DI,%d\n",atoi(variable->tokendata->value));
            printf("mov byte[arr+2*EDI+%d],%s\n",variable->a_offset,reg);

        }
        else{
            printf("MOV EDI,0\n");
            printf("mov DI,word[arr+%d]\n",variable->b_offset);
            printf("mov byte[arr+2*EDI+%d],%s\n",variable->a_offset,reg);

        }
    }
}

void codegen(node_tree* astroot)

{
    int i;
    
    if(astroot==NULL||astroot->item==epsilon)
        return;

    if(astroot->item==assignmentStmt)
    {
        // printf("%s %s\n",tokens6[astroot->child[0]->item],tokens6[astroot->child[1]->item]);
        if(astroot->child[1]->child[0]->item==var){
            putvarinreg("AX",astroot->child[1]->child[0]);
        printf("PUSH AX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP AX\n");
        putreginmem(astroot->child[0],"AX");
        return;
    }
    else if(astroot->item==iterativeStmt)
    {

        if(astroot->child[0]->item==WHILE)
        {
            //printf("in loop while\n");
            int temp=label;
            printf("\nlabel%d: \n",temp);
            label+=2;
            codegen(astroot->child[2]);
            printf("POP AX\n");
            printf("CMP AX,0\n");
            printf("JZ label%d\n",temp+1);
            codegen(astroot->child[5]);
            printf("JMP label%d\n",temp);
            printf("label%d: \n",temp+1);
        }
        else
        {
            int temp=label;
            temp+=2;

            printf("MOV CX,%d\n",atoi(astroot->child[4]->child[0]->tokendata->value));
            printf("label%d:\n",temp);
            putreginmem(astroot->child[2],"CX");

            printf("CMP CX,%d\n",atoi(astroot->child[4]->child[2]->tokendata->value));
            printf("JG label%d\n",temp+1);

            codegen(astroot->child[7]);

            putvarinreg("CX",astroot->child[2]);
            printf("INC CX\n");
            printf("JMP label%d\n",temp);
            printf("label%d:\n",temp+1);
        }
    }
    else if(astroot->item==ioStmt)
    {
        if(astroot->child[0]->item==GET_VALUE)
        {
            printf("mov rdi, LC5\nmov rsi, choice \nxor eax, eax\ncall scanf \nmov eax,[choice]\n");
            astroot->child[0]->typeofdata=INTEGER;
            printf("\n;----------%d %s %d\n",astroot->child[1]->typeofdata,tokens6[astroot->child[1]->item],astroot->child[1]->a_offset);
            putreginmem(astroot->child[1],"AX");
            printf("\n;------------ done printing\n");
          
        }
        else if(astroot->child[0]->item==PRINT)
        {

            printf("mov rax,0\n");
             putvarinreg("BX",astroot->child[1]);
             printf("cmp BX,0\n");
             printf("MOV rbx,0xFFFFFFFFFFFFFFFF\n" );
             printf("cmovl rax,rbx\n");
             putvarinreg("AX",astroot->child[1]);

             printf("push    rax\npush    rcx\nmov     rdi, men\nmov     rsi, rax\nxor     rax, rax\ncall    printf\npop     rcx\npop     rax\n");

        }



    }
    else if(astroot->item==condionalStmt)
    {
        idtemp=astroot->child[2];
        codegen(astroot->child[5]);
        codegen(astroot->child[6]);
        printf("end%d:\n",end);
        end++;
        return;
    }
    else if(astroot->item==caseStmts)
    {
        int temp=label;
        label++;
        if(astroot->child[1]->item==NUM)
            printf("MOV CX,%d\n",atoi(astroot->child[1]->tokendata->value));
        else if(astroot->child[1]->item==TRUE)
            printf("MOV CX,1\n");
        else printf("MOV CX,0\n");

        putvarinreg("DX",idtemp);
        printf("CMP CX,DX\n");
        printf("JNZ label%d\n",temp);
        codegen(astroot->child[3]);
        printf("JMP end%d\n",end);             /**deciding**/
        printf("label%d:\n",temp);
        codegen(astroot->child[6]);
        return;
    }
    else if(astroot->item==N9)
    {
        if(astroot->children==1)
            return;
        int temp=label;
        label++;
        if(astroot->child[1]->item==NUM)
            printf("MOV CX,%d\n",atoi(astroot->child[1]->tokendata->value));
        else if(astroot->child[1]->item==TRUE)
            printf("MOV CX,1\n");
        else printf("MOV CX,0\n");

        putvarinreg("DX",idtemp);
        printf("CMP CX,DX\n");
        printf("JNZ label%d\n",temp);
        codegen(astroot->child[3]);
        printf("JMP end%d\n",end);             /**deciding**/
        printf("label%d:\n",temp);
        codegen(astroot->child[6]);
        return;
    }
    else if(astroot->item==default1)
    {
        if(astroot->children==1)
            return;
        codegen(astroot->child[2]);
    }
    



   else if(astroot->item==PLUS)
    {

         if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP AX\n");
        printf("POP BX\n");

        printf("ADD AX,BX\n");
        printf("PUSH AX\n");
        return;
    }

    else if(astroot->item==MINUS)
    {
        
        if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP BX\n");
        printf("POP AX\n");

        printf("SUB AX,BX\n");
        printf("PUSH AX\n");
        return;
    }

     else if(astroot->item==MUL)
    {
         if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP AX\n");
        printf("POP BX\n");

        printf("IMUL BX\n");
        printf("PUSH AX\n");
        return;
    }
     else if(astroot->item==DIV)
    {
         if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP BX\n");
        printf("POP AX\n");

        printf("IDIV BX\n");
        printf("PUSH AX\n");
        return;
    }
    else if(astroot->item==OR)
    {
       
        if(astroot->child[0]->item==var)
        {
            printf("MOV AX ,0\n");
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            printf("MOV BX ,0\n");
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else
            codegen(astroot->child[1]);
        printf("POP AX\n");
        printf("POP BX\n");

        printf("OR AX,BX\n");
        printf("PUSH AX\n");
        return;
    }

    else if(astroot->item==AND)
    {
        if(astroot->child[0]->item==var)
        {
            printf("MOV AX ,0\n");
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            printf("MOV BX ,0\n");
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else
            codegen(astroot->child[1]);
        printf("POP AX\n");
        printf("POP BX\n");

        printf("AND AX,BX\n");
        printf("PUSH AX\n");
        return;
    }
    else if(astroot->item==LE)
    {
        if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        printf("POP BX\n");
        printf("POP AX\n");
        printf("MOV DX,0\n");
        printf("MOV SI,1\n");
        printf("CMP AX,BX\n");
        printf("CMOVLE DX,SI\n");
        printf("PUSH DX\n");
        return;
    }
   
    else if(astroot->item==LT)
    {
        if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP BX\n");
        printf("POP AX\n");
        printf("MOV DX,0\n");
        printf("MOV SI,1\n");
        printf("CMP AX,BX\n");
        printf("CMOVL DX,SI\n");
        printf("PUSH DX\n");
        return;
    }
    else if(astroot->item==GE)
    {
        if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP BX\n");
        printf("POP AX\n");
        printf("MOV DX,0\n");
        printf("MOV SI,1\n");
        printf("CMP AX,BX\n");
        printf("CMOVGE DX,SI\n");
        printf("PUSH DX\n");
        return;
    }
    else if(astroot->item==GT)
    {
        if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP BX\n");
        printf("POP AX\n");
        printf("MOV DX,0\n");
        printf("MOV SI,1\n");
        printf("CMP AX,BX\n");
        printf("CMOVG DX,SI\n");
        printf("PUSH DX\n");
        return;
    }
    else if(astroot->item==EQ)
    {
        if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP BX\n");
        printf("POP AX\n");
        printf("MOV DX,0\n");
        printf("MOV SI,1\n");
        printf("CMP AX,BX\n");
        printf("CMOVE DX,SI\n");
        printf("PUSH DX\n");
        return;
    }
    else if(astroot->item==NE)
    {
        if(astroot->child[0]->item==var)
        {
            putvarinreg("AX",astroot->child[0]);
            printf("PUSH AX\n");
        }
        else
            codegen(astroot->child[0]);
        if(astroot->child[1]->item==var)
        {
            putvarinreg("BX",astroot->child[1]);
            printf("PUSH BX\n");
        }
        else 
            codegen(astroot->child[1]);
        printf("POP BX\n");
        printf("POP AX\n");
        printf("MOV DX,0\n");
        printf("MOV SI,1\n");
        printf("CMP AX,BX\n");
        printf("CMOVNE DX,SI\n");
        printf("PUSH DX\n");
        return;
    }

    else {
    for(i=0;i<astroot->children;i++)
    {
        codegen(astroot->child[i]);
    }
}

}
