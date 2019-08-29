#include <stdio.h>
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
  struct Node *next[];
}root;

void init_root(struct node *root)
{
    root->type = "d";
    root->dir.dirname = "/";
    root->dir.pem= "r--";
    time_t rawtime = time(NULL);
    root->ptm = localtime(&rawtime);
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

int main()
{
    init_root(&root);
    fetchppt(&root);
}
