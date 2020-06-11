#include <stdio.h>
#include <unistd.h>
#include "process.h"
#include "scheduling.h"

void print_table(process p[], int n)
{
    int i;
    printf(".------.--------------.-------------.--------------.-----------------.\n");
    printf("| Name | Arrival Time |  Burst Time | Waiting Time | Turnaround Time |\n");
    printf(".------.--------------.-------------.--------------.-----------------.\n");
    for(i=0; i<n; i++) {
        printf("|  %s  |      %2d      |     %2d      |      %2d      |        %2d       |\n" ,p[i].process_name, p[i].arrival_time,  p[i].burst_time, p[i].waiting_time, p[i].turnaround_time );
        printf(".------.--------------.-------------.--------------.-----------------.\n");
    }
}

void print_gantt_chart(process p[], int n)
{
    int i, j;
    // print top bar
    printf(".");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(".");
    }
    printf("\n|");

    // printing process name in the middle
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
        printf("%s", p[i].process_name);
        for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n.");
    // printing bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(".");
    }
    printf("\n");

    // printing the timeline
    printf("0");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("  ");
        if(p[i].turnaround_time > 9) 
          printf("\b");
        printf("%d", p[i].turnaround_time);

    }
    printf("\n\n");
} 

int get(process arr[],int t,int n)
{
       int imin,min=9999,i;
       for(i=0;i<n;i++)
       {
              if(arr[i].arrival_time <= t && arr[i].s_time == 0)
                     if(min > arr[i].burst_time)
                     {
                           min=arr[i].burst_time;
                           imin=i;
                     }
       }
       return imin;
}

  
void gantt_chart_srjf(process arr[],int p[],int n,int nop)
{
       int i,a[100],s=0;
       float avgtt=0,avgwt=0;
       printf("***************************************\n");
       printf("GANTT CHART\n");
       printf("0");
       for(i=0;i<n-1;i++)
       {
              while(i<n-1&&p[i]==p[i+1])
              {
                     s++;
                     i++;
              }
               
              s++;
              printf(" |  %s   [%d]",arr[p[i]].process_name,s);
              arr[p[i]].waiting_time = s - arr[p[i]].arrival_time - arr[p[i]].turnaround_time;
       }
       for(i = 0;i < nop;i++)
       {
              arr[i].turnaround_time += arr[i].waiting_time;
              avgwt += arr[i].waiting_time;
              avgtt += arr[i].turnaround_time;
       }
        printf("\n.------.--------------.-------------.---------------.----------------.\n");
        printf("| Name | Arrival Time |  Burst Time | Turnaround Time | Waiting Time |\n");
        printf(".------.--------------.-------------.-----------------.-------------.\n");
       for(i=0;i<nop;i++)
       {
        printf("   %s  |       %d       |     %d      |       %d         |       %d \n",arr[i].process_name, arr[i].arrival_time,arr[i].r_time,arr[i].turnaround_time,arr[i].waiting_time);
       }
         printf(".------.--------------.-------------.-----------------.-------------.\n");
       avgwt = avgwt/nop;
       avgtt = avgtt/nop;
       printf("Average Waiting Time : %.2f\n"
       ,avgwt);
       printf("Average Turnaround Time : %.2f\n",avgtt);
       return;
}

int iscomplite(process arr[],int n)
{
       int i;
       for(i=0;i<n;i++)
              if(arr[i].s_time == 0)
                     return 0;
       return 1;
}

void sort_by_arrival_time(process p[10], int n)
{
  process p_tmp;
  for(int i = 0; i < n; i++) // sorting by arrival time
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

void shortest_remaining_time_first(process p[10], int n)
{
    int i, t = 0, a;
    int tmp[100];
    float avgwt=0,avgtt=0;
    printf("SJF (Shortest Job First) - Preemptive\n");
    for(i = 0;i < n;i++)
    {
        p[i].r_time = p[i].burst_time;
        p[i].s_time = 0;
        p[i].turnaround_time = p[i].burst_time;
        p[i].waiting_time = 0;
    }
    sort_by_arrival_time(p, n);
    i = 0;
    while(1)
    {
        if(iscomplite(p,n))
             break;
        a = get(p,t,n);
        tmp[i] = a;
        p[a].burst_time -= 1;
        if(p[a].burst_time == 0)
               p[a].s_time = 1;
        t += 1;
        i++;
    }
    gantt_chart_srjf(p, tmp ,i ,n);
}

void first_come_first_served(process p[10], int n)
{
    int sum_waiting_time = 0, sum_turnaround_time, i;
    p[0].turnaround_time = p[0].burst_time;

    for(i=1; i<n; i++) {
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }

    for(i=0; i<n; i++) {
            sum_waiting_time += p[i].waiting_time;
            sum_turnaround_time += p[i].turnaround_time;
    }

    print_table(p, n);
    // printing Gantt chart
    puts("\nGANTT CHART\n");
    print_gantt_chart(p, n);
    printf("Total Waiting Time      : %-2d\n", sum_waiting_time);
    printf("Average Waiting Time    : %-2.2lf\n", (double)sum_waiting_time / (double) n);
    printf("Total Turnaround Time   : %-2d\n", sum_turnaround_time);
    printf("Average Turnaround Time : %-2.2lf\n", (double)sum_turnaround_time / (double) n);
}

void round_robin(process p[10], int n, int time_slice)
{
    printf("\nRound Robin\n");
    int i, j, remaining, flag = 0, time;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    remaining = n;
    for(i = 0;i < n;i++)
    {
        p[i].r_time = p[i].burst_time;
    }
    sort_by_arrival_time(p, n);

    for(time = 0,i = 0;remaining != 0;)
    {
        if(p[i].r_time <= time_slice && p[i].r_time > 0)
        {
            time = time + p[i].r_time;
            printf(" |   %s    [%d]",p[i].process_name, time);
            p[i].r_time = 0;
            flag = 1;
        }
        else if(p[i].r_time > 0)
        {
            p[i].r_time = p[i].r_time - time_slice;
            time = time + time_slice;
            printf("|    %s     [%d]",p[i].process_name, time);
        }
        if(p[i].r_time == 0 && flag == 1)
        {
                remaining--;
                p[i].turnaround_time = time-p[i].arrival_time;
                p[i].waiting_time = time-p[i].arrival_time-p[i].burst_time;
                avg_waiting_time = avg_waiting_time + time - p[i].arrival_time - p[i].burst_time;
                avg_turnaround_time = avg_turnaround_time + time - p[i].arrival_time;
                flag = 0;
        }
        if(i == n - 1)
                i = 0;
        else if(p[i+1].arrival_time <= time)
                i++;
        else
                i=0;
    }
    printf("\nAverage Waiting Time      : %-2.2f\n", avg_waiting_time);
    // printf("Average Waiting Time    : %-2.2lf\n", (double)avg_waiting_time / (double) n);
    printf("\nAverage Turnaround Time   : %-2.2f\n", avg_turnaround_time);
    // printf("Average Turnaround Time : %-2.2lf\n", (double)avg_turnaround_time / (double) n);
}