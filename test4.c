// test4.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Test 4: Single Argument - Running 'nice 4'\n");

    // Prepare arguments for the "nice" command
    char *args[] = {"nice", "4", 0};  // Simulates "nice 4" command with a single argument

    // Execute the "nice" command with the given arguments
    exec("nice", args);

    // If exec fails, print an error message
    printf(2, "Error: exec failed to run 'nice 4'\n");
    exit();
}
