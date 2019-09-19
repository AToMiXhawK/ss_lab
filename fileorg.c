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

struct node
{
    char *type;
    char name[32];
    char *pem;
    struct tm *ptm;
	int child_count;
	struct node *parent;
	struct node *childs[32];
}root;

void init_root(struct node *root)
{
	root->type = "d";
	strcpy(root->name,"/");
	root->pem= "rw-";
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
            tree[i] = t->name;
        else
            tree[i] - t->name;
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
		printf("Directory name: %s\n",N->name);
        printf("Location: ");
        fetchloc(N);
		printf("\nPermissions: %s\n",N->pem);
		printf("Created on: %s",asctime(N->ptm));
		printf("No of Childs: %d",N->child_count);
	}
	else
	{
		printf("Node type: File %c\n",*N->type);
	}
}

struct node* mkdir(struct node *Parent)
{
    if(Parent->type!="d")
    { printf("Parent not a directory\n"); return NULL; }
	struct node* new = (struct node*) malloc(sizeof(struct node)) ;
	new->parent = Parent;
	new->type = "d";
	char name[20];
	printf("Enter the name for new directory: ");
	scanf("%s",name);
	strcpy(new->name,name);
    new->pem = Parent->pem;
	time_t rawtime = time(NULL);
	new->ptm = localtime(&rawtime);
	new->child_count=0;
	Parent->childs[Parent->child_count] = new;
    Parent->child_count++;
	printf("New directory created: %s\n",new->name);
    return new;
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
		{ green(); printf("%s\t",pwd->childs[i]->name); reset(); }

		else
		{ printf("%s\t",pwd->childs[i]->name); }
	}
}

int main()
{
	struct node* pwd = (struct node*) malloc(sizeof(struct node)) ;
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