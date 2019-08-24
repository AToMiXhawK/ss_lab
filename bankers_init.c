#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#define rnd(ll,ul) ((rand() % (ul - ll + 1)) + ll)
#define red() (printf("\033[0;31m"))
#define yellow() (printf("\033[0;33m"))
#define green() (printf("\033[0;32m"))
#define blue() (printf("\033[0;34m"))
#define cyan() (printf("\033[0;36m"))
#define reset() (printf("\033[0m"))

struct Process
{
     int p_id;
     int alloc[3];
     int need[3];
     int max[3];
};

struct Resource
{
    int r_id;
    int max;
    int avail;
};

struct State
{
    struct Process P[7];
    struct Resource R[3];
}current, previous;

void print_state(struct State *current, int no_resource, int no_process)
{
    printf("\n\n\033[0;32mProcess\t\t\033[0;34m Allocation\t\033[0;31m   Max\t\t\033[0;33m  Need\n");

    for(int i=0; i<no_process; i++)
    {
        green();
        printf("P%d\t\t",current->P[i].p_id);
        blue();

        for(int j=0; j<no_resource; j++)
        {
            printf(" %d  ",current->P[i].alloc[j]);
        }

        printf("\t");
        red();
        for(int j=0; j<no_resource; j++)
        {
            printf(" %d  ",current->P[i].max[j]);
        }

        printf("\t");
        yellow();
        for(int j=0; j<no_resource; j++)
        {
            printf(" %d  ",current->P[i].need[j]);
        }

        reset();
        printf("\n");
    }
}

void init_state(struct State *current, int no_resource, int no_process)
{
    red();
    printf("\nNo of Resources = %d",no_resource);
    green();
    printf("\nNo of Processes = %d",no_process);
    reset();

    for(int i=0; i<no_resource; i++)
    {
        current->R[i].r_id = i+1;
        current->R[i].max = rnd(10,20);
        current->R[i].avail = current->R[i].max;
    }

    for(int i=0; i<no_process; i++)
    {
        current->P[i].p_id = i+1;
        for(int j=0; j<no_resource; j++)
        {
            current->P[i].max[j] = rnd(0,current->R[j].avail);
            current->P[i].alloc[j] = rnd(0, current->P[i].max[j]);
            current->P[i].need[j] = current->P[i].max[j] - current->P[i].alloc[j];
            current->R[j].avail -= current->P[i].alloc[j];
        }
    }

    print_state(current,no_resource,no_process);
    red();
    printf("\nResource max: [");
    for(int i=0; i<no_resource; i++)
        printf(" %d ",current->R[i].max );
    printf("]");
    green();
    printf("\nResource avail: [");
    for(int i=0; i<no_resource; i++)
        printf(" %d ",current->R[i].avail );
    printf("]\n");
    reset();
}


int safety(struct State *S, int r, int p)
{
    int finish[p], seq[p], work[r], s=0;
    
    for(int i=0; i<p; i++)
        finish[i]=0;

    printf("work: [");
    for(int i=0; i<r; i++)
    {
        work[i] = S->R[i].avail;
        printf(" %d ",work[i]);
    }
    printf("]\n");
    
    while(1)
    {
        int flag1 = 0;
        for(int i=0; i<p; i++)
        {
            int flag2 = 0;
            if(finish[i]==0)
            {
                
                for(int j=0; j<r; j++)
                {
                    if(S->P[i].need[j]>work[j])
                    {
                        flag2 = 1;
                        break;
                    }
                }
            }///////////////////    
            if(flag2 == 1)
            {
                flag1 = 1;
                continue;
            }
            else if(finish[i]==0)
            {
                finish[i] = 1;
                printf("After P%d, work: [",S->P[i].p_id);
                for(int k=0; k<r; k++)
                {
                    work[k] += S->P[i].alloc[k];
                    printf(" %d ",work[k]);
                }
                printf("]");
                printf("\tfinish: [");
                for(int k=0; k<p; k++)
                    printf(" %d ",finish[k]);
                printf("]\n");
                seq[s] = S->P[i].p_id;
                s++; 
            }
            
        }
        if(flag1==0)
            break;
    }

    for(int i=0; i<p; i++)
        if(finish[i]==0)
        {
            red();
            printf("\nSafety check failed!!!\n");
            reset();
            return 0;
        }
    
    green();
    printf("\nSafety check Passed :-)\n");
    cyan();
    printf("Safe sequence: <");
    for(int i=0; i<p; i++)
        printf(" %d ",seq[i]);
    printf(">\n");
    reset();
    return 1;
}


int main()
{
    srand(time(0));
    const int no_process = rnd(3,7);
    const int no_resource = rnd(2,3);

    init_state(&current,no_resource,no_process);
    //print_state(&current,no_resource,no_process);
    safety(&current,no_resource,no_process);

}