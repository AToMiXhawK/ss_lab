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
  struct node *childs;
  int child_count;
  struct node *parent;
}root;

void init_root(struct node *root)
{
    root->type = "d";
    root->dir.dirname = "/";
    root->dir.pem= "rw-";
    time_t rawtime = time(NULL);
    root->ptm = localtime(&rawtime);
    root->parent=NULL;
    root->childs=NULL;
    root->child_count=0;
}

void fetchppt(struct node *N)
{
    if(N->type=="d")
    {
        printf("Node type: Directory\n");
        printf("Directory name: %s\n",N->dir.dirname);
        printf("Permissions: %s\n",N->dir.pem);
        printf("Created on: %s\n",asctime(N->ptm));
    }
    else
    {
        printf("Node type: File\n");
    }
}

void create_subdir(struct node *Parent)
{
    struct node *new = (struct node*) malloc(sizeof(struct node*)) ;
    new->parent = Parent;
    new->type = "d";
    new->dir.dirname = "New Folder";
    new->dir.pem= "rw-";
    time_t rawtime = time(NULL);
    new->ptm = localtime(&rawtime);
    new->childs=NULL;
    new->child_count=0;
    Parent->childs = new;
}

int main()
{
    struct node *pwd = (struct node*) malloc(sizeof(struct node*)) ;
    init_root(&root);
    pwd = &root;
    fetchppt(pwd);
    create_subdir(pwd);
    fetchppt(pwd->childs);
}
