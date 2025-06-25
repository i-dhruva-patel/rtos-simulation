#ifndef RTOS_H
#define RTOS_H

#include <pthread.h>
#include <stdint.h>

typedef struct {
    char name[16];
    int period_ms;
    int exec_time_ms;
    int priority;  // lower = higher priority (RM)
    pthread_t thread;
} Task;

void create_task(Task *task, void *(*task_func)(void *));
void *task_runner(void *arg);
long get_time_ms();

#endif
