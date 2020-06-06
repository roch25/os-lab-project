#include <stdio.h>
#include <unistd.h>
#include "process.h"
#include "scheduling.h"

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