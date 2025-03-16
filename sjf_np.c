#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void sortByBurstTime(Process processes[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (processes[j].burst_time < processes[minIndex].burst_time) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Process temp = processes[i];
            processes[i] = processes[minIndex];
            processes[minIndex] = temp;
        }
    }
}

void calculateTimes(Process processes[], int count) {
    processes[0].waiting_time = 0;
    for (int i = 1; i < count; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
    for (int i = 0; i < count; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void displayProcesses(Process processes[], int count) {
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < count; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, 
               processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    Process test1[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}};
    int size1 = sizeof(test1) / sizeof(test1[0]);

    printf("Test Case 1:\n");
    sortByBurstTime(test1, size1);
    calculateTimes(test1, size1);
    displayProcesses(test1, size1);

    Process test2[] = {{1, 2}, {2, 4}, {3, 1}, {4, 3}};
    int size2 = sizeof(test2) / sizeof(test2[0]);

    printf("\nTest Case 2:\n");
    sortByBurstTime(test2, size2);
    calculateTimes(test2, size2);
    displayProcesses(test2, size2);

    return 0;
}