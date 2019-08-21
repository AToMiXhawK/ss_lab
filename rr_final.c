#include <stdio.h>
#include <stdlib.h>
#include<time.h> 

struct Process
{
    int pno;
    int arrival;
    int burst;
    float burst_complete;
    float burst_remain;
    float last_time;
    int turn;
    int wait;
    int done;
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

void waiting(int n, float quantum, char opt)
{
    float wavg=0.0, tavg=0.0, time = P[0].arrival, total_burst;
    
    for(int i=0;i<n;i++)
    {
        total_burst += P[i].burst;
        P[i].burst_remain = P[i].burst;
        P[i].burst_complete = 0;
        P[i].wait = 0;
        P[i].last_time = 0;
        P[i].done = 0;
    }
    if(opt=='y')
                printf("\n\nOutput:\nProcess\t    Burst Time Completed\t Burst Time Remaining\t Time Elapsed\n");

    while(1)
    {
        int flag = 0, flag2=0;
        for(int i=0;i<n;i++)
        {
            if(P[i].done==0)
            {
                if(flag2!=0)
                    time += 1;
                if(P[i].arrival<=time)
                {
                    if(P[i].burst_remain<=quantum)
                    {
                        if(P[i].last_time==0)
                        {
                            P[i].wait = time - P[i].arrival;
                        }
                        else
                            P[i].wait += (time - P[i].last_time);

                        time += P[i].burst_remain;
                        P[i].burst_complete += P[i].burst_remain;
                        P[i].burst_remain = 0;
                        P[i].turn = time - P[i].arrival;
                        P[i].last_time = time;
                        P[i].done = 1;
                    }
                    else
                    {
                        if(P[i].last_time==0)
                        {
                            P[i].wait = time - P[i].arrival;
                        }
                        else
                            P[i].wait += (time - P[i].last_time);
                        time += quantum;
                        P[i].burst_complete += quantum;
                        P[i].burst_remain -= quantum;
                        P[i].last_time = time;
                        
                    }

                    if(opt=='y')
                        printf("\nP%d\t\t%f\t\t\t%f\t   %f\n",P[i].pno,P[i].burst_complete,P[i].burst_remain,time);
                }
                else
                {
                    flag2++;
                    continue;
                }
            }
            else
            {
                flag++;
                continue;
            }
        }
        if(flag==n)
            break;
    }

    int err = 0;
    for(int i=0;i<n;i++)
    {
        wavg += P[i].wait;
        tavg += P[i].turn;
        
        if(P[i].burst!=P[i].burst_complete)                                                //
        {                                                                                  //   Some Error checks
            printf("\nBurst integrity failed for P%d",P[i].pno);                           //   Not Necessary
            err++;                                                                         //
        }                                                                                  //
    }

    if(err==0)                                                                              //
        printf("\nIndividual burst time of each process integral");                         //
    else                                                                                    //
        printf("\nIndividual burst time integrity failed for %d processes",err);            //  Some Error checks
    if(total_burst=time-P[0].arrival)                                                       //  Not Necessary
        printf("\nTotal burst time integrity check passed\n");                              //
    else                                                                                    //
        printf("\nTotal burst time integrity check failed\n");                              //

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
    char ch, fl, opt;
    float quantum = 5;
    printf("Continue with random input? (y/n): ");
    scanf("%c",&ch);
    scanf("%c",&fl);
    printf("Do you want to print the sequence? (y/n): ");
    scanf("%c",&opt);
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
        printf("\n\nInput: Quantum = %f",quantum);
        printf("\nProcess\t    Burst Time\t Arrival Time\n");
        for(int i=0;i<n;i++)
	    	printf("\nP%d\t\t%d\t\t%d\n",P[i].pno,P[i].burst,P[i].arrival);	
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

        printf("\n\nInput: Quantum = %f",quantum);
        printf("\nProcess\t    Burst Time\t Arrival Time\n");
        for(int i=0;i<n;i++)
	    	printf("\nP%d\t\t%d\t\t%d\n",P[i].pno,P[i].burst,P[i].arrival);
    }
    else {printf("Invalid Input\n"); return 0;}

    sorting(n);
    waiting(n,quantum,opt);
    printf("\n");
    return 0;
}