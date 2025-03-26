#include <stdio.h>

void RoundRobin(int processes[], int n, int bt[], int quantum) {
    int rem_bt[n], wt[n], tat[n], total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int time = 0; // Current time

    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0; // There is at least one pending process
                if (rem_bt[i] > quantum) {
                    time += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    time += rem_bt[i];
                    wt[i] = time - bt[i]; // Waiting time = (Current time - burst time)
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1) // If all processes are completed, exit loop
            break;
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time = burst time + waiting time
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Print results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int processes[] = {1, 2, 3, 4};
    int burst_time[] = {10, 5, 8, 12};
    int quantum = 3;
    int n = sizeof(processes) / sizeof(processes[0]);

    RoundRobin(processes, n, burst_time, quantum);
    return 0;
}
