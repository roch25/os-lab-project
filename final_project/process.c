#include <stdio.h>
#include <string.h>
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
    printf("Enter arrival time (in milliseconds) [Note: Arrival time for FCFS is automatically set to 0]\n");
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

    printf("Enter priority [0 - highest ... 5 - lowest]\n");
    scanf("%d", &p1[i].priority);
    while (is_valid(p1[i].priority, 0, 5))
    {
      printf("Burst time should be between %d and %d (inclusive). Please enter the number of procceses again\n", 0, 5);
      scanf("%d", &p1[i].priority);
    }
    printf("\n");
    i++;
  }
}

