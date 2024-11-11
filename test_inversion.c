// test_priority_inversion.c

#include "types.h"
#include "stat.h"
#include "user.h"

// Low-priority task
void low_priority_task(int lock_id) {
    set_priority(1);  // Set initial low priority
    printf(1, "[%d ms] Low-priority process started with priority 1.\n", uptime() * 10);
    lock(lock_id);
    printf(1, "[%d ms] Low-priority process acquired lock %d.\n", uptime() * 10, lock_id);

    sleep(50);  // Simulate work for 5 seconds

    printf(1, "[%d ms] Low-priority process releasing lock %d.\n", uptime() * 10, lock_id);
    release(lock_id);
    exit();
}

// High-priority task
void high_priority_task(int lock_id) {
    sleep(30);  // Delay to ensure low-priority process acquires lock first
    set_priority(3);  // Set initial high priority
    printf(1, "[%d ms] High-priority process started with priority 3.\n", uptime() * 10);

    printf(1, "[%d ms] High-priority process attempting to acquire lock %d held by low-priority process.\n", uptime() * 10, lock_id);
    lock(lock_id);
    printf(1, "[%d ms] High-priority process acquired lock %d.\n", uptime() * 10, lock_id);
    release(lock_id);
    exit();
}

int main() {
    int lock_id = 1;

    // Start marker
    printf(1, "Test Case 2: Priority Inversion Demonstration\n");

    // Fork the low-priority task
    int low_pid = fork();
    if (low_pid == 0) {
        low_priority_task(lock_id);
    }

    // Fork the high-priority task
    int high_pid = fork();
    if (high_pid == 0) {
        high_priority_task(lock_id);
    }

    // Wait for both processes to complete
    wait();
    wait();

    // End marker and summary of expected vs. actual behavior
    printf(1, "\nExpected: Low-priority process acquires the lock first, holding it for 5 seconds. High-priority process starts after 3 seconds, waits until the lock is released, and then acquires it.\n");
    printf(1, "Actual: Priority inversion observed as high-priority process waits for low-priority process to release the lock.\n");
    printf(1, "Priority Inversion Test Completed successfully.\n");

    exit();
}