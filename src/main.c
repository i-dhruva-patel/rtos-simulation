#include "rtos.h"
#include <stdio.h>

void *task1_func(void *arg) { return task_runner(arg); }
void *task2_func(void *arg) { return task_runner(arg); }
void *task3_func(void *arg) { return task_runner(arg); }

int main() {
    printf("🚀 Starting RM Scheduler Simulation...\n");

    Task task1 = {"T1", 1000, 200, 1}; // Period 1000 ms, exec 200 ms
    Task task2 = {"T2", 1000, 300, 2}; // Period 1000 ms, exec 300 ms
    Task task3 = {"T3", 1000, 250, 3}; // Period 1000 ms, exec 250 ms

    create_task(&task1, task1_func);
    create_task(&task2, task2_func);
    create_task(&task3, task3_func);

    pthread_join(task1.thread, NULL);
    pthread_join(task2.thread, NULL);
    pthread_join(task3.thread, NULL);

    return 0;
}

