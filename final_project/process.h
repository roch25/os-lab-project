#define NUM_OF_PROCESSES_MIN 2
#define NUM_OF_PROCESSES_MAX 10
#define TIME_MIN 0
#define TIME_MAX 255

struct process
{
  char process_name[25];
  int arrival_time, burst_time, waiting_time, turnaround_time, flag, priority;
};
typedef struct process process;
