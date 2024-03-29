#define NUM_OF_PROCESSES_MIN 2
#define NUM_OF_PROCESSES_MAX 10
#define TIME_MIN 0
#define TIME_MAX 255

struct process
{
  char process_name[25];
  int arrival_time, burst_time, waiting_time, turnaround_time, r_time, s_time;
};
typedef struct process process;

int is_valid(int, int, int);                       // funtion to validate the user input for a particular variable is between limits, 2nd arg takes the lower limit and third variable takes the upper limit
void enter_process_details(int, process p1[10]);   // funtion to take input of process details
int check_unique_process_name(int, process p[10]); // funtion to take check if the process name is unique
void display_gannt_chart(process p[10], int);      // displays gannt chart for scheduling algorithm input as an abbr