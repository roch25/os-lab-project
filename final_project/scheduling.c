#include <stdio.h>
#include <unistd.h>
#include "process.h"
#include "scheduling.h"

void sort(process p[],int n)
{
    process p_tmp;
    for(int i = 0; i < n; i++)
    {
        for(int j = 1; j < n; j++){
            if(p[i].arrival_time > p[j].arrival_time){
                p_tmp = p[i];
                p[i] = p[j];
                p[j] = p_tmp;
            }
        }
    }
}

// First Come First Served
void first_come_first_served(process p[10], int n)
{
	process temp[10];
	int sum_waiting_time = 0, sum_turnaround_time = 0;
	int x = 0;
	float avg_waiting_time = 0.0, avg_turnaround_time = 0.0;
	int i,j;
     
	for(i = 0;i < n;i++) //save the array to a temp 
		temp[i] = p[i];
    
	sort(temp,n); // sorting by arrival time
	
    sum_waiting_time = temp[0].waiting_time = 0;
    sum_turnaround_time = temp[0].turnaround_time = temp[0].burst_time - temp[0].arrival_time;
    for(i=1;i<n;i++){
        temp[i].waiting_time = (temp[i-1].burst_time + temp[i-1].arrival_time + temp[i-1].waiting_time) - temp[i].arrival_time;;
        temp[i].turnaround_time = (temp[i].waiting_time + temp[i].burst_time);
        sum_waiting_time+=temp[i].waiting_time;
        sum_turnaround_time+=temp[i].turnaround_time;
    }
    avg_waiting_time = (float)sum_waiting_time/n;
    avg_turnaround_time = (float)sum_turnaround_time/n;

    printf("\n\nFIRST COME FIRST SERVED\n.------.--------------.-------------.----------------.-------------------.\n");
    printf("| Name | Arrival Time |  Burst Time |  Waiting Time  | Turnaround Time   |");
    printf("\n.------.--------------.-------------.----------------.-------------------.");
    for(i=0;i<n;i++)
    printf("\n|  %s  |       %d      |       %d     |      %d         |        %d          |",temp[i].process_name,temp[i].burst_time,temp[i].arrival_time, temp[i].waiting_time,temp[i].turnaround_time);
    printf("\n.------.--------------.-------------.----------------.-------------------.");
 
    printf("\n\n GANTT CHART\n\n");
    for(i=0;i<n;i++)
        printf("    %s   ", temp[i].process_name);
    printf("\n ");

    printf("0\t");
    for(i=1;i<=n;i++){
        x+=temp[i-1].burst_time;
        printf("%d      ",x);
    }
    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avg_waiting_time,avg_turnaround_time);
}

// Shortest Job First - Pre-emptive
void shortest_job_first_scheduling(process p[],int n)
{
	int i, t_total = 0,tcurr, b[10], j, x, min_burst_time;
	int sum_waiting_time = 0, sum_turnaround_time = 0;
	float avg_waiting_time = 0.0, avg_turnaround_time = 0.0;
	process temp[10], t;

	for(i=0;i<n;i++){
		temp[i]=p[i];
		t_total+=p[i].burst_time;
	}

	sort(temp, n);

	for(i=0;i<n;i++)
		b[i] = temp[i].burst_time;

	i = j = 0;

    
	printf("\nGANTT CHART\n\n %d %s",i,temp[i].process_name);
	for(tcurr=0;tcurr<t_total;tcurr++){

		if(b[i] > 0 && temp[i].arrival_time <= tcurr)
			b[i]--;

		if(i!=j)
			printf(" %d %s",tcurr,temp[i].process_name);

		if(b[i]<=0 && temp[i].flag != 1){
		
			temp[i].flag = 1;
			temp[i].waiting_time = (tcurr+1) - temp[i].burst_time - temp[i].arrival_time;
			temp[i].turnaround_time = (tcurr+1) - temp[i].arrival_time;
			sum_waiting_time += temp[i].waiting_time;
			sum_turnaround_time += temp[i].turnaround_time;
		}

       
 
		j=i;	
        min_burst_time = 999;
		for(x=0;x<n;x++){
		
			if(temp[x].arrival_time <= (tcurr+1) && temp[x].flag != 1){
			
				if(min_burst_time != b[x] && min_burst_time > b[x]){
					min_burst_time = b[x];
					i=x;
				}
			}
		}
		
	}
	printf(" %d",tcurr);
     printf("\n\nShortest Job First - Pre-emptive \n.------.--------------.-------------.----------------.-------------------.\n");
    printf("| Name | Arrival Time |  Burst Time |  Waiting Time  | Turnaround Time   |");
    printf("\n.------.--------------.-------------.----------------.-------------------.");
    for(i=0;i<n;i++)
    printf("\n|  %s  |       %d      |       %d     |      %d         |         %d         |",temp[i].process_name,temp[i].burst_time,temp[i].arrival_time, temp[i].waiting_time,temp[i].turnaround_time);
    printf("\n.------.--------------.-------------.----------------.-------------------.");
	avg_waiting_time = (float)sum_waiting_time/n;	
    avg_turnaround_time = (float)sum_turnaround_time/n;
	printf("\n\n Average waitiing time = %0.2f\n Average turn-ffaround = %0.2f.",avg_waiting_time,avg_turnaround_time);
}