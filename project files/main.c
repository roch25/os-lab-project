/*
  Authors:
    Chetana Marathe (1929)
    Rochelle Martins (1930)
    Bhakti Naik (1935)
  Pl206 Project
  Description: Program to display Gannt Chart and calculate and display the Response Time, Waiting Time and Turnaround time for a set of user-input participating procceses or various scheduling algorithms
*/
#include<stdio.h>
#include"process.h"

int main(int argc, char const *argv[]) {
  int num_of_processes;
  printf("This is a program to display Gannt Chart and calculate and display the Response Time, Waiting Time and Turnaround time for a set of user-input participating procceses for various scheduling algorithms\n");
  printf("Enter the number of procceses\n");
  scanf("%d", &num_of_processes);
  while(is_valid(num_of_processes, NUM_OF_PROCESSES_MIN, NUM_OF_PROCESSES_MAX)){
    printf("Number of procceses should be between %d and %d (inclusive). Please enter the number of procceses again\n", NUM_OF_PROCESSES_MIN, NUM_OF_PROCESSES_MAX);
    scanf("%d", &num_of_processes);
  }
  enter_process_details(num_of_processes);
  return 0;
}
