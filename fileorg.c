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
	char *data;
	char name[32];
	char pem[3];
	struct tm *ptm;
	int child_count;
	struct node *parent;
	struct node *childs[32];
}root;

void init_root(struct node *root)
{
	root->type = "d";
	strcpy(root->name,"/");
	strcpy(root->pem,"rw-");
	time_t rawtime = time(NULL);
	root->ptm = localtime(&rawtime);
	root->parent=NULL;
	root->child_count=0;
    root->data=NULL;
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

void fetchppt(struct node *pwd)
{
	struct node* N = (struct node*) malloc(sizeof(struct node)) ;
	int f=0;
	char name[32];
	scanf("%s",name);

	if(strcmp(name,".") == 0)
	{ N = pwd; f=1; }

	for(int i=0; i<pwd->child_count; i++)
		if(strcmp(name,pwd->childs[i]->name) == 0)
			{ N = pwd->childs[i]; f=1;  break; }

	if(f==0)
	{ printf("%s not found",name); return; }

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
	printf("\n");
}

struct node* mkdir(struct node *Parent)
{
	if(Parent->type!="d")
	{ printf("Parent not a directory\n"); return NULL; }
	char name[32];
	//printf("Enter the name for new directory: ");
	scanf("%s",name);
	for(int i=0; i<Parent->child_count; i++)
		if(strcmp(name,Parent->childs[i]->name) == 0)
			if(Parent->childs[i]->type == "d")
			{ printf("%s: Directory already exixts!\n",name); return NULL; }
	
	struct node* new = (struct node*) malloc(sizeof(struct node)) ;
	strcpy(new->name,name);
	strcpy(new->pem,Parent->pem);
	new->parent = Parent;
	new->type = "d";
	time_t rawtime = time(NULL);
	new->ptm = localtime(&rawtime);
	new->child_count=0;
	Parent->childs[Parent->child_count] = new;
	Parent->child_count++;
	//printf("New directory created: %s",new->name);
	new->data = NULL;
	return new;
}

void rmdir(struct node *pwd)
{
	if(pwd->type!="d")
	{ red(); printf("Parent not a directory"); reset(); return; }
	if(pwd->child_count == 0)
	{ red(); printf("Empty directory"); reset(); return; }

	char name[32];
	//printf("Enter the name of directory: ");
	scanf("%s",name);

	for(int i=0; i<pwd->child_count; i++)
	{
		if(strcmp(name,pwd->childs[i]->name) == 0)
		{
			if(pwd->childs[i]->type == "d")
			{ 
					for(int j=i; j<pwd->child_count; j++)
					pwd->childs[j] = pwd->childs[j+1];
					pwd->child_count--;
					free(pwd->childs[pwd->child_count]); 
					pwd->childs[pwd->child_count] = NULL;
					return; 
			}

			else
			{ printf("%s not a Directory",name); return; }
		}
	}

	printf("%s not found",name);
	return;
}

void ls(struct node *pwd)
{
	if(pwd->type!="d")
	{ red(); printf("Parent not a directory\n"); reset(); return; }
	if(pwd->child_count == 0)
	{ red(); printf("Empty directory\n"); reset(); return; }

	for(int i=0; i<pwd->child_count; i++)
	{
		if(pwd->childs[i]->type == "d")
		{ green(); printf("%s\t",pwd->childs[i]->name); reset(); }

		else
		{ printf("%s\t",pwd->childs[i]->name); }
	}
	printf("\n");
}

struct node* cd(struct node *pwd, struct node *rt)
{
	if(pwd->type!="d")
	{ red(); printf("Parent not a directory"); reset(); return pwd; }

	char name[32];
	//printf("Enter the name of directory: ");
	scanf("%s",name);

	if(strcmp(name,"..") == 0)
	return pwd->parent;

	if(strcmp(name,"/") == 0)
	return rt;

	for(int i=0; i<pwd->child_count; i++)
	{
		if(strcmp(name,pwd->childs[i]->name) == 0)
		{
			if(pwd->childs[i]->type == "d")
			return pwd->childs[i];

			else
			{ printf("%s not a Directory",name); return pwd; }
		}
	}

	printf("%s not found",name);
	return NULL;
}

void chmod(struct node *pwd)
{
	char name[32], pem[3];
	scanf("%s",name);
	scanf("%s",pem);

	if(strcmp(name,".") == 0)
	{ strcpy(pwd->pem,pem); return; }

	for(int i=0; i<pwd->child_count; i++)
		if(strcmp(name,pwd->childs[i]->name) == 0)
			{ strcpy(pwd->childs[i]->pem,pem); return; }

	printf("%s not found",name);
	return;

}

int count=0;
void print_tree(struct node *N)
{
	char *s="|-----",*s1="|     ";
	printf("\n");
	for(int j=0;j<(count-1);j++)
		printf("%s",s1);
	if(count>0)
		printf("%s",s);
    
	printf("%s",N->name);
	for(int i=0; i<N->child_count; i++)
	{
		count++;
		print_tree(N->childs[i]);
		count--;
	}	
}

void tree(struct node *pwd)
{
	struct node* N = (struct node*) malloc(sizeof(struct node)) ;
	int f=0;
	char name[32];
	scanf("%s",name);

	if(strcmp(name,".") == 0)
	{ N = pwd; f=1; }

	for(int i=0; i<pwd->child_count; i++)
		if(strcmp(name,pwd->childs[i]->name) == 0)
			{ N = pwd->childs[i]; f=1;  break; }

	if(f==0)
	{ printf("%s not found",name); return; }

	print_tree(N);
	printf("\n");
}

struct node* touch(struct node *Parent)
{
	if(Parent->type!="d")
	{ printf("Parent not a directory\n"); return NULL; }
	char name[32], data[128];
	scanf("%s",name);
	for(int i=0; i<Parent->child_count; i++)
		if(strcmp(name,Parent->childs[i]->name) == 0)
			if(Parent->childs[i]->type == "f")
			{ printf("%s: File already exixts!\n",name); return NULL; }
	
	struct node* new = (struct node*) malloc(sizeof(struct node)) ;
	new->parent = Parent;
	new->type = "f";
	strcpy(new->name,name);
	//scanf("%s",data);
	fgets(data, 32, stdin);
	strcpy(new->data,data);
	strcpy(new->pem,Parent->pem);
	time_t rawtime = time(NULL);
	new->ptm = localtime(&rawtime);
	new->child_count=0;
	Parent->childs[Parent->child_count] = new;
	Parent->child_count++;
	printf("New file created %s, %s",new->name,new->data);
	return new;
}

void cat(struct node *pwd)
{
	char name[32];
	scanf("%s",name);

	if(strcmp(name,".") == 0)
	{ printf("Invalid filename"); return; }

	for(int i=0; i<pwd->child_count; i++)
		if(strcmp(name,pwd->childs[i]->name) == 0)
			{ printf("%s",pwd->childs[i]->data); return; }

	printf("%s not found",name);
	return;
}

void help()
{
	green(); printf("File Organization implementation\n\n");
	blue(); printf("Available Commands:");
	cyan(); printf("\npwd: "); reset(); printf("\tTo print location of present working directory");
	cyan(); printf("\nls: "); reset(); printf("\tTo print contents of pwd");
	cyan(); printf("\ninfo: "); reset(); printf("\tTo print properties of given node"); red(); printf("\t\tUsage: "); cyan(); printf("info <nodename>");
	cyan(); printf("\ntree: "); reset(); printf("\tTo print tree structure of given node"); red(); printf("\t\tUsage: "); cyan(); printf("tree <nodename>");
	cyan(); printf("\nmkdir: "); reset(); printf("\tTo create new directory in pwd"); red(); printf("\t\t\tUsage: "); cyan(); printf("mkdir <dirname>");
	cyan(); printf("\nrmdir: "); reset(); printf("\tTo remove directory in pwd"); red(); printf("\t\t\tUsage: "); cyan(); printf("rmdir <dirname>");
	cyan(); printf("\ntouch: "); reset(); printf("\tTo create new file in pwd"); red(); printf("\t\t\tUsage: "); cyan(); printf("touch <filename> <enter> <data>");
	cyan(); printf("\ncat: "); reset(); printf("\tTo print data in a file"); red(); printf("\t\t\t\tUsage: "); cyan(); printf("cat <filename>");
	cyan(); printf("\nchmod: "); reset(); printf("\tTo change permissions of a node in pwd"); red(); printf("\t\tUsage: "); cyan(); printf("chmod <nodename> <pem>");
	cyan(); printf("\nquit: "); reset(); printf("\tQuit the program");
	blue(); printf("\n\nNote: "); reset(); printf("use \'.\' to pass pwd as nodename argument");
	printf("\n");
}

int main()
{
	struct node* rt = (struct node*) malloc(sizeof(struct node)) ;
	struct node* pwd = (struct node*) malloc(sizeof(struct node)) ;
	init_root(&root);
	rt = &root;
	pwd = rt;
	printf("Root Directory Initialized\n");
	//fetchppt(pwd);
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
		else if(strcmp(cmd,"rmdir") == 0)
			rmdir(pwd);
		else if(strcmp(cmd,"touch") == 0)
			touch(pwd);
		else if(strcmp(cmd,"cat") == 0)
			cat(pwd);
		else if(strcmp(cmd,"pwd") == 0)
			fetchloc(pwd);
		else if(strcmp(cmd,"info") == 0)
			fetchppt(pwd);
		else if(strcmp(cmd,"chmod") == 0)
			chmod(pwd);
		else if(strcmp(cmd,"cd") == 0)
			pwd = cd(pwd,rt);
		else if(strcmp(cmd,"tree") == 0)
			tree(pwd);
		else if(strcmp(cmd,"help") == 0)
			help();
		else if(strcmp(cmd,"quit") == 0)
			break;
		else if(strcmp(cmd,"exit") == 0)
			break;
		else
			printf("Invalid Command\n");
		scanf("%c",&ch);
		//printf("\n");	
	}
}

