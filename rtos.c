#include "rtos.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// Get current time in milliseconds
long get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

// Create a POSIX thread for the given task
void create_task(Task *task, void *(*task_func)(void *)) {
    pthread_create(&task->thread, NULL, task_func, (void *)task);
}

// Simulated RTOS task runner
void *task_runner(void *arg) {
    Task *t = (Task *)arg;
    long start_time = get_time_ms();
    long next_release = start_time;
    long deadline = start_time + t->period_ms;

    // Open trace file in append mode
    FILE *fp = fopen("trace.csv", "a");
    if (!fp) {
        perror("❌ Could not open trace.csv for writing");
        return NULL;
    }

    while (1) {
        long now = get_time_ms();

        // Check if the deadline is missed
        int missed = now > deadline;

        // Print status to console
        if (missed) {
            printf("❌ [%s] Deadline MISSED at %ld ms (expected < %d ms)\n", t->name, now, t->period_ms);
        } else {
            printf("▶️ [%s] Running at %ld ms\n", t->name, now);
        }

        // Log to trace.csv: TaskName,StartTime,Duration,MissedFlag
        fprintf(fp, "%s,%ld,%d,%d\n", t->name, now - start_time, t->exec_time_ms, missed);
        fflush(fp);  // Force flush to file

        // Simulate task execution
        usleep(t->exec_time_ms * 1000);

        // Set up for next period
        next_release += t->period_ms;
        deadline = next_release;

        // Wait until next release
        long sleep_time = next_release - get_time_ms();
        if (sleep_time > 0)
            usleep(sleep_time * 1000);
    }

    fclose(fp);
    return NULL;
}

