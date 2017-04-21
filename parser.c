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
#include "lexer.h"
#define TABLESIZE 191

char tokens[115][100]={
"program","moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1","output_plist","N2","dataType","type","moduleDef","statements","statement","ioStmt","var","whichId","simpleStmt","assignmentStmt","whichStmt",
"lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional","idlist","N3","expression","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term","N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt",
"caseStmts","N9","value","default1","iterativeStmt","range","INTEGER","REAL","BOOLEAN","OF",
"ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR","FOR",
"IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF","ENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK","NUM","RNUM","ERR",
"ID","DRIVERDEF","DRIVERENDDEF","dollar","epsilon"};

int counter;

void push( node_tree* item)
{
    stack[++stack_index]=item;
}

node_tree* pop()
{
    return stack[stack_index--];
}

node_tree* create_node_tree(int item)
{
    node_tree* node1=(node_tree* )malloc(sizeof (node_tree));
    node1->item=item;
    memset(node1->child,NULL,sizeof node1->child);
    node1->children=0;
    node1->parent=NULL;
    node1->typeofdata=-1;
    node1->tokendata=NULL;
    node1->symnode=NULL;
    node1->tag=counter++;
    return node1;
    }


void inorder(node_tree* ptr,FILE* fp)
{
	int len; int lallu;
    if(ptr==NULL)
        return;
    numofptreenodes++;
      inorder(ptr->child[0],fp);
    if(ptr->item==epsilon)
    {   printf("------------------ ");
     	printf("------------------ ");
     	printf("------------------ ");
       	printf("%s ",tokens[ptr->item]);
       	len=18-strlen(tokens[ptr->item]);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       	printf(" ");
        printf("%s ",tokens[ptr->parent->item]);
        len=18-strlen(tokens[ptr->parent->item]);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       	printf(" ");
        printf("------Yes--------- ");
        printf("------------------ ");
  
        printf("\n");

    }
     else if(ptr->item>=INTEGER){
            //printf("%s\n",tokens[ptr->item]);
            //printf("baccha-%d\n",baccha_number);
            ptr->tokendata = arrtoken[baccha_number];
            printf("%s ",arrtoken[baccha_number]->value);
            len=18-strlen(arrtoken[baccha_number]->value);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       	printf(" ");

/************************************************/

            printf("%d ",arrtoken[baccha_number]->line);
            len=14;
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       	printf(" ");

/**********************************************/

            printf("%s ",tokens[ptr->item]);
len=18-strlen(tokens[ptr->item]);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       	printf(" ");
            if(ptr->item==NUM || ptr->item==RNUM){
                printf("%s ",arrtoken[baccha_number]->value);
                len=18-strlen(arrtoken[baccha_number]->value);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       	printf(" ");
            }
            else
                 printf("------------------ ");

            printf("%s ",tokens[ptr->parent->item]);
            len=18-strlen(tokens[ptr->parent->item]);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       	printf(" ");
            printf("--------Yes------- ");
             printf("------------------");
           
            printf("\n");
            baccha_number++;

     }

     else
     {
         printf("------------------ ");
        printf("------------------ ");
     	 printf("------------------ ");
     	  printf("------------------ ");
        if(ptr->parent==NULL)
          printf("-------ROOT------ ");
        else{
        printf("%s ",tokens[ptr->parent->item]);
    len=18-strlen(tokens[ptr->parent->item]);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       	printf(" ");
       }
        printf("-------No--------- ");
        printf("%s ",tokens[ptr->item]);
        len=18-strlen(tokens[ptr->item]);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");
       
        printf("\n");
     }

    int i;
    for(i=1;i<ptr->children;i++)
    {
    inorder(ptr->child[i],fp);
    }

}

void printParseTree(node_tree*  PT, char *outfile)
{
   FILE* fp8=fopen(outfile,"w");
    inorder(PT,fp8);
    fclose(fp8);
}


