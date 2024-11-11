// test_lock_basic.c

#include "types.h"
#include "stat.h"
#include "user.h"

// Basic lock/unlock test function
void test_basic_lock(int lock_id) {
    int pid = fork();
    if (pid == 0) {
        printf(1, "[%d ms] Process 1: Trying to acquire lock %d\n", uptime() * 10, lock_id);
        int result = lock(lock_id);
        if (result == -1) {  // Assuming lock() returns -1 for invalid IDs
            printf(1, "[%d ms] Process 1: Failed to acquire invalid lock %d\n", uptime() * 10, lock_id);
            exit();
        }
        printf(1, "[%d ms] Process 1: Acquired lock %d\n", uptime() * 10, lock_id);

        sleep(20);  // Simulate work for 2 seconds

        printf(1, "[%d ms] Process 1: Releasing lock %d\n", uptime() * 10, lock_id);
        release(lock_id);
        exit();
    } else {
        sleep(10);  // Ensure Process 1 acquires lock first

        int pid2 = fork();
        if (pid2 == 0) {
            printf(1, "[%d ms] Process 2: Trying to acquire lock %d\n", uptime() * 10, lock_id);
            int result = lock(lock_id);
            if (result == -1) {
                printf(1, "[%d ms] Process 2: Failed to acquire invalid lock %d\n", uptime() * 10, lock_id);
                exit();
            }
            printf(1, "[%d ms] Process 2: Acquired lock %d\n", uptime() * 10, lock_id);
            release(lock_id);
            exit();
        }
        wait();
        wait();
    }
}

int main() {
    printf(1, "Test Case 1: Basic Lock Functionality\n");

    // Testing valid lock
    test_basic_lock(1);
    printf(1, "Basic Lock Functionality Test Completed with valid lock.\n");

    // Testing invalid lock ID
    printf(1, "\nTest Case 2: Invalid Lock ID Handling\n");
    test_basic_lock(0); // Assuming 0 is an invalid ID
    printf(1, "Invalid Lock ID Test Completed.\n");

    exit();
}
