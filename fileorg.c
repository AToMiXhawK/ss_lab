#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t rawtime;

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
        printf("root");
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
		printf("Created on: %s\n",asctime(N->ptm));
	}
	else
	{
		printf("Node type: File\n");
	}
}

void create_subdir(struct node *Parent)
{
    if(Parent->type!="d")
    { printf("Parent not a directory\n"); return; }
	struct node *new = (struct node*) malloc(sizeof(struct node*)) ;
	new->parent = Parent;
	new->type = "d";
	printf("Enter the name for new directory: ");
	scanf("%s",new->dir.dirname);
	new->dir.pem= "rw-";
	time_t rawtime = time(NULL);
	new->ptm = localtime(&rawtime);
	new->child_count=0;
	Parent->childs[Parent->child_count++] = new;
}

int main()
{
	struct node *pwd = (struct node*) malloc(sizeof(struct node*)) ;
	init_root(&root);
	pwd = &root;
	fetchppt(pwd);
	create_subdir(pwd);
	fetchppt(pwd->childs[0]);
    create_subdir(pwd->childs[0]);
    fetchppt(pwd->childs[0]->childs[0]);
}
