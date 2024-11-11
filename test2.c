// test2.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Test 2: Out-of-Bounds Values\n");

    // Setting a nice value below the valid range
    printf(1, "Expected: Error message about nice value range.\n");
    printf(1, "Output: ");
    nice(getpid(), 0);  // Below minimum

    // Setting a nice value above the valid range
    printf(1, "Expected: Error message about nice value range.\n");
    printf(1, "Output: ");
    nice(getpid(), 6);  // Above maximum

    exit();
}