void getgrammar()
{
    FILE *fpa = fopen("Grammar.txt","r");
    FILE *fpb = fopen("fingrammar.txt","w");
    if(fpa==NULL||fpb==NULL);
       // printf("damn\n");
    char str[1000]={0};

    int cnt=0,i,j,k,x;
while (fgets(str, 1000, fpa) != NULL)
{
    char str2[1000];
    x=0;

    for(i=0;i<strlen(str);i++)
    {
        if(isalpha(str[i])||str[i]=='_')
        {
            int begin=i;
            while(isalnum(str[i])||str[i]=='_')
                {//str2[x++]=str[i];
                i++;}
                //str2[x++]=' ';
            k=0;
            char temp[25]={0};
            for(j=begin;j<i;j++)
                temp[k++]=str[j];
            //printf("t - %s -\n",temp);
            for(j=0;j<=epsilon;j++)
            {
                if(strcmp(temp,tokens[j])==0)
                {

                    char num[5]={0};
                    snprintf(num, sizeof(num), "%d", j);
                    //printf("th - %s\n",num);
                    for(k=0;k<4;k++)
                    {
                        if(isdigit(num[k]))
                       str2[x++]=num[k];
                    }
                    str2[x++]=' ';
                }
            }

        }
    else str2[x++]=str[i];

    }
    str2[x++]='~';
    str2[x++]='\n';
    for(;x<1000;x++)
        str2[x]='\0';
    //puts(str2);
    fputs(str2,fpb);
}
fclose(fpa);
fclose(fpb);
}

int isterm(int i)
{
    return i>=INTEGER;
}

int isepsilonthereg(int x)
{
    int i;
    for(i=0;g[x][i]!=-1;i++)
    {
        if(g[x][i]==epsilon)
            return 1;
    }
    return 0;
}

void ffirst(int x)
{
    //printf("x= %d\n",x);
    int j=0;
    while(fst[x][j]!=-1)
    {
        j++;
    }
    if(fst[x][0]==-1)
    {
        if(isterm(g[x][0])==1&&g[x][0]!=epsilon)
        {
            fst[x][j++]=g[x][0];
        }
        else
        {
            int a=0,flag1=0;
            /*while(isterm(g[x][a])==1&&(g[x][a]!=-1||g[x][a]!=-2))
                                a++;*/
            while(1)
            {
                if(isterm(g[x][a])==1&&g[x][a]!=epsilon&&g[x][a]>=0)
                {
                    fst[x][j++]=g[x][a];
                    break;
                }
                else if(g[x][a]==-2||g[x][a]==-1)
                {
                    fst[x][j++]=epsilon;
                    break;
                }
                ffirst(g[x][a]);
                int k=0;
                for(k=0;fst[g[x][a]][k]!=-1;k++)
                {
                    if(fst[g[x][a]][k]!=epsilon)
                    fst[x][j++]=fst[g[x][a]][k];
                }
                if(isepsilonthereg(g[x][a])==1)
                {
                    a++;
                    /*while(isterm(g[x][a])==1&&(g[x][a]!=-1||g[x][a]!=-2))
                                a++;*/
                }
                else if (isepsilonthereg(g[x][a])==0)
                        {
                            /*if(isterm(g[x][a])==1)
                                fst[x][j++]=g[x][a];*/
                            break;
                        }
            }
        }
        for(i=0;g[x][i]!=-1;i++)
        {
            if(g[x][i]==-2)
            {
                if(isterm(g[x][i+1])&&g[x][i+1]!=epsilon)
                {
                    fst[x][j++]=g[x][i+1];
                }
                else
                {
                    int a=i+1;
                    /*while(isterm(g[x][a])==1&&(g[x][a]!=-1||g[x][a]!=-2))
                                a++;*/
                    while(1)
                    {
                        if(isterm(g[x][a])==1&&g[x][a]!=epsilon)
                        {
                            fst[x][j++]=g[x][a];
                            break;
                        }
                        else if(g[x][a]==-2||g[x][a]==-1)
                        {
                            fst[x][j++]=epsilon;
                            break;
                        }
                        ffirst(g[x][a]);
                        int k=0;
                        for(k=0;fst[g[x][a]][k]!=-1;k++)
                        {
                            //if(fst[g[x][a]][k]!=epsilon)
                            fst[x][j++]=fst[g[x][a]][k];
                        }
                        if(isterm(g[x][a])==0&&isepsilonthereg(g[x][a])==1)
                        {
                            a++;
                            /*while(isterm(g[x][a])==1&&(g[x][a]!=-1||g[x][a]!=-2))
                                a++;*/
                        }
                        else if (isepsilonthereg(g[x][a])==0)
                        {
                            /*if(isterm(g[x][a])==1)
                                fst[x][j++]=g[x][a];*/
                            break;
                        }
                    }
                    i=a;
                }
            }
        }
    }
}

int isepsilontherefst(int x)
{
    int i;
    for(i=0;fst[x][i]!=-1;i++)
    {
        if(fst[x][i]==epsilon)
            return 1;
    }
    return 0;
}

