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
#include "lexer.h"
#include "alldef.h"
#include "parser.h"
//#include "allglobals.h"
#define TABLESIZE 191


char known_symbols[]={'(',')','[',']','/','+','-',';',',','*','<','=','>','!','.',0,' ','\n'};

//int line_number=0;
int getliner(FILE* fp)
{
    memset(buf1,'\0',sizeof(buf1));
    if(feof(fp))
        return 0;
    fgets(buf1,sizeof(buf1),fp);
    i=0;
    int j=strlen(buf1)-1;
    while(buf1[j]=='\n'||buf1[j]==' '||buf1[j]=='\t')
        buf1[j--]='\0';
    return 1;
}

void lexical_error_function(int error,struct token* ptr)
{
    if(error==ERROR_1)
    printf("Identifier at line %d is longer than the prescribed length\n",ptr->line);

    if(error==ERROR_2)
    printf("Unknown symbol %s at line %d\n",ptr->value,ptr->line);

    if(error==ERROR_3)
    printf("Unknown pattern (%s)\n",ptr->value);

    if(error==ERROR_4);
    if(error==ERROR_5);
}

int hashvalue(char* word)
{
	int len=strlen(word),i,hash=0;
	for (i=0;i<len;i++)
	{
	    hash+=((int)word[i])%TABLESIZE;
	}
	    return hash%TABLESIZE;
}

void add_keyword(struct node* hashtable[],char* keyword,enum tokentype type)
{
    int hash=hashvalue(keyword);
    struct node* new_node= (struct node *)malloc(sizeof (struct node));
    new_node->next=hashtable[hash];
    new_node->type=type;
    strcpy(new_node->string,keyword);
    hashtable[hash]=new_node;
}

//changed
int find(char* word)
{
	int hash=hashvalue(word);
	struct node* ptr=hashtable[hash];
	while(ptr!=NULL)
	{
	    if(strcmp(word,ptr->string)==0)
	        return ptr->type;
	    ptr=ptr->next;
	}
	if(strlen(word)>8)
	    error_encountered=ERROR_1;
	    return ID;

}

void removeComments(char* testcasefile, char* cleanfile)
{

	FILE * fp1=fopen(testcasefile,"r");
	FILE * fp2=fopen(cleanfile,"w");
	bool state=0;
	char buffer[100000];
	char buffer2 [100000];
	int read=0;
	while(!feof(fp1))
  	{
	fgets(buffer+read,sizeof buffer,fp1);
	read=strlen(buffer);

	}
    int i,j=0;
    for(i=0;i<strlen(buffer);)
    {
    	if(buffer[i]==13)
    	{
    		i++;
    		continue;
    	}
    	if(buffer[i]=='*'&& buffer[i+1]=='*')
    	{
    	state= !(state);
    	i+=2;
    	continue;
		}
		else if(state==0)
		{

			buffer2[j++]=buffer[i];

		}
		else if(buffer[i]=='\n') {
            buffer2[j++]=buffer[i];

		}
        i++;

	}
	j--;
    while(buffer2[j]=='\n'||buffer2[j]=='\t'||buffer2[j]==' ')
    {

        buffer2[j]=0;
        j--;
    }
    fputs(buffer2,fp2);
    fclose(fp1);
    fclose(fp2);
}

void string_copy(char* dest,char* src,int begin,int end)
{
    int index=0;
    int len=end-begin;
    while(index<len){
        dest[index]=src[index+begin];
        index++;}
    dest[index]=0;
}

