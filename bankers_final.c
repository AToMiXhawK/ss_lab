#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#define rnd(ll,ul) ((rand() % (ul - ll + 1)) + ll)          // function to generate a random number between ll and ul
#define red() (printf("\033[0;31m"))                        //  
#define yellow() (printf("\033[0;33m"))                     //
#define green() (printf("\033[0;32m"))                      //
#define blue() (printf("\033[0;34m"))                       //      For Color output in terminal
#define cyan() (printf("\033[0;36m"))                       //
#define magenta() (printf("\033[0;35m"))                    //
#define reset() (printf("\033[0m"))                         //

struct Process                                              // structure representing a process
{
     int p_id;
     int alloc[3];
     int need[3];
     int max[3];
};

struct Resource                                             // structure representing a resource
{
    int r_id;
    int max;
    int avail;
};

struct State                                                // structure represneting current state
{
    struct Process P[7];
    struct Resource R[3];
}current, previous;

void print_state(struct State *current, int no_resource, int no_process)            // function to print a state
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

void init_state(struct State *current, int no_resource, int no_process)             // function to initialize the state at start of program
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


int safety(struct State *S, int r, int p)                      // function implementing the safety algorithm
{
    int finish[p], seq[p], work[r], s=0;
    
    for(int i=0; i<p; i++)
        finish[i]=0;                                          // initialize finish[] 0==False 1==True

    printf("\navail = work: [");
    magenta();
    for(int i=0; i<r; i++)
    {
        work[i] = S->R[i].avail;                             // to initialize work[]
        printf(" %d ",work[i]);
    }
    reset();
    printf("]\n");
    
    int l = 0;
    while(1<p)
    {
        int flag1 = 0;
        for(int i=0; i<p; i++)
        {
            int flag2 = 0;
            if(finish[i]==0)
            {
                
                for(int j=0; j<r; j++)
                {
                    if(S->P[i].need[j]>work[j])                                                  // check need[i] <= work
                    {
                        flag2 = 1;
                        break;
                    }
                }
            }  
            if(flag2 == 1)
            {
                flag1 = 1;
                continue;
            }
            else if(finish[i]==0)
            {
                finish[i] = 1;                                                               // set finish[i] = True
                printf("After\033[0;32m P%d\033[0m, work: [\033[0;35m",S->P[i].p_id);
                for(int k=0; k<r; k++)
                {
                    work[k] += S->P[i].alloc[k];                                            // work += allocation[i]
                    printf(" %d ",work[k]);
                }
                printf("\033[0m]");
                printf("\tfinish: [\033[0;33m");
                for(int k=0; k<p; k++)
                {
                    if(k==i)
                        blue();
                    printf(" %d ",finish[k]);
                    if(k==i)
                        yellow();
                }
                printf("\033[0m]\n");
                seq[s] = S->P[i].p_id;
                s++; 
            }
            
        }
        if(flag1==0)
            break;
        
        l++;
        if(l==p)
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

void request(struct State *C, struct State *P, int r, int p)                                       // function to implement resource request
{
    *P = *C;
    int pid, req[r];
    char fl;
    blue();
    printf("\nEnter process id for resource request: ");
    green(); printf("P");
    scanf("%d",&pid);
    reset();
    if(pid<=0 || pid>p)
    { red(); printf("\nInvalid process id!\n"); reset(); return; }
    blue();
    printf("\nEnter the request for \033[0;32mP%d:\033[0m ",pid);
    red();
    for(int i=0; i<r; i++)
        scanf("%d",&req[i]);
    reset();
    pid--;                                                                                            // To convert to absolute indexing

    for(int j=0; j<r; j++)
    {
        if(req[j]>C->P[pid].need[j])                                                                   // check request <= need[i]
        { red(); printf("\nrequest > need, Allocation not possible\n"); return; }               

        if(req[j]>C->R[j].avail)                                                                      // check request <= available
        { red(); printf("\nrequest > resource available, Allocation not possible\n"); return; }
    }

    for(int j=0; j<r; j++)
    {
        C->R[j].avail -= req[j];                                                                     // available -= request
        C->P[pid].alloc[j] += req[j];                                                                // allocation[i] += request
        C->P[pid].need[j] -= req[j];                                                                 // need[i] += request
    }

    blue(); printf("\nNew State"); reset();
    print_state(C,r,p);

    blue(); printf("\nChecking Safety algorithm for the request\n"); reset();
    int s = safety(C,r,p);                                                                           // check safety algorithm

    if(s == 0)
    {
        red(); printf("\nSafety check failed, reverting to previous state!\n"); reset();
        *C = *P;
    }
    
    green();
    printf("\nResource avail: [");
    for(int i=0; i<r; i++)
        printf(" %d ",C->R[i].avail );
    printf("]\n");
    reset();

}

int main()                                                  // main function
{
    srand(time(0));
    const int no_process = rnd(3,7);
    const int no_resource = rnd(2,3);

    init_state(&current,no_resource,no_process);
    safety(&current,no_resource,no_process);

    char ch, fl;
    while(1)
    {
        green();
        printf("\nRequest Resource? (y/n): ");
        yellow();
        scanf("%c",&ch);
        scanf("%c",&fl);
        reset();
        if(ch=='y')
        {
            request(&current,&previous,no_resource,no_process);
        }
        else if(ch=='n')
        { red(); printf("\nQuit!\n"); return 0; }
        else
        { red(); printf("\nInvalid Input!!\n"); reset(); }
         scanf("%c",&fl);
    }

}