#include<stdio.h>
#include <stdlib.h>
#include<time.h>

int main()
{
    srand(time(0));
    const int no_process = rand()%5 + 1;
    const int no_resource = rand()%5 + 1;

    struct Process
    {
         int p_id;
         int alloc;
         int need;
         int max;
    };

    struct Resource
    {
        int r_id;
        int max;
        int avail;
    };

    struct State
    {
        struct Process P[no_process];
        struct Resource R[no_resource];

    }current, previous;

    for(int i=0; i<no_process; i++)
    {
        current.P[i].p_id = i+1;

    }

}