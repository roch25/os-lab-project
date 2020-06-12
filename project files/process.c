#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "process.h"
#include "scheduling.h"

int is_valid(int n, int l, int h)
{
  if (n >= l && n <= h)
    return 0;
  else
    return -1;
}

int check_unique_process_name(int current_process_index, process p1[10])
{
  int flag = 0;
  if (!current_process_index)
  {
    return flag;
  }
  for (int i = 0; i < current_process_index; i++)
  {
    if (!strcmp(p1[i].process_name, p1[current_process_index].process_name))
    {
      flag = -1;
      break;
    }
  }
  return flag;
}

void enter_process_details(int n, process p1[n])
{
  int i = 0;
  while (i < n)
  {
    printf("Enter the process name \n");
    scanf("%s", p1[i].process_name);
    while (check_unique_process_name(i, p1))
    {
      printf("A process with this process name already exists. Enter the process name again \n");
      scanf("%s", p1[i].process_name);
    }
    printf("Enter arrival time (in milliseconds) [Note: Arrival time for FCFS is automatically set to 0]\n");
    scanf("%d", &p1[i].arrival_time);
    while (is_valid(p1[i].arrival_time, TIME_MIN, TIME_MAX))
    {
      printf("Arrival time should be between %d and %d (inclusive). Please enter the number of procceses again\n", TIME_MIN, TIME_MAX);
      scanf("%d", &p1[i].arrival_time);
    }
    printf("Enter CPU burst time(in milliseconds)\n");
    scanf("%d", &p1[i].burst_time);
    while (is_valid(p1[i].burst_time, TIME_MIN + 1, TIME_MAX))
    {
      printf("Burst time should be between %d and %d (inclusive). Please enter the number of procceses again\n", TIME_MIN + 1, TIME_MAX);
      scanf("%d", &p1[i].burst_time);
    }
    printf("\n");
    i++;
  }
}

void display_gannt_chart(process p[10], int n)
{
  int time_slice;
  printf("\nEnter the time quantum for Round Robin ");
  fflush(stdin);
  scanf("%d", &time_slice);
  pid_t p1 = fork(); // create child 1
  pid_t p2 = fork(); // create child 2
  if (p1 && p2)
  {
    for(int i = 0; i < n; i++)
    {
        p[i].waiting_time = p[i].turnaround_time = p[i].arrival_time = 0;
    }
    first_come_first_served(p, n);
  }
  else if (p1 && (!p2))
  {
    // in child1: SJFS code comes here
  }
  else if (p2 && (!p1))
  {
    shortest_remaining_time_first(p, n);
  }
  else
  {
    round_robin(p, n, time_slice);
  }
}