struct token* getNextToken()
{
    struct token* newToken= (struct token*) malloc(sizeof (struct token));
    newToken->line=0;
    newToken->value=NULL;
    newToken->type=0;
    error_encountered=-1;
    char str[1000];
     int k=0,j=0;
    int s=1;
    int begin=i;
    enum tokentype ans;
    int a=0;
    char* arr=buf1;
  while(1)
  {
      switch(s)
      {
      case 1:
                if(arr[i]==' '|| arr[i]=='\t' || arr[i]=='\n' || arr[i]=='\0')
                {
                    s=1;
                    i++;
                    begin=i;
                    break;
                }
                switch(arr[i])
                {
                    case '(':
                        s=2;
                        i++;
                        break;
                    case ')':
                        s=3;
                        i++;
                        break;
                    case ']':
                        s=5;
                        i++;
                        break;
                    case '[':
                        s=4;
                        i++;
                        break;
                    case '/':
                        s=6;
                        i++;
                        break;
                    case '+':
                        s=7;
                        i++;
                        break;
                    case '-':
                        s=8;
                        i++;
                        break;
                    case ';':
                        s=9;
                        i++;
                        break;
                    case ',':
                        s=10;
                        i++;
                        break;
                    case '*':
                        s=21;
                        i++;
                        break;
                    case '<':
                        i++;
                        s=22;
                        break;
                    case '=':
                        s=26;
                        i++;
                        break;
                    case '>':
                        s=28;
                        i++;
                        break;
                    case ':':
                        s=32;
                        i++;
                        break;
                    case '!':
                        s=35;
                        i++;
                        break;
                    case '.':
                        s=37;
                        i++;
                        break;

                    default:
                         if(arr[i]>='0'&&arr[i]<='9')
                            {
                        s=11;
                        i++;
                            }
                    else if(isalpha(arr[i]))
                    {
                    s=39;
                    i++;
                    }
                    else
                        s=41;
                    break;
                    }

                break;
        case 2:
            a=1;

            newToken->type=BO;
            break;
        case 3:
            newToken->type=BC;
            a=1;
            break;
        case 4:
            newToken->type=SQBO;
            a=1;
            break;
        case 5:
            newToken->type=SQBC;
            a=1;
            break;
        case 6:
            a=1;
            newToken->type=DIV;
            break;
        case 7:
            newToken->type=PLUS;
            a=1;
            break;
        case 8:
            newToken->type=MINUS;
            a=1;
            break;
        case 9:
            a=1;
            newToken->type=SEMICOL;
            break;
        case 10:
            newToken->type=COMMA;
            a=1;
            break;
        case 11:
            if(arr[i]>='0'&&arr[i]<='9')
               {
                 i++;
                 s=11;
               }
            else if(arr[i]=='.')
            {
                s=13;
                i++;
            }
            else if(isalpha(arr[i]))
            {
                s=41;

            }
            else
                s=12;
            break;
        case 12:
            a=1;
            newToken->type=NUM;
            break;
        case 13:
            if(isdigit(arr[i]))
            {
                s=15;
                i++;
            }
            else if(arr[i]=='.')
            {
                s=14;
                i--;
            }
            else
            {
                    s=41;
            }
            break;
        case 14:
            a=1;
            newToken->type=NUM;
            break;
        case 15:
            if(isdigit(arr[i]))
            {
                s=15;
                i++;
            }
            else if(arr[i]=='e'||arr[i]=='E')
            {
                s=17;
                i++;
            }
             else if(isalpha(arr[i]))
            {
                s=41;

            }
            else
                {
                    s=16;
                }
            break;
        case 16:
            a=1;
            newToken->type=RNUM;
            break;
        case 17:
            if(arr[i]=='+'||arr[i]=='-')
            {
                s=18;
                i++;
            }
            else if(isdigit(arr[i]))
            {
                s=19;
                i++;
            }
            else
            {
                s=41;
            }

            break;

        case 18:
            if(isdigit(arr[i]))
            {
                s=19;
                i++;
            }
            else s=41;
            break;

        case 19:
            if(isdigit(arr[i]))
            {
                i++;
                s=19;
            }
            else if(isalpha(arr[i]))
            {
                s=41;

            }
            else s=20;
            break;
        case 20:
            a=1;
            newToken->type=RNUM;
            break;
        case 21:
            a=1;
            newToken->type=MUL;
            break;
        case 22:
            if(arr[i]=='=')
            {
                s=23;
                i++;
            }
            else if(arr[i]=='<')
            {
                s=24;
                i++;
            }
            else s=25;
            break;
        case 23:
            a=1;
            newToken->type=LE;
            break;
        case 24:
            if(arr[i]=='<')
            {
                a=1;
                newToken->type=DRIVERDEF;
                i++;
            }
            else
            {
            a=1;
            newToken->type=DEF;
            }
            break;
        case 25:
            a=1;
            newToken->type=LT;
            break;
        case 26:
            if(arr[i]=='='){
		i++;
                s=27;}
            else s=41;
        case 27:
            a=1;
            newToken->type=EQ;
            break;
        case 28:
            if(arr[i]=='=')
            {
                s=30;
                i++;
            }
            else if(arr[i]=='>')
            {
                s=31;
                i++;
            }
            else s=29;
            break;
        case 29:
            a=1;
            newToken->type=GT;
            break;
        case 30:
            a=1;
            newToken->type=GE;
            break;
        case 31:
            if(arr[i]=='>')
            {
                a=1;
                newToken->type=DRIVERENDDEF;
                i++;
            }
            else
            {
            a=1;
            newToken->type=ENDDEF;
            }
            break;
        case 32:
            if(arr[i]=='=')
            {
                s=33;
                i++;
            }
            else s=34;
            break;
        case 33:
            a=1;
            newToken->type=ASSIGNOP;
            break;
        case 34:
            a=1;
            newToken->type=COLON;
            break;
        case 35:
            if(arr[i]=='=')
            {
                s=36;
                i++;
            }
            else s=41;
        case 36:
            a=1;
            newToken->type=NE;
            break;
        case 37:
            if(arr[i]=='.')
            {
                s=38;
                i++;
            }
            else s=41;
        case 38:
            a=1;
            newToken->type=RANGEOP;
            break;
        case 39:
            if(isalpha(arr[i])||isdigit(arr[i])||arr[i]=='_')
            {
                s=39;
                i++;
            }
            else s=40;
            break;
        case 40:


            for(j=begin;j<i;j++)
                str[k++]=buf1[j];
            str[k]='\0';
            a=1;
            //printf("%s\n %d\n %d\n",str,begin,i);
            newToken->type=find(str);
            //ans=21;
            break;
        case 41:

            if(strchr(known_symbols,arr[i])==NULL && !(isalnum(arr[i])))
               error_encountered=ERROR_2;
               else
                error_encountered=ERROR_3;
            a=1;
            break;
      }
    if(a==1)
        break;
  }
newToken->value= (char*)malloc((i-begin+10)* sizeof (char));
string_copy(newToken->value,arr,begin,i);
if(error_encountered==ERROR_2){
    newToken->value[0]=arr[i];
    newToken->value[1]=0;
}
if(error_encountered==ERROR_3){
    newToken->value[i-begin]=arr[i];
    newToken->value[i-begin+1]=0;
}
newToken->line=line_number;
return newToken;
}

