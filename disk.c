#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void sort(int *ar, int n)
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(ar[j]>ar[j+1])
            { int t = ar[j]; ar[j] = ar[j+1]; ar[j+1] = t; }
}

void plot(int *s, int head, int n, char str[])
{
    char * commands[] = {"set style data line", "plot [0:200][0:20] 'data.temp'"};
    FILE * temp = fopen("data.temp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(temp, "%d 0 \n", head);
    for (int i=0; i < n; i++)
        fprintf(temp, "%d %d \n", s[i], i+1);
    
    fprintf(gnuplotPipe, "set title \"%s\" \n", str);

    for (int i=0; i < 2; i++)
        fprintf(gnuplotPipe, "%s \n", commands[i]);
    fclose(temp);
    fclose(gnuplotPipe);
}

int total(int *seek, int n, int head)
{
    int sum=0;
    for(int i=0;i<n;i++)
    { sum += abs(head-seek[i]); head = seek[i]; }
    return sum;
}

void fcfs(int *seek, int n, int head)
{
    printf("\nFCFS scheduling\nHead: %d\n",head);
    for(int i=0;i<n;i++)
        printf("%d ", seek[i]);
    printf("\nSum = %d \n", total(seek, n, head));
    char str[] = "FCFS";
    plot(seek,head,n,str);
}

void scan(int *seek, int n, int head, int max, char ch)
{
    int seek_scan[n+1];
    sort(seek, n);
    printf("\nSCAN scheduling\nHead: %d\n",head);
    printf("Sorted: ");
    for(int i=0;i<n;i++)
        printf("%d ", seek[i]);

    int p;
    for(p=0; p<n; p++)
        if(head<seek[p])
            break;

    if(ch=='?')
    {
        if(p==0) {ch='r';}
        else if(p>=n) {ch='l';}
        else if(head-seek[p-1] < seek[p]-head)
            ch = 'l';
        else
            ch = 'r';
    }

    int i;
    if(ch=='l')
    {
        i = 0;
        for(int j=p-1; j>=0; j--)
        {   seek_scan[i] = seek[j]; i++;   }
        if(p==n) { n--; goto print_scan; }
        seek_scan[i] = 0; i++;
        for(int j=p; j<n; j++)
        {   seek_scan[i] = seek[j]; i++;  }
    }
    else if(ch=='r')
    {
        i = 0;
        for(int j=p; j<n; j++)
        {   seek_scan[i] = seek[j]; i++;   }
        if(p==0) { n--; goto print_scan; }
        seek_scan[i] = max; i++;
        for(int j=p-1; j>=0; j--)
        {   seek_scan[i] = seek[j]; i++;  }
    }

print_scan:
    printf("\nScheduling: ");
    for(int i=0;i<n+1;i++)
        printf("%d ", seek_scan[i]);
    
    printf("\nSum = %d \n", total(&seek_scan[0], n+1, head));
    char str[] = "SCAN";
    plot(&seek_scan[0],head,n+1,str);
}

void cscan(int *seek, int n, int head, int max, char ch)
{
    int seek_scan[n+1];
    sort(seek, n);
    printf("\nC-SCAN scheduling\nHead: %d\n",head);
    printf("Sorted: ");
    for(int i=0;i<n;i++)
        printf("%d ", seek[i]);

    int p;
    for(p=0; p<n; p++)
        if(head<seek[p])
            break;

    int i;
    if(ch=='l')
    {
        i = 0;
        for(int j=p-1; j>=0; j--)
        {   seek_scan[i] = seek[j]; i++;   }
        if(p==n) { n-=2; goto print_cscan; }
        seek_scan[i] = 0; i++;
        seek_scan[i] = max; i++;
        for(int j=n; j>=p; j--)
        {   seek_scan[i] = seek[j]; i++;  }
    }
    else if(ch=='r')
    {
        i = 0;
        for(int j=p; j<n; j++)
        {   seek_scan[i] = seek[j]; i++;   }
        if(p==0) { n-=2; goto print_cscan; }
        seek_scan[i] = max; i++;
        seek_scan[i] = 0; i++;
        for(int j=0; j<p; j++)
        {   seek_scan[i] = seek[j]; i++;  }
    }

print_cscan:
    printf("\nScheduling: ");
    for(int i=0;i<n+2;i++)
        printf("%d ", seek_scan[i]);
    
    printf("\nSum = %d \n", total(&seek_scan[0], n+2, head));
    char str[] = "C-SCAN";
    plot(&seek_scan[0],head,n+2,str);
}

int main()
{
    int max = 200;
    srand(time(0));
    int n = (rand()%10 + 10), *seek = (int *)malloc(sizeof(int *)*n), head = rand()%max;
    for(int i=0;i<n;i++)
        seek[i] = rand()%200;

    fcfs(seek,n,head);
    scan(&seek[0],n,head,max,'?');
    cscan(&seek[0],n,head,max,'r');
}