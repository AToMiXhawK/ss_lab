#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define red() (printf("\033[0;31m"))                        //  
#define yellow() (printf("\033[0;33m"))                     //
#define green() (printf("\033[0;32m"))                      //
#define blue() (printf("\033[0;34m"))                       //      For Color output in terminal
#define cyan() (printf("\033[0;36m"))                       //
#define magenta() (printf("\033[0;35m"))                    //
#define reset() (printf("\033[0m"))     
//#include "hawk.h"

struct directory
{
	char* pem;
	char* dirname;
};

struct file
{
	char *pem;
	char *filename;
	char *data;
};

struct node                             
{
	char *type;
	struct directory dir;
	struct file file;
	struct tm *ptm;
	int child_count;
	struct node *parent;
	struct node *childs[];
}root;

void init_root(struct node *root)
{
	root->type = "d";
	root->dir.dirname = "/";
	root->dir.pem= "rw-";
	time_t rawtime = time(NULL);
	root->ptm = localtime(&rawtime);
	root->parent=NULL;
	root->child_count=0;
}

void fetchloc(struct node *N)
{
	struct node *t = N;
    char *tree[20]; int i=0;
	while(1)
	{
        if(t->type == "d")
            tree[i] = t->dir.dirname;
        else
            tree[i] - t->file.filename;
        t = t->parent;
        if(t==NULL) { break; }
        i++;
		
	}
    for(int j=i-1;j>=0;j--)
		printf("/%s",tree[j]);
    
    if(i==0)
        printf("/");
}

void fetchppt(struct node *N)
{
	if(N->type=="d")
	{
		printf("Node type: Directory\n");
		printf("Directory name: %s\n",N->dir.dirname);
        printf("Location: ");
        fetchloc(N);
		printf("\nPermissions: %s\n",N->dir.pem);
		printf("Created on: %s",asctime(N->ptm));
		printf("No of Childs: %d",N->child_count);
	}
	else
	{
		printf("Node type: File\n");
	}
}

void mkdir(struct node *Parent)
{
    if(Parent->type!="d")
    { printf("Parent not a directory\n"); return; }
	struct node *new = (struct node*) malloc(sizeof(struct node*)) ;
	new->parent = Parent;
	new->type = "d";
	char name[20];
	printf("Enter the name for new directory: ");
	scanf("%s",name);
	strcpy(new->dir.dirname,name);
	time_t rawtime = time(NULL);
	new->ptm = localtime(&rawtime);
	new->child_count=0;
	Parent->childs[Parent->child_count++] = new;
	printf("New directory created: %s\n",new->dir.dirname);
}

void ls(struct node *pwd)
{
	if(pwd->type!="d")
    { red(); printf("Parent not a directory"); reset(); return; }
	if(pwd->child_count == 0)
	{ red(); printf("Empty directory"); reset(); return; }

	for(int i=0; i<pwd->child_count; i++)
	{
		if(pwd->childs[i]->type == "d")
		{ green(); printf("%s\t",pwd->childs[i]->dir.dirname); reset(); }

		else
		{ printf("%s\t",pwd->childs[i]->file.filename); }
	}
}

int main()
{
	struct node *pwd = (struct node*) malloc(sizeof(struct node*)) ;
	init_root(&root);
	pwd = &root;
	printf("Root Directory Initialized\n");
	fetchppt(pwd);
	char ch, *cmd;
    while(1)
    {
        blue();
        printf("\n> ");
		reset();
        scanf("%s",cmd);
		if(strcmp(cmd,"ls") == 0)	
			ls(pwd);
		else if(strcmp(cmd,"mkdir") == 0)
			mkdir(pwd);
		else if(strcmp(cmd,"pwd") == 0)
			fetchloc(pwd);
		else if(strcmp(cmd,"info") == 0)
			fetchppt(pwd);
		else if(strcmp(cmd,"quit") == 0)
			break;
		else if(strcmp(cmd,"exit") == 0)
			break;
		else
			printf("Invalid Command\n");
		scanf("%c",&ch);
		printf("\n");	
	}
}
