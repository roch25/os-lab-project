#include<stdio.h>
#include"process.h"

int is_valid(int n, int l, int h)
{
  if(n >= l && n <= h)
    return 0;
  else
    return -1;
}

void enter_process_details(int n)
{
    process p1[n]; // [declaration] an array of type 'process' and size n
    int i = 0;
    while(i < n){
      printf("Enter the process name \n" );
      scanf("%s", p1[i].process_name);
      printf("Enter arrival time (in milliseconds)\n");
      scanf("%d", &p1[i].arrival_time);
      while(is_valid(p1[i].arrival_time, TIME_MIN, TIME_MAX)){
        printf("Arrival time should be between %d and %d (inclusive). Please enter the number of procceses again\n", TIME_MIN, TIME_MAX);
        scanf("%d", &p1[i].arrival_time);
      }
      printf("Enter CPU burst time(in milliseconds)\n");
      scanf("%d", &p1[i].burst_time);
      while(is_valid(p1[i].burst_time, TIME_MIN, TIME_MAX)){
        printf("Burst time should be between %d and %d (inclusive). Please enter the number of procceses again\n", TIME_MIN, TIME_MAX);
        scanf("%d", &p1[i].burst_time);
      }
      printf("\n");
      i++;
    }
    for(int i = 0; i < n; i++){
      printf("%s %d %d\n",p1[i].process_name, p1[i].arrival_time, p1[i].burst_time);
    }
}