int present (int item,int j)
{
    int start;
    for(start=0;start<indexes[j];start++)
    {

        if(item==follow[j][start])
            return 1;
    }

    return 0;
}

void follow_compute()
{
int j;
follow[0][0]=dollar;
indexes[0]++;
int change=1;
for(i=0;i<INTEGER;i++)
    {
        j=0;
        while(1)
        {
            if(g[i][j]==-1)
                break;
            if(g[i][j]==-2)
                j++;
            int k;
            for(k=j+1;g[i][k]!=-2 && g[i][k]!=-1;k++)
            {
                int l=0;
                int chalo=0;
                while(fst[g[i][k]][l]!=-1)
                { if(fst[g[i][k]][l]==epsilon)
                    chalo=1;
                    if(present(fst[g[i][k]][l],g[i][j]));
                    else
                    {
                        if(fst[g[i][k]][l]!=epsilon)
                        follow[g[i][j]][indexes[g[i][j]]++]=fst[g[i][k]][l];
                    }
                    l++;
                }
                //j follow insert k first
                if(chalo)
                    continue;
                else break;
                //if(k first contains epsilon continue else break
            }
            j++;
        }
    }
change=1;
int counter=10;
while(change)
{  // printf("%d\n",counter++);
    change=0;

    for(i=0;i<INTEGER;i++)
    {
        int j=0;
        while(1)
        {
            if(g[i][j]==-1)
                break;
            if(g[i][j]==-2)
                j++;


            int k;
            for(k=j+1;g[i][k]!=-2 && g[i][k]!=-1;k++)
            {   int l=0;
                int chalo=0;
                while(fst[g[i][k]][l]!=-1)
                {
                    if(fst[g[i][k]][l]==epsilon)
                    chalo=1;
                    l++;
                }
                if(chalo)
                    continue;
                else break;
                //j follow insert k first
                //if(k first contains epsilon continue else break
            }
            if(g[i][k]==-1 || g[i][k]==-2)
            {
                //printf("%d %d ",i,j);
                int l=0;
             while(follow[i][l]!=-1)
                {
                    if(present(follow[i][l],g[i][j]));
                    else if(follow[i][l]!=epsilon)
                    {   change=1;
                        follow[g[i][j]][indexes[g[i][j]]++]=follow[i][l];
                    }
                    l++;
                }
            } //j follow insert i follow
            j++;
        }
    }
}
}

void ComputeFirstAndFollowSets()
{
        int a=0;
        char str[40];
        memset(g,-1,sizeof g);
        int i,j,k,x=0,y;
        FILE *fp1 = fopen("fingrammar.txt","r");
        while (fscanf(fp1, "%s", str) == 1)
        {

            fscanf(fp1,"%s",str);
            y=0;
            while(1)
            {
                fscanf(fp1,"%s",str);
                if(strcmp(str,"~")==0)
                    break;
                else if(strcmp(str,"|")==0)
                    g[x][y++] = -2;
                else
                    g[x][y++] = atoi(str);
            }
            x++;
        }
        memset(fst,-1,sizeof fst);
        for(i=0;i<INTEGER;i++)
        {
            //printf("%d\n",i);
            if(fst[i][0]==-1)
                ffirst(i);
        }
        for(i=INTEGER;i<=epsilon;i++)
        {
            fst[i][0]=i;
        }

        memset (follow,-1,sizeof follow);
        follow_compute();

         FILE* fpa=fopen("first_set.txt","w");
        FILE* fpb=fopen("follow_set.txt","w");
        for(i=0;i<x;i++)
        {
            fprintf(fpa,"%d %s -> { ",i,tokens[i]);
            for(j=0;fst[i][j]!=-1;j++)
            {
                fprintf(fpa,"%s ",tokens[fst[i][j]]);
            }
            fprintf(fpa,"}\n");
        }

        for(i=0;i<x;i++)
        {
            fprintf(fpb,"%d %s -> { ",i,tokens[i]);
            for(j=0;follow[i][j]!=-1;j++)
            {
                fprintf(fpb,"%s ",tokens[follow[i][j]]);
            }
            fprintf(fpb,"}\n");
        }
        fclose(fpa);
        fclose(fpb);

        fclose(fp1);
}

