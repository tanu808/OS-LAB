#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

void calculateTimes(Process processes[], int count) {
    int completed = 0, time = 0;
    int is_completed[count];
    int min_time, shortest_index;

    for (int i = 0; i < count; i++) {
        is_completed[i] = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed < count) {
        min_time = INT_MAX;
        shortest_index = -1;

        for (int i = 0; i < count; i++) {
            if (processes[i].arrival_time <= time && !is_completed[i] && processes[i].remaining_time < min_time) {
                min_time = processes[i].remaining_time;
                shortest_index = i;
            }
        }

        if (shortest_index == -1) {
            time++;
            continue;
        }

        processes[shortest_index].remaining_time--;

        if (processes[shortest_index].remaining_time == 0) {
            completed++;
            int finish_time = time + 1;
            processes[shortest_index].completion_time = finish_time;
            processes[shortest_index].turnaround_time = finish_time - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
            is_completed[shortest_index] = 1;
        }

        time++;
    }
}

void displayProcesses(Process processes[], int count) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < count; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    Process test1[] = {{1, 0, 6}, {2, 2, 8}, {3, 4, 7}, {4, 5, 3}};
    int size1 = sizeof(test1) / sizeof(test1[0]);

    printf("Test Case 1:\n");
    calculateTimes(test1, size1);
    displayProcesses(test1, size1);

    Process test2[] = {{1, 0, 3}, {2, 1, 1}, {3, 2, 6}, {4, 3, 2}};
    int size2 = sizeof(test2) / sizeof(test2[0]);

    printf("\nTest Case 2:\n");
    calculateTimes(test2, size2);
    displayProcesses(test2, size2);

    return 0;
}
