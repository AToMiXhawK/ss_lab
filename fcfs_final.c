#include <stdio.h>
#include <stdlib.h>
#include<time.h> 

struct Process
{
    int pno;
    int arrival;
    int burst;
    int turn;
    int wait;
}P[20];

void swap(struct Process *p1, struct Process *p2)
{
    struct Process tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void sorting(int n)
{
    for(int i=0;i<n-1;i++)
        for (int j=0;j<n-i-1;j++)
            if(P[j].arrival > P[j+1].arrival)
                swap(&P[j], &P[j+1]);
}

void waiting(int n)
{
    float wavg=0.0, time= P[0].arrival + P[0].burst;
    P[0].wait=0;
    P[0].turn=P[0].burst;
    float tavg= P[0].turn;

    for(int i=1;i<n;i++)
    {
        P[i].wait= time - P[i].arrival;
        if(P[i].wait<0)
        {
            time = time - P[i].wait + P[i].burst;
            P[i].wait=0;
            P[i].turn = P[i].burst;
        }
        else
        {
            time += P[i].burst; 
            P[i].turn = time - P[i].arrival;
        }
            
        wavg += P[i].wait;
        tavg += P[i].turn;
        
        
    }

    printf("\nProcess\t    Burst Time\t Arrival Time\t Waiting Time\t Turnaround Time\n");
    for(int i=0;i<n;i++)
	{
		printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t%d\n",P[i].pno,P[i].burst,P[i].arrival,P[i].wait,P[i].turn);	
	}

    printf("\nAverage waiting time: %f", wavg/n);
    printf("\nAverage turnaround time: %f", tavg/n);
}


int main()
{
    int n;
    char ch, fl;
    printf("Continue with random input? (y/n): ");
    scanf("%c",&ch);
    scanf("%c",&fl);
    if(ch=='y')
    {
        printf("continuing with random inputs");
        srand(time(0));
        n = rand()%10 + 1;
        for (int i=0; i<n; i++)
        {
            P[i].pno=i+1;
            P[i].burst = rand()%10 + 1;
            P[i].arrival = rand()%10 + 1;
        }
    }
    else if(ch=='n')
    {
        printf("Enter no of processes: ");
        scanf("%d", &n);
        printf("Enter values: ");
        for (int i=0; i<n; i++)
        {
            P[i].pno=i+1;
            printf("P[%d]: ", i);
            printf("Burst time: ");
            scanf("%d", &P[i].burst);
            printf("Arrival time: ");
            scanf("%d", &P[i].arrival);
        }
    }
    else {printf("Invalid Input\n"); return 0;}

    sorting(n);
    waiting(n);
    printf("\n");
    return 0;
}
