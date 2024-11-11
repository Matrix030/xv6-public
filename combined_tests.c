// combined_tests.c
#include "types.h"
#include "stat.h"
#include "user.h"

void run_test1() {
    printf(1, "Running Test 1: Valid Values\n");

    printf(1, "Expected: Current PID and old nice value.\n");
    printf(1, "Output: ");
    nice(getpid(), 3);  // Set to a middle value

    printf(1, "Expected: Current PID and old nice value.\n");
    printf(1, "Output: ");
    nice(getpid(), 5);  // Set to the maximum valid value

    printf(1, "Expected: Current PID and old nice value.\n");
    printf(1, "Output: ");
    nice(getpid(), 1);  // Set to the minimum valid value

    printf(1, "Test 1 Completed\n\n");
}

void run_test2() {
    printf(1, "Running Test 2: Out-of-Bounds Values\n");

    printf(1, "Expected: Error message about nice value range.\n");
    printf(1, "Output: ");
    nice(getpid(), 0);  // Below minimum

    printf(1, "Expected: Error message about nice value range.\n");
    printf(1, "Output: ");
    nice(getpid(), 6);  // Above maximum

    printf(1, "Test 2 Completed\n\n");
}

void run_test3() {
    printf(1, "Running Test 3: Invalid PID\n");

    printf(1, "Expected: Error message stating PID does not exist.\n");
    printf(1, "Output: ");
    nice(9999, 3);  // Assuming 9999 is an invalid/non-existent PID

    printf(1, "Test 3 Completed\n\n");
}

void run_test4() {
    printf(1, "Running Test 4: Single Argument - Running 'nice 4'\n");

    // Prepare arguments for the "nice" command
    char *args[] = {"nice", "4", 0};  // Simulates "nice 4" command with a single argument

    // Execute the "nice" command with the given arguments
    exec("nice", args);

    // If exec fails, print an error message
    printf(2, "Error: exec failed to run 'nice 4'\n");

    printf(1, "Test 4 Completed\n\n");
}

int main() {
    printf(1, "Starting Combined Tests for 'nice' System Call\n\n");

    run_test1();
    run_test2();
    run_test3();
    run_test4();

    printf(1, "All Tests Completed.\n");
    exit();
}