void add_keywords()
{
memset(hashtable,(struct node*)NULL,sizeof hashtable);
add_keyword(hashtable,"integer",INTEGER);
add_keyword(hashtable,"real",REAL);
add_keyword(hashtable,"boolean",BOOLEAN);
add_keyword(hashtable,"of",OF);
add_keyword(hashtable,"array",ARRAY);
add_keyword(hashtable,"start",START);
add_keyword(hashtable,"end",END);
add_keyword(hashtable,"declare",DECLARE);
add_keyword(hashtable,"module",MODULE);
add_keyword(hashtable,"driver",DRIVER);
add_keyword(hashtable,"program",PROGRAM);
add_keyword(hashtable,"get_value",GET_VALUE);
add_keyword(hashtable,"print",PRINT);
add_keyword(hashtable,"use",USE);
add_keyword(hashtable,"with",WITH);
add_keyword(hashtable,"parameters",PARAMETERS);
add_keyword(hashtable,"true",TRUE);
add_keyword(hashtable,"false",FALSE);
add_keyword(hashtable,"takes",TAKES);
add_keyword(hashtable,"input",INPUT);
add_keyword(hashtable,"returns",RETURNS);
add_keyword(hashtable,"AND",AND);
add_keyword(hashtable,"OR",OR);
add_keyword(hashtable,"for",FOR);
add_keyword(hashtable,"in",IN);
add_keyword(hashtable,"switch",SWITCH);
add_keyword(hashtable,"case",CASE);
add_keyword(hashtable,"break",BREAK);
add_keyword(hashtable,"default",DEFAULT);
add_keyword(hashtable,"while",WHILE);
}




