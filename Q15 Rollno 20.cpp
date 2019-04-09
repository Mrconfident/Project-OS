#include<stdio.h>
#include<conio.h>
int n;   // FOR NUMBER OF PROCESS
struct process
{
	int p_no; //PROCESSNUMBER
	int turnA_time,burst_time,wait_time,f_burst;
	int arrival_time,completion_time;
	int flag;  //for delimiter
}process_list[100]; //object array of structure

void Arrange()  // function arranges process and swaps as per ARRIVAL TIME
{
	struct process p;
	int i,j;
	for(i=0;i<n;i++)
	
	{
		for(j=0;j<n-1;j++)
		{
				if(process_list[j].burst_time>process_list[j+1].burst_time)
				{
				p=process_list[j];
				process_list[j]=process_list[j+1];
				process_list[j+1]=p;
				}
		}
	}
}

int main()
{
	int t=0,Burst_t=0,Arrival_t=0,peak;  //PEAK USED for MAXIMA
	float Wait_t=0,TurnAround_t=0,AVGTurn_t=0,AVGWait_t=0;
	int a[10];  //ARRAY TO STORE BURST TIME OF PROCESSEs
	printf("ENTER NUMBER OF PROCESSES: ");
	scanf("%d",&n);
	int count=n,time=0,f=0;
	for(int i = 0; i < n; i++)
 
 {

    process_list[i].p_no = i+1;

    printf("\nEnter Details For P%d process:-\n", process_list[i].p_no);
    printf("Enter Arrival Time: ");
    scanf("%d", &process_list[i].arrival_time );
    printf("Enter Burst Time: ");
    scanf("%d", &process_list[i].burst_time);
    process_list[i].flag = 0;
    Burst_t = Burst_t + process_list[i].burst_time;
    process_list[i].f_burst=process_list[i].burst_time;
 }
	while(count)
	{
		f=0;
		
		for(int j=0;j<n;j++)
		{
			
			if(process_list[j].arrival_time<=time && process_list[j].burst_time!=0)
			{
				
				f=1;
				process_list[j].burst_time--;
				time++;
				if(process_list[j].burst_time==0)
				{
				process_list[j].completion_time=time;
				process_list[j].turnA_time=time-process_list[j].arrival_time;
				process_list[j].wait_time=time-process_list[j].arrival_time-process_list[j].f_burst;
			    count--;
			   }
			   Arrange();
			   break;
			}
		}
		if(f==0)
		{
		time++;
	    }
	}
printf("PNO\tAT\tCT\tTA\tWTt\n");
for(int i=0;i<n;i++)
{
printf("P%d\t%d\t%d\t%d\t%d\n",process_list[i].p_no,process_list[i].arrival_time,process_list[i].completion_time,process_list[i].turnA_time
,process_list[i].wait_time);
AVGTurn_t+=process_list[i].turnA_time;
AVGWait_t+=process_list[i].wait_time;
 }
printf("Average Turn around Time: %f\t\n\n",(AVGTurn_t)/n);
printf("Average Waiting Time :\t %f\t\n",(AVGWait_t)/n);
}




