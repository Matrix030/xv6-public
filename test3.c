// test3.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Test 3: Invalid PID\n");

    // Setting a nice value for a non-existent PID
    printf(1, "Expected: Error message stating PID does not exist.\n");
    printf(1, "Output: ");
    nice(9999, 3);  // Assuming 9999 is an invalid/non-existent PID

    exit();
}
