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
#include "parser.h"

typedef struct nodetree node_tree;

char tokens4[115][100]={
"program","moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1","output_plist","N2","dataType","type","moduleDef","statements","statement","ioStmt","var","whichId","simpleStmt","assignmentStmt","whichStmt",
"lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional","idlist","N3","expression","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term","N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt",
"caseStmts","N9","value","default1","iterativeStmt","range","INTEGER","REAL","BOOLEAN","OF",
"ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR","FOR",
"IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF","ENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK","NUM","RNUM","ERR",
"ID","DRIVERDEF","DRIVERENDDEF","dollar","epsilon"};
 
void isnull(node_tree* root)
{
    int i,j;
    for(i=0;i<root->children;i++)
    {
        if(root->child[i]->children==1 && root->child[i]->child[0]->item==epsilon)
        {
            //free(root->child[i]);
            root->child[i]=NULL;
            for(j=i+1;j<root->children;j++)
            {
                root->child[j-1]=root->child[j];
            }
            root->child[j-1]=NULL;
            root->children-=1;
        }
    }
}

void copynode(node_tree* root,node_tree* child)
{
	//if(child==NULL)
		//printf("is null\n");
	//printf("a\n");
    int i,j,k,ll;
    root->item=child->item;
    root->tokendata=child->tokendata;
    //printf("b\n");
    for(i=0;i<root->children;i++)
    {
        if(root->child[i]==child)
        {
        	//printf("c\n");
            int start=i+1;
            int children=child->children-1;
            for(ll=root->children-1;ll>=start;ll--)
            {
                root->child[ll+children]=root->child[ll];

            }
            //printf("d\n");
            for(ll=start-1;ll<start+children;ll++)
            {

                root->child[ll]=child->child[ll-start+1];
                child->child[ll-start+1]->parent=root;
            }

            break;
            //printf("e\n");
        }
    }
    //printf("f\n");
    root->children+=child->children-1;
}

