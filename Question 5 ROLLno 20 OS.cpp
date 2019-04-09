#include<stdio.h>
#include<unistd.h>
#define clear() printf("\033[H\033[J");//screen clear escape sequence
struct process
{
    int p_no;//process no
    int at;//arrival time
    int bt;//burst time
    int wt;//waiting time
    int pr;//priority
    int et;//end time
    int rbt;//required burst time
};
int N,Q,count,time=0;//N is no of processes,Q is time qunata;
void sort(struct process a[])//to sort according to the priority and burst time
{
	int i;
   for( i=0;i<N;i++)
   {
   	int j;
	     for(j=0;j<i;j++)
      {
            struct process temp;
          if(a[j].pr>a[j+1].pr)
           {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=a[j];
              }
           else if(a[j].pr==a[j+1].pr)
             {
                 if(a[j].rbt>a[j+1].rbt)
                 {
                    temp=a[j];
                   a[j]=a[j+1];
                   a[j+1]=a[j];
                    }
                }
         }
      }
}
void arrange(struct process a[],int n)//to put process at last in the queue
{
     struct process temp;
     temp=a[n];
     int i=0;
     for(i=n;i<N-1;i++)
     {
          a[i]=a[i+1];
         }
      a[i]=temp;
}
void Rr(struct process a[])//round robin
{
 while(count)
 {
 	int i;
   int flag=0;//to get whether processing is done or not
   for( i=0;i<N;i++)
    {
           if(count<=0)
            return;
         clear();
      
      if(time>=(a[i].at) && a[i].rbt!=0)
      {
        if(a[i].rbt>Q)
        {
              printf("Time at Start %d\n",time);     
               flag=1;
              time+=Q;
              a[i].rbt-=Q;
              printf("Process %d processed for %d minutes and remaining processing time is %d %d \n",a[i].p_no,Q,a[i].rbt,time);
              sleep(2);
              arrange(a,i);
              break;
            }
         else
          {
             printf("Time at Start %d\n",time);
             flag=1;
              time+=a[i].rbt;
             printf("Process %d processed for %d minutes and remaining processing time is %d %d\n",a[i].p_no,a[i].rbt,0,time);
                a[i].rbt=0;
               a[i].et=time;
               count--;
               a[i].wt=time-a[i].at-a[i].bt;
              sleep(2);
                arrange(a,i);
               break;
           }
        }
     }
      if(flag==0)
         {
        printf("Waiting.....%d\n",time);
       time++;
           }
  }    
}
int main()
{
     struct process a[50];
     printf("Enter the total no of processes.\n");
     scanf("%d",&N);
     count=N;
     time;
     printf("Enter the Amount of Time Quantum in Seconds.\n");
     scanf("%d",&Q);
     int i;
    for( i=0;i<N;i++)
     {    clear();
          printf("Enter details of process%d\n",i+1);
           printf("Enter priority No.\n");
           scanf("%d",&a[i].pr);
           a[i].p_no=i+1;
           a[i].et=0;
            printf("Enter arrival time of process.\n");
            scanf("%d",&a[i].at);
            printf("Enter burst time of the process.\n");
            scanf("%d",&a[i].bt);
            a[i].rbt=a[i].bt;
       }
   sort(a);
   Rr(a);
   int awt=0,atat=0;
   clear();
   for(i=0;i<N;i++)
     {
         printf("Waiting time for process%d is %d and turnaround time is %d.\n",a[i].p_no,a[i].wt,a[i].et-a[i].at);
          awt+=a[i].wt;
          atat+=a[i].et-a[i].at;
        }
      awt=awt/N;
      atat=atat/N;
      printf("Total time taken is %d\n",time);
      printf("Average waiting time is %d\n",awt);
      printf("Average turn Around time is %d\n",atat);
      return 0;
}
