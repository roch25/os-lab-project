#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "process.h"

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
    printf("Enter arrival time (in milliseconds)\n");
    scanf("%d", &p1[i].arrival_time);
    while (is_valid(p1[i].arrival_time, TIME_MIN, TIME_MAX))
    {
      printf("Arrival time should be between %d and %d (inclusive). Please enter the number of procceses again\n", TIME_MIN, TIME_MAX);
      scanf("%d", &p1[i].arrival_time);
    }
    printf("Enter CPU burst time(in milliseconds)\n");
    scanf("%d", &p1[i].burst_time);
    while (is_valid(p1[i].burst_time, TIME_MIN, TIME_MAX))
    {
      printf("Burst time should be between %d and %d (inclusive). Please enter the number of procceses again\n", TIME_MIN, TIME_MAX);
      scanf("%d", &p1[i].burst_time);
    }
    printf("\n");
    i++;
  }
}

void display_gannt_chart(process p[10], int n)
{
  pid_t p1 = fork(); // create child 1
  pid_t p2 = fork(); // create child 2

  if (p1 && p2)
  {
    // in parent: FCFS code comes here
  }
  else if (p1 && (!p2))
  {
    // in child1: SJFS code comes here
  }
  else if (p2 && (!p1))
  {
    // in child2: SRTF code comes here
  }
  else
  {
    // in child 3 (child 2's child): RR code comes here
  }
}
