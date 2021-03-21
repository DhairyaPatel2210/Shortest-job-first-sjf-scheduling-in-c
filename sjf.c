#include<conio.h>
#include<stdio.h>

/*
variable naming
no_process = total number of processes
process_nm = it will store process name
arrival_time = store the value of arrival time
burst_time = store the value of burst time
wt = total waiting time
tat = total turn around time
time = store the current value of time
arrived_process_name = it will store all the process name that were arrived before the current time value
arrived_process_at = store the arrival time of arrived process
arrived_process_bt = store the burst time of arrived process
process_number = process number that currently running
temp1 = will store the temporary value of process name
average_wt = average waiting time
average_tat = average turn around time
*/

typedef struct process_nam
{
    char process_name[20];
}process_name;


void main()
{
    int no_process,temp;
    printf("------This program is for ShortestJob First(non-preemptive)------");
    printf("\nEnter the number of processes : ");
    scanf("%d",&no_process);
    process_name process_nm[no_process],temp_process_nm;
    int arrival_time[no_process],burst_time[no_process];
    for(int i=0;i<no_process;i++)
    {
        printf("Enter process name : ");
        scanf("%s",&process_nm[i].process_name);
        printf("Enter arrival time : ");
        scanf("%d",&arrival_time[i]);
        printf("Enter burst time : ");
        scanf("%d",&burst_time[i]);
        printf("-----------------------------\n");
    }
    //code for sorting the processes according to their arrival time with the use of selection sort
    for(int i=0;i<no_process-1;i++)
    {
        int minimum = i;
        for(int j=i+1;j<no_process;j++)
        {
            if(arrival_time[j]<arrival_time[minimum])
            {
                minimum = j;
            }
            else if(arrival_time[j] == arrival_time[minimum])
            {
                minimum = j;
            }
        }
        temp = arrival_time[minimum];
        arrival_time[minimum] = arrival_time[i];
        arrival_time[i] = temp;

        temp_process_nm = process_nm[minimum];
        process_nm[minimum] = process_nm[i];
        process_nm[i] = temp_process_nm;

        temp = burst_time[minimum];
        burst_time[minimum] = burst_time[i];
        burst_time[i] = temp;

    }

    //printing out the process name, arrival time, burst time
    printf("\nProcess_name \t\t arrival_time \t\t burst_time");
    for(int i=0;i<no_process;i++)
    {
        printf("\n %s \t\t\t %d \t\t\t %d",process_nm[i].process_name,arrival_time[i],burst_time[i]);
    }


    //code for calculating waiting time(wt) and turn around time(tat)
    int time = 0,process_number = 0,wt=0,tat=0;
    process_name arrived_prcs_name[no_process],temp1;
    int arrived_prcs_at[no_process],arrived_prcs_bt[no_process];
    //calculating total waiting and turn around time
    for(int i=0;process_number<no_process;i++)
    {
        time = time + burst_time[i];
        wt = ( wt + time ) - (arrival_time[i] + burst_time[i]);
        tat = ( tat + time ) - arrival_time[i];
        process_number++;  //after calculation of current process increment process number
        for(int j=process_number;j<no_process;j++) //adding all the processes to arrived_processes array which are arrived before time
        {
            if(arrival_time[j] <= time)
            {
                arrived_prcs_name[j] = process_nm[j];
                arrived_prcs_at[j] = arrival_time[j];
                arrived_prcs_bt[j] = burst_time[j];
            }
        }
        //sorting arrived processes array on the basis of burst time
        int min=0;
        for(int j=process_number;j<no_process-1;j++)
        {
            min = j;
            for(int k=j+1;k<no_process;k++)
            {
                if(arrived_prcs_bt[k] < arrived_prcs_bt[min])
                {
                    min = k;
                }
            }
            temp = arrived_prcs_bt[min];
            arrived_prcs_bt[min] = arrived_prcs_bt[j];
            arrived_prcs_bt[j] = temp;

            temp1 = arrived_prcs_name[min];
            arrived_prcs_name[min] = arrived_prcs_name[j];
            arrived_prcs_name[j] = temp1;

            temp = arrived_prcs_at[min];
            arrived_prcs_at[min] = arrived_prcs_at[j];
            arrived_prcs_at[j] = temp;
        }
        //now change the order of actual array according to sorted_arrived_process
        //so that first process here will go for execution as it's burst time is minimum
        for(int j=process_number;j<no_process;j++)
        {
            process_nm[j] = arrived_prcs_name[j];
            arrival_time[j] = arrived_prcs_at[j];
            burst_time[j] = arrived_prcs_bt[j];
        }
    }

    //calculating average waiting time and turn around time
    float average_wt=0,average_tat=0;
    average_wt = (wt * 1.0 )/ no_process;
    average_tat = (tat * 1.0 )/ no_process;
    //printing the values
    printf("\n-----------------------------");
    printf("\nAverage waiting time  = %f",average_wt);
    printf("\nAverage turnaround time  = %f",average_tat);
    printf("\n-----------------------------");

}