void createAST(node_tree* proot)
{
    if(proot->children>0)
    {
        int i,j;
        for(i=0;i<proot->children;i++)
        {
            createAST(proot->child[i]);
        }
    }
    //intf("%s\n",tokens4[proot->item]);
    enum tokentype x=proot->item;
    switch(x)
    {

    	case idlist:
    	
    		{
    			copynode(proot,proot->child[1]);

    		}
    		break;

    	case N3:

    		{
    			if(proot->children==3)
    			{
	    			proot->child[0]=proot->child[1];
	    			proot->child[1]=proot->child[2];
	    			proot->child[2]=NULL;
	    			proot->children-=1;
	    			isnull(proot);
	    			if(proot->child[1]!=NULL)
	    			copynode(proot,proot->child[1]);
	    			break;

	    			}
                break;	
    		}


    	case optional:

    	{
    		if(proot->children==4){
    		proot->children=1;
    		proot->child[0]=proot->child[1];
    		copynode(proot,proot->child[0]);
    		}
    	break;
    	}

    	case moduleDeclarations:
    	{

    		if(proot->children==2)
    		{
    			isnull(proot);
    			if(proot->child[1]!=NULL)
    			copynode(proot,proot->child[1]);

    		}
			break;
    	}

    	case otherModules:
    	{

    		if(proot->children==2)
    		{
    			isnull(proot);
    			if(proot->child[1]!=NULL)
    			copynode(proot,proot->child[1]);

    		}
			break;
    	}

    	case type:
    	{
    		copynode(proot,proot->child[0]);


    	}
    	break;

    	case statements:
    	{
    		if(proot->children==2)
    		{
    			isnull(proot);
    			if(proot->child[1]!=NULL)
    				copynode(proot,proot->child[1]);

    		}
    		break;

    	}
    	case input_plist:
    	{
    		proot->child[1]=proot->child[2];
    		proot->child[2]=proot->child[3];
    		proot->children-=1;
    		isnull(proot);
    		if(proot->child[2]!=NULL)
    		{
    			copynode(proot,proot->child[2]);
    		}
    		break;
    	}

    	case N1:
    	{
    		if(proot->children!=5)
    			break;
    		proot->child[0]=proot->child[1];
    		proot->child[1]=proot->child[3];
    		proot->child[2]=proot->child[4];
    		proot->child[3]=proot->child[4]=NULL;
    		proot->children-=2;
    		isnull(proot);
    		if(proot->child[2]!=NULL)
    		{
    			copynode(proot,proot->child[2]);
    		}
    		break;

    	}

    	case output_plist:
    	{
    		proot->child[1]=proot->child[2];
    		proot->child[2]=proot->child[3];
    		proot->children-=1;
    		isnull(proot);
    		if(proot->child[2]!=NULL)
    		{
    			copynode(proot,proot->child[2]);
    		}
    		break;
    	}

    	case N2:
    	{
    		if(proot->children!=5)
    			break;
    		proot->child[0]=proot->child[1];
    		proot->child[1]=proot->child[3];
    		proot->child[2]=proot->child[4];
    		proot->child[3]=proot->child[4]=NULL;
    		proot->children-=2;
    		isnull(proot);
    		if(proot->child[2]!=NULL)
    		{
    			copynode(proot,proot->child[2]);
    		}
    		break;

    	}
    	case statement:
    		{
    			copynode(proot,proot->child[0]);
    			break;
    		}
    	case simpleStmt:
    		{
    			copynode(proot,proot->child[0]);
    			break;
    		}
    	case whichStmt:
    		{
    			copynode(proot,proot->child[0]);
    			break;
    		}
    	case value:
    		{
    			copynode(proot,proot->child[0]);
    			break;
    		}

    	case ioStmt:
    		{
    			if(proot->children!=5)
    				printf("ioerror\n");
    			proot->child[1]=proot->child[2];
    			proot->child[3]=proot->child[4]=proot->child[2]=NULL;
    			proot->children-=3;
    			break;
    		}

        case arithmeticOrBooleanExpr:
            {
                
                isnull(proot);
                if(proot->children==1)
                {
                   copynode(proot,proot->child[0]);

                }
                else
                {
                    copynode(proot,proot->child[1]);
                }
            }
            break;
          case AnyTerm:
            {
                isnull(proot);
                if(proot->children==1)
                {
                   copynode(proot,proot->child[0]);

                }
                else
                {
                    copynode(proot,proot->child[1]);
                }
            }
                break;
            case arithmeticExpr:
            {
                isnull(proot);
                if(proot->children==1)
                {
                   copynode(proot,proot->child[0]);

                }
                else
                {
                    copynode(proot,proot->child[1]);
                }
            }
                break;
            
            case term:
            {
                isnull(proot);
                if(proot->children==1)
                {
                   copynode(proot,proot->child[0]);

                }
                else
                {
                    copynode(proot,proot->child[1]);
                }
                //isnull(proot);
            }
                break;
            case N7:
                {


                	isnull(proot);
                	if(proot->child[0]->item==epsilon && proot->children==1)
                		break;
                    //copynode(proot,proot->child[0]);
                    proot->tokendata=proot->child[0]->tokendata;
                    proot->item=proot->child[0]->item;
                    if(proot->children==2)
                    {
                    proot->child[0]=proot->child[1];
                    proot->child[1]=NULL;
                    proot->children-=1;
                    } 
                    else if(proot->children==3)
                    {
                    proot->child[0]=proot->child[1];
                    proot->child[1]=proot->child[2];
                    proot->child[2]=NULL;
                    proot->children-=1;
                    if(proot->child[1]->children==1&&proot->child[1]->child!=epsilon)
                    {
                        proot->child[1]->child[1]=proot->child[1]->child[0];
                        proot->child[1]->child[0]=proot->child[0];
                        proot->child[0]=proot->child[1];
                        proot->child[1]=NULL;
                        proot->child[0]->child[0]->parent=proot->child[0];
                        proot->children-=1;
                        proot->child[0]->children+=1;
                    }
                    } 
                }
                break;
            case N8:
                {
                	isnull(proot);
                	if(proot->child[0]->item==epsilon && proot->children==1)
                		break;
                    //copynode(proot,proot->child[0]);
                    proot->tokendata=proot->child[0]->tokendata;
                    proot->item=proot->child[0]->item;
                    if(proot->children==2)
                    {
                    proot->child[0]=proot->child[1];
                    proot->child[1]=NULL;
                    proot->children-=1;
                    } 
                    else if(proot->children==3)
                    {
                    proot->child[0]=proot->child[1];
                    proot->child[1]=proot->child[2];
                    proot->child[2]=NULL;
                    proot->children-=1;
                    if(proot->child[1]->children==1&&proot->child[1]->child!=epsilon)
                    {
                        proot->child[1]->child[1]=proot->child[1]->child[0];
                        proot->child[1]->child[0]=proot->child[0];
                        proot->child[0]=proot->child[1];
                        proot->child[1]=NULL;
                        proot->child[0]->child[0]->parent=proot->child[0];
                        proot->children-=1;
                        proot->child[0]->children+=1;
                    }
                    } 
                }
                break;
            case N4:
               
                {

                	isnull(proot);
                	if(proot->child[0]->item==epsilon && proot->children==1)
                		break;
                    //copynode(proot,proot->child[0]);
                    proot->tokendata=proot->child[0]->tokendata;
                    proot->item=proot->child[0]->item;
                    if(proot->children==2)
                    {
                    proot->child[0]=proot->child[1];
                    proot->child[1]=NULL;
                    proot->children-=1;
                    } 
                    else if(proot->children==3)
                    {
                    proot->child[0]=proot->child[1];
                    proot->child[1]=proot->child[2];
                    proot->child[2]=NULL;
                    proot->children-=1;
                    if(proot->child[1]->children==1&&proot->child[1]->child!=epsilon)
                    {
                        proot->child[1]->child[1]=proot->child[1]->child[0];
                        proot->child[1]->child[0]=proot->child[0];
                        proot->child[0]=proot->child[1];
                        proot->child[1]=NULL;
                        proot->child[0]->child[0]->parent=proot->child[0];
                        proot->children-=1;
                        proot->child[0]->children+=1;
                    }
                    }  
                }
                break;
            case N5:
                {  
                    isnull(proot);
                    if(proot->child[0]->item==epsilon && proot->children==1)
                    		break;
                    //copynode(proot,proot->child[0]);
                        proot->tokendata=proot->child[0]->tokendata;
                    proot->item=proot->child[0]->item;
                    if(proot->children==2)
                    {
                    proot->child[0]=proot->child[1];
                    proot->child[1]=NULL;
                    proot->children-=1;
                    } 
                    else if(proot->children==3)
                    {

                    proot->child[0]=proot->child[1];
                    proot->child[1]=proot->child[2];
                    proot->child[2]=NULL;
                    proot->children-=1;
                    if(proot->child[1]->children==1&&proot->child[1]->child!=epsilon)
                    {
                        proot->child[1]->child[1]=proot->child[1]->child[0];
                        proot->child[1]->child[0]=proot->child[0];
                        proot->child[0]=proot->child[1];
                        proot->child[1]=NULL;
                        proot->child[0]->child[0]->parent=proot->child[0];
                        proot->children-=1;
                        proot->child[0]->children+=1;
                    }

                    } 
                }
                //printf("3\n");
                break;
            case N9:
                {
                    if(proot->children==1)
                        break;
                    if(proot->child[6]->children==1)
                        proot->typeofdata=proot->child[1]->item;
                    if(((proot->child[1]->item==TRUE|| proot->child[1]->item==FALSE)&&(proot->child[6]->typeofdata==FALSE||proot->child[6]->typeofdata==TRUE))||(proot->child[1]->item==proot->child[6]->typeofdata))
                        proot->typeofdata=proot->child[1]->item;
                    else
                    {
                        printf("Case statement type mismatch as all case statement condition is not of same type at line %d\n",proot->child[1]->tokendata );
                    }
                }
                break;
            case caseStmts:
                {
                    if(proot->child[6]->children==1)
                        proot->typeofdata=proot->child[1]->item;
                    if(((proot->child[1]->item==TRUE|| proot->child[1]->item==FALSE)&&(proot->child[6]->typeofdata==FALSE||proot->child[6]->typeofdata==TRUE))||(proot->child[1]->item==proot->child[6]->typeofdata))
                        proot->typeofdata=proot->child[1]->item;
                    else
                    {
                        printf("Case statement type mismatch as all case statement condition is not of same type at line %d\n",proot->child[1]->tokendata );
                    }
                    break;
                }

            case factor:
                {
                    if(proot->children==1)
                    {
                        copynode(proot,proot->child[0]);
                    }
                    else if(proot->children==3)
                    {
                        proot->child[0]=proot->child[1];
                        proot->children=1;
                        proot->child[1]=proot->child[2]=NULL;
                        copynode(proot,proot->child[0]);
                    }
                    else printf("Factor error");
                }
                break;
            case op1:
                copynode(proot,proot->child[0]);
                break;
            case op2:
                copynode(proot,proot->child[0]);
                break;
            case relationalOp:
                copynode(proot,proot->child[0]);
                break;
            case logicalOp:
                copynode(proot,proot->child[0]);
                break;
            default:
               break;
    }
}

