/*
  Contributors:
    Chetana Marathe (1929)
    Rochelle Martins (1930)
    Bhakti Naik (1935)
  Title: Pl206 Lab Project
  Description: Program to display Gannt Chart and calculate and display the Response Time, Waiting Time and Turnaround time for a set of user-input participating procceses or various scheduling algorithms
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "process.h"
#include "scheduling.h"

void signal_handler(int signo)
{
	int i,j;
	if(signo==SIGINT)
	{	
    return;
	}
	else if(signo==SIGTSTP)
	{
		printf("\nexiting\n");
		exit(0);
	}
}

int main(int argc, char const *argv[])
{
  signal(SIGINT, signal_handler);
  int num_of_processes, time_slice, status, status1, status2, status3, status4;
  printf("This is a program to display Gannt Chart and calculate and display the Waiting Time and Turnaround time for a set of user-input participating procceses for various scheduling algorithms\n");
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

  float rr_w, rr_t, fcfs_w, fcfs_t, sjfs_w, sjfs_t, p_w, p_t;
  pid_t p1 = fork(); // create child 1

  if (p1)
  {
    first_come_first_served(p, num_of_processes, &fcfs_t, &fcfs_w);
    wait(&status1);
    shortest_job_first_scheduling(p, num_of_processes, &sjfs_t, &sjfs_w);
    wait(&status1);
    round_robin(p, num_of_processes, &rr_t, &rr_w, time_slice);
    wait(&status1);
    priority(p, num_of_processes, &p_w, &p_t);
    wait(&status1);
    printf("\n\nWaiting time for \nRound Robin: %.2f\nShortest Job First: %.2f\nPritority: %.2f\nFirst Come First Served :%.2f", rr_w, sjfs_w, p_w, fcfs_w);
  }

  sleep(1);
  return 0;
}