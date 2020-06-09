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
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // printing process name in the middle
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
        printf("%s", p[i].process_name);
        for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
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

void shortest_remaining_time_first(process p[10], int n)
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