void printast(node_tree*  PT)
{
   //FILE* fp8=fopen(outfile,"w");
    inorderast(PT);
   // fclose(fp8);
}

void inorderast(node_tree* root )
{
	if(root==NULL)
		return;
	//("%d\n",root->item);
	//("Start-%s\n",tokens4[root->item] );
	//("Num of child = %d\n",root->children );
	if(root->item==var)
	{
		//("yay\n");
		if(root->child[1]==NULL)
        {

			//("NULL child\n");
        }
	}
	
	int i,j,k;
	if(root->children>0)
	{
		for(i=0;i<root->children;i++)
			inorderast(root->child[i]);
	}

	//("End-%s\n",tokens4[root->item] );	

}

void printasttree(node_tree* ptr, FILE* fp )
{
		//f//(fp,"IN ASTFUNC\n");
		int len; int lallu;
    if(ptr==NULL)
        return;

 	numofastnodes++; 
    //("ast-----------%s\n",tokens4[ptr->item]);
      printasttree(ptr->child[0],fp);
    	
    if(ptr->item==epsilon)
 	{   	
 		printf( "epsilon\n" );
 		return;
	}
     if(ptr->item>=INTEGER)
     {
            //printf("%s\n",tokens[ptr->item]);
            //printf("baccha-%d\n",baccha_number);
            printf("%s ",ptr->tokendata->value);
            len=18-strlen(ptr->tokendata->value);
     	
     	  	for(lallu=0;lallu<len;lallu++)
       			printf("-");
       	
       		printf(" ");

/************************************************/

            printf("%d ",ptr->tokendata->line);
            len=14;
       	
       		for(lallu=0;lallu<len;lallu++)
       			printf("-");
       	
       		printf(" ");

/**********************************************/

            printf("%s ",tokens4[ptr->item]);
			len=18-strlen(tokens4[ptr->item]);
       	
       		for(lallu=0;lallu<len;lallu++)
       			printf("-");
       	
       		printf(" ");
            if(ptr->item==NUM || ptr->item==RNUM)
            {
                printf("%s ",ptr->tokendata->value);
                len=18-strlen(ptr->tokendata->value);
       	
       			for(lallu=0;lallu<len;lallu++)
       				printf("-");
       	
       			printf(" ");
            }
            else
                 printf("------------------ ");

            printf("%s ",tokens4[ptr->parent->item]);
            len=18-strlen(tokens4[ptr->parent->item]);
       	
       		for(lallu=0;lallu<len;lallu++)
       			printf("-");
       	
       		printf(" ");
            printf("--------Yes------- ");
            printf("------------------");

            //printf("childno-%d ",ptr->children);
            int v;
            /*for(v=0;v<3;v++)
           {
                if(ptr->child[v]!=NULL && ptr->child[v]->item==var)
                    printf( "var-%s ",ptr->child[v]->child[0]->tokendata->value );
                else if(ptr->child[v]!=NULL)
                    printf("c%d-%s ",v+1,tokens4[ptr->child[v]->item] );
            }**/
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
        		printf("%s ",tokens4[ptr->parent->item]);
    			len=18-strlen(tokens4[ptr->parent->item]);
       	
       			for(lallu=0;lallu<len;lallu++)
       				printf("-");
       	
       			printf(" ");
       }
        
       printf("-------No--------- ");
       printf("%s ",tokens4[ptr->item]);
       len=18-strlen(tokens4[ptr->item]);
       	for(lallu=0;lallu<len;lallu++)
       		printf("-");

       printf(" ");

           // printf("childno-%d ",ptr->children);
            int v;
           /* for(v=0;v<3;v++)
            {
                if(ptr->child[v]!=NULL && ptr->child[v]->item==var && ptr->child[v]->tokendata!=NULL)
                    printf( "var-%s ",ptr->child[v]->child[0]->tokendata->value );
                else if(ptr->child[v]!=NULL)
                    printf("c%d-%s ",v+1,tokens4[ptr->child[v]->item] );
            }*/
       printf("\n");
     }

    int i;
    for(i=1;i<ptr->children;i++)
    {
    printasttree(ptr->child[i],fp);
    }

}

