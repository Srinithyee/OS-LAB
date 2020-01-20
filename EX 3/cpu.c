#include<stdio.h>
#include<stdlib.h>
struct processes
{
	int arrival_time;
	int burst_time;
	int process_id;
	int turnaround_time;
	int waiting_time;
	int remaining_time;
	int leave_time;
};
void fcfs(struct processes *p, int np)
{	
	int wait_time = 0;
	int turn_time = 0;
	for(int i = 0; i < np; i++)
	{
		// printf(" %d \n",wait_time);
		p[i].waiting_time = wait_time;
		p[i].turnaround_time = wait_time + p[i].burst_time;
		turn_time += p[i].turnaround_time;
		wait_time += p[i].burst_time;
		
	}
	printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
	for(int i = 0; i < np; i++)
	{
		printf("\t %d \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
	}
	int t_time = 0;
	for(int i=0; i<np;i++)
	{
		t_time += p[i].waiting_time;
	}
	float avg_wait = t_time /np;
	float avg_turn = turn_time /np;
	printf("Average waiting time : %f \n",avg_wait);
	printf("Average turnaround time : %f \n",avg_turn);
}
void sort(struct processes *p ,int np)
{
	struct processes t;
	for(int i = 0; i < np -1 ;i++) 
	{
		for(int j = 0 ;j < np -i-1; j++)
			{
				if(p[j+1].burst_time < p[j].burst_time)
					{
						t = p[j+1];
						p[j+1] = p[j];
						p[j] = t;
					}
			}
	}
}
void sort_rem(struct processes *p ,int np)
{
	struct processes t;
	for(int i = 0; i < np -1 ;i++) 
	{
		for(int j = 0 ;j < np -i-1; j++)
			{
				if(p[j+1].remaining_time < p[j].remaining_time)
					{
						t = p[j+1];
						p[j+1] = p[j];
						p[j] = t;
					}
			}
	}
}

void nonpreemptive(struct processes* p ,int np)
{
	sort(p,np);
	fcfs(p,np);
}
void preemptive(struct processes *p ,int np)
{
	int shortest = 0;
	int complete = 0; // no of completed processes
	int finish = 0;
	int minimum = 100;
	int wait_time = 0;
	int turn_time = 0;
	int t = 0; //cpu current time
	int check = 0; // checking if shortest time exists
	for(int i = 0;i < np;i++)
	 p[i].remaining_time = p[i].burst_time;
	 
	while(complete != np)
	{
		for(int j = 0 ; j < np ; j++)
		{	
			if( (p[j].arrival_time <=t) && (p[j].remaining_time < minimum) && (p[j].remaining_time > 0)) 
			{	
				minimum = p[j].remaining_time;
				shortest = j;
				check = 1;
			}
		}
		if(check == 0)
		{
			t++;
			continue;
		}
		
		p[shortest].remaining_time -=1;
		minimum = p[shortest].remaining_time;
		if(minimum == 0)
			minimum = 100;
		if(p[shortest].remaining_time == 0)
		{
			complete++;
			check = 0 ;
			finish = t + 1;
		p[shortest].waiting_time = finish - p[shortest].burst_time - p[shortest].arrival_time;
		
		if( p[shortest].waiting_time < 0)
			p[shortest].waiting_time = 0;
		}
		
		t++;
	}
	for(int i = 0 ; i < np;i++)
		p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
	
	for(int i = 0; i < np; i++)
	{
		turn_time += p[i].turnaround_time;
		wait_time += p[i].waiting_time;
		
	}
	printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
	
	for(int i = 0; i < np; i++)
	{
		printf("\t %d \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
	}
	
	float avg_wait = wait_time /np;
	float avg_turn = turn_time /np;
	printf("Average waiting time : %f \n",avg_wait);
	printf("Average turnaround time : %f \n",avg_turn);		
}			
void main()
{
	int no_of_processes;
	printf("Enter number of processes \n");
	scanf("%d",&no_of_processes);
	int choice;
	struct processes *p = malloc(sizeof(struct processes)*no_of_processes);
	
	for(int i = 0; i < no_of_processes; i++)
	{
		printf("Enter process ID \n");
		scanf("%d",&p[i].process_id);
		printf("Enter Burst time \n");
		scanf("%d",&p[i].burst_time);
		printf("Enter arrival time \n");
		scanf("%d",&p[i].arrival_time);
	}
	while(choice!=4)
	{
	printf("\t\t Main Menu \n");
	printf("\t 1. First Come First Serve(FCFS)\n");
	printf("\t 2. SJF (preemptive)\n");
	printf("\t 3. SJF (Non-Preemptive)\n");
	printf("\t 4. Exit\n");
	printf("Enter choice \n");
	scanf("%d",&choice);
	switch(choice)
		{
			case 1: fcfs(p,no_of_processes);
			        break;
			case 2: preemptive(p,no_of_processes);
			        break;
			case 3: nonpreemptive(p, no_of_processes);
			        break;
		}
	}

}