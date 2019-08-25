#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int total(int *seek, int n, int head, char c)
{
    int sum=0, tail, flag=0;
    for(int i=0;i<n;i++)
        if(seek[i]>head)
        {
            tail = i;
            flag = 1;
            break;
        }
    if(flag==0)
        tail=n-1;
    if(c=='r')
    {
        for(int i=tail-1;i>=0;i--)
        {
            printf("\n%d", seek[i]);
            sum += abs(head-seek[i]);
            head = seek[i];
        }
        for(int i=n-1;i>=tail;i--)
        {
            printf("\n%d", seek[i]);
            sum += abs(head-seek[i]);
            head = seek[i];
        }
    }
    else
    {
        for(int i=tail;i<n;i++)
        {
            printf("\n%d", seek[i]);
            sum += abs(head-seek[i]);
            head = seek[i];
        }
        for(int i=0;i<tail;i++)
        {
            printf("\n%d", seek[i]);
            sum += abs(head-seek[i]);
            head = seek[i];
        }
    }
    
    return sum;
}

void sorting(int seek[], int n)
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(seek[j]>seek[j+1])
            {
                int t = seek[j];
                seek[j] = seek[j+1];
                seek[j+1] = t;
            }
}

void plot(int *s, int head, int n)
{
    char * commandsForGnuplot[] = {"set title \"Disk SCAN\"", "set style data line", "plot [0:200][0:10] 'scan.data'"};
    FILE * temp = fopen("scan.data", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(temp, "%d 0 \n", head);
    for (int i=0; i < n; i++)
        fprintf(temp, "%d %d \n", s[i], i+1);
    for (int i=0; i < 3; i++)
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
}

int main()
{
    srand(time(0));
    int n = rand()%10+1, *seek = (int *)malloc(sizeof(int *)*n), head = rand()%200;
    seek[0] = 0;
    printf("Head: %d\n", head);
    for(int i=1;i<n;i++)
        seek[i] = rand()%200;
    sorting(seek, n);
    for(int i=0;i<n;i++)
        printf("%d ", seek[i]);
    printf("\nSum = %d \n", total(seek, n, head, 'l'));
    plot(seek,head,n);
}