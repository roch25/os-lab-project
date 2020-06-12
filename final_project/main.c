/*
  Contributors:
    Chetana Marathe (1929)
    Rochelle Martins (1930)
    Bhakti Naik (1935)
  Title: Pl206 Lab Project
  Description: Program to display Gannt Chart and calculate and display the Response Time, Waiting Time and Turnaround time for a set of user-input participating procceses or various scheduling algorithms
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "process.h"
#include "scheduling.h"

int main(int argc, char const *argv[])
{
  int num_of_processes, time_slice, status;
  printf("This is a program to display Gannt Chart and calculate and display the Response Time, Waiting Time and Turnaround time for a set of user-input participating procceses for various scheduling algorithms\n");
  printf("Enter the number of procceses\n");
  scanf("%d", &num_of_processes);
  while (is_valid(num_of_processes, NUM_OF_PROCESSES_MIN, NUM_OF_PROCESSES_MAX))
  {
    printf("Number of procceses should be between %d and %d (inclusive). Please enter the number of procceses again\n", NUM_OF_PROCESSES_MIN, NUM_OF_PROCESSES_MAX);
    scanf("%d", &num_of_processes);
  }
  process p[num_of_processes]; // [declaration] an array of type 'process' and size num_of_processes
  enter_process_details(num_of_processes, p);

  printf("\nEnter the time quantum for Round Robin ");
  fflush(stdin);
  scanf("%d", &time_slice);

  pid_t p1 = fork(); // create child 1
  pid_t p2 = fork(); // create child 2

  if (p1 && p2)
  {
      wait(&status);
      first_come_first_served(p, num_of_processes);
  }
  else if (p1 && (!p2))
  {
      wait(&status);
      shortest_job_first_scheduling(p, num_of_processes);
  }
  else if (p2 && (!p1))
  {
       wait(&status);
       round_robin(p, num_of_processes, time_slice);
  }
  else
  {
     wait(&status);
       priority(p, num_of_processes);
  }
  return 0;
}