void createparsetable()
{
  int i,j;
  for(i=0;i<INTEGER+10;i++)
  {
      for(j=INTEGER-INTEGER;j<=dollar-INTEGER+10;j++)
      {
          ptable[i][j]=(pnode)malloc(sizeof(struct ptnode));
            ptable[i][j]->rule=-1;
            ptable[i][j]->pos=-1;
      }
  }
  int p=0;
  for(i=0;i<INTEGER;i++)
  {
      //printf("%d\n",i);
      p=0;
      j=0;
      int k;
      while(1)
      {
          //printf("oh-%d\n",i);
          for(;g[i][j]!=-1&&g[i][j]!=-2;)
          {

              for(k=0;fst[g[i][j]][k]!=-1;k++)
                {
                    if(fst[g[i][j]][k]==epsilon)
                        continue;
                    //printf("a-%d %d %d %d\n",i,j,k,fst[g[i][j]][k]);
                    ptable[i][fst[g[i][j]][k]-INTEGER]->rule=i;
                    ptable[i][fst[g[i][j]][k]-INTEGER]->pos=p;
                    //printf("%d %d %d %d\n",i,j,k,fst[g[i][j]][k]);
                }
                if(isepsilontherefst(g[i][j])==1)
                    j++;
                else break;
          }
          //printf("oh-2 %d\n",i);
          if(g[i][j]==-1)
          {
              for(k=0;follow[i][k]!=-1;k++)
              {
                  ptable[i][follow[i][k]-INTEGER]->rule=i;
                  ptable[i][follow[i][k]-INTEGER]->pos=p;
              }
              break;
          }
          else if(g[i][j]==-2)
          {
              for(k=0;follow[i][k]!=-1;k++)
              {
                  ptable[i][follow[i][k]-INTEGER]->rule=i;
                  ptable[i][follow[i][k]-INTEGER]->pos=p;
              }
              j++;
              p++;
          }
          while(g[i][j]!=-1&&g[i][j]!=-2)
          {
              j++;
          }
          if(g[i][j]==-1)
            break;
          else if(g[i][j]==-2)
          {
              j++;
              p++;
          }
      }
  }
}


node_tree*  parseInputSourceCode(char *testcaseFile)
{
    FILE* fp9=fopen(testcaseFile,"r");
    int array_tokens[1000];
    int i=0;
    char buffer9[20];
    while(!feof(fp9))
    {
    fgets(buffer9,sizeof buffer9,fp9);
    array_tokens[i++]=atoi(buffer9);
    }
    array_tokens[i-1]=dollar; //end of file
    push(NULL);
    node_tree* parsetree=create_node_tree(program);
    push(parsetree);
    node_tree* popped_node;
    i=0;
    //printf("done");
    while((popped_node=pop())!=NULL)
    {//printf("done");
        if(popped_node->item>=INTEGER)
        {
            //printf("terminal %d\n",popped_node->item);
            if(array_tokens[i]==popped_node->item)
                i++;
            else
            {
                if(popped_node->item==epsilon);
                else{
                printf("The token %s for lexeme %s  does not match at line %d. The expected token here is %s\n" ,tokens[array_tokens[i]],arrtoken[i]->value,arrtoken[i]->line,tokens[popped_node->item]);
                return NULL;}
            }

        }
        else
        {

          pnode rule= ptable[popped_node->item][array_tokens[i]-INTEGER];
          //printf("non terminal %d %d\n",rule->rule,rule->pos);
          if(rule->rule==-1)
          {
            printf("The token %s for lexeme %s  does not match at line %d. The expected token here is %s\n" ,tokens[array_tokens[i]],arrtoken[i]->value,arrtoken[i]->line,tokens[popped_node->item]);
            return NULL;
          }
          int lal=0;
          int count=0;
          while(1)
          {
              if(count==rule->pos)
                break;
             if(g[rule->rule][lal]==-2)
                count++;
              lal++;

          }
          int start=0;
          int array_of_rules[20];

          while(g[rule->rule][lal]!=-1 && g[rule->rule][lal]!=-2 )
            array_of_rules[start++]=g[rule->rule][lal++];
            //printf("done");
          array_of_rules[start]=-1;

          int j=0;
           while( array_of_rules[j]!=-1)
            {
                popped_node->child[j]=create_node_tree(array_of_rules[j]);
                popped_node->child[j]->parent=popped_node;
                popped_node->children++;
                j++;
           }
           j--;
           while(j>=0)
           {
               push(popped_node->child[j--]);

           }
        }
    }
    printf("Successful parsing\n");
    return parsetree;
}



