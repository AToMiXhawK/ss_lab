#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int total(int *seek, int n, int head)
{
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum += abs(head-seek[i]);
        head = seek[i];
    }
    return sum;
}

void plot(int *s, int head, int n, char str[])
{
    char * commandsForGnuplot[] = {"set style data line", "plot [0:200][0:10] 'data.temp'"};
    FILE * temp = fopen("data.temp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(temp, "%d 0 \n", head);
    for (int i=0; i < n; i++)
        fprintf(temp, "%d %d \n", s[i], i+1);
    
    fprintf(gnuplotPipe, "set title \"%s\" \n", str);

    for (int i=0; i < 2; i++)
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
}

int main()
{
    srand(time(0));
    int n = rand()%10, *seek = (int *)malloc(sizeof(int *)*n), head = rand()%200;
    for(int i=0;i<n;i++)
        seek[i] = rand()%200;
    
    printf("Head: %d\n",head);
    for(int i=0;i<n;i++)
        printf("%d ", seek[i]);
    printf("\nSum = %d \n", total(seek, n, head));
    char str[] = "FCFS";
    plot(seek,head,n,str);                                                      // install package gnuplot for this function to work
}