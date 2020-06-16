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
#define RED "\e[1;31m"
#define YELLOW "\e[1;35m"
#define RESET "\x1b[0m"

void find_minimum(float rr_w, float sjfs_w, float p_w, float fcfs_w);

void signal_handler(int signo)
{
  char another;
	if(signo==SIGINT)
	{
    printf(YELLOW"Are you sure you want to exit? (Y/N)"RESET);
    scanf(" %c", &another);
    if(another == 'y' || another == 'Y'){
      printf("Exiting...\n");
      exit(0);
    }
    else
      return;
	}
}

int main(int argc, char const *argv[])
{
  int num_of_processes, time_slice, status, status1;

  if(signal(SIGINT, signal_handler) == SIG_ERR)
    printf("\nError catching signal");

  printf("This is a program to display Gannt Chart and calculate and display the Waiting Time and Turnaround time for a set of user-input participating procceses for various scheduling algorithms\n");

  printf("Enter the number of procceses\n");
  scanf("%d", &num_of_processes);

  while (is_valid(num_of_processes, NUM_OF_PROCESSES_MIN, NUM_OF_PROCESSES_MAX))
  {
    printf(RED"Number of procceses should be between %d and %d (inclusive). Please enter the number of procceses again\n"RESET, NUM_OF_PROCESSES_MIN, NUM_OF_PROCESSES_MAX);
    scanf("%d", &num_of_processes);
  }
  process p[num_of_processes]; // [declaration] an array of type 'process' and size num_of_processes
  enter_process_details(num_of_processes, p);

  printf("\nEnter the time quantum for Round Robin ");
  fflush(stdin);
  scanf("%d", &time_slice);

  float rr_w, fcfs_w, sjfs_w, p_w;
  pid_t p1 = fork();

  if (!p1)
  {
    first_come_first_served(p, num_of_processes, &fcfs_w);
    shortest_job_first_scheduling(p, num_of_processes, &sjfs_w);
    round_robin(p, num_of_processes, &rr_w, time_slice);
    priority(p, num_of_processes, &p_w);
    printf("\n\nWaiting time for \nFirst Come First Served :%.2f\nRound Robin: %.2f\nShortest Job First: %.2f\nPritority: %.2f\n",rr_w, sjfs_w, p_w, fcfs_w);
    // wait(&status1);
  }
  else{

    find_minimum(rr_w, sjfs_w, p_w, fcfs_w);
		wait(&status1);
			// printf("ssagfjh %f %f %f %f",rr_w, sjfs_w, p_w, fcfs_w );
    // int min = ((rr_w * (rr_w > sjfs_w && rr_w > p_w && rr_w > fcfs_w)) + (fcfs_w * (fcfs_w > sjfs_w && fcfs_w > p_w && fcfs_w > rr_w)) + (sjfs_w * (sjfs_w > rr_w && sjfs_w > p_w && sjfs_w > fcfs_w)) + (p_w * (p_w> sjfs_w && p_w> sjfs_w && p_w> fcfs_w)));
    // printf("%d %f %f %f %f", min, rr_w * (rr_w > sjfs_w && rr_w > p_w && rr_w > fcfs_w), fcfs_w * (fcfs_w > sjfs_w && fcfs_w > p_w && fcfs_w > rr_w), sjfs_w * (sjfs_w > rr_w && sjfs_w > p_w && sjfs_w > fcfs_w), p_w * (p_w> sjfs_w && p_w> sjfs_w && p_w> fcfs_w));
  }

  return 0;
}

void find_minimum(float rr_w, float sjfs_w, float p_w, float fcfs_w)
{
 		printf("\n %f %f %f %f",rr_w, sjfs_w, p_w, fcfs_w );
}
