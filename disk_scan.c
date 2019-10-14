#include<stdio.h>
#include<stdlib.h>
void main()
{
	int n,max,tr[20],init,i,j,seek=0,pos,current,next,count,flag=0;
	char dir;
	printf("\nEnter l for left r for right:\t");
	scanf("%c",&dir);
	printf("\nEnter number of requests:\t");
	scanf("%d",&n);
	printf("\nEnter initial head position:\t");
		scanf("%d",&init);
	printf("\nEnter range of disk:\t");
	scanf("%d",&max);
	current=init;
	printf("\nEnter requests:\t");
	for(i=0;i<n;i++)
	{	
		scanf("%d",&tr[i]);
	}	
	for(i=0;i<n;i++)
	{
		pos=i;
		for(j=i+1;j<n;j++)
		{
			if(tr[j]<tr[pos])
				pos=j;	
		}
		int temp=tr[pos];
		tr[pos]=tr[i];
		tr[i]=temp;
	}
	switch(dir)
	{
		case 'l':	for(i=n-1;i>=0;i--)
					if(tr[i]<current)
						{next=i;break;}
				break;
		case 'r':for(i=0;i<n;i++)
					if(tr[i]>current)
						{next=i;break;}
				break;
	}
	printf("\nSequence is: \t");

	count=n;
	//printf("\ncount:%d",count);
	while(count>0)
	{
		//printf("\ncount:%d",count);
		switch(dir)
		{
		 case 'l':	//printf("\nGoing left");
				for(j=next;j>=0;j--)
				{
					count--;
					printf("%d\t",tr[j]);
					seek+=abs(tr[j]-current);
					current=tr[j];
					if(count==0)
					{
						flag=1;break;
					}
				}
				if(flag==0)
				{
					seek+=current;
					current=0;
					printf("%d\t",current);
					dir='r';
					next++;	
				}			
				break;
		 case 'r':	//printf("\nGoing right");	
				for(j=next;j<n;j++)
				{
					count--;
					printf("%d\t",tr[j]);
					seek+=abs(tr[j]-current);
					current=tr[j];
					if(count==0)
					{
						flag=1;break;
					}
				}
				if(flag==0)
				{
					seek+=abs(current-max);
					current=max;
					printf("%d\t",current);
					dir='l';
					next--;
				}
				break;
		default:printf("\nInvalid choice");
		}
	}
	printf("\nTotal head movement:\t%d\n",seek);	
}
