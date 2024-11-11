#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int pid, new_value, old_value;

    if (argc == 2) {  // If only one argument, assume it's the nice value for the current process
        pid = getpid();  // Get the current process ID
        new_value = atoi(argv[1]);
    } else if (argc == 3) {  // If two arguments, treat as pid and new nice value
        pid = atoi(argv[1]);
        new_value = atoi(argv[2]);
    } else {
        printf(2, "Usage: nice <pid> <value> or nice <value>\n");
        exit();
    }

    // Validate that the new nice value is between 1 and 5
    if (new_value < 1 || new_value > 5) {
        printf(2, "Error: nice value should be between 1 and 5.\n");
        exit();
    }

    // Call nice to set the new nice value and get the old value
    old_value = nice(pid, new_value);

    // Check if the pid is valid
    if (old_value == -1) {
        printf(2, "Error: PID %d does not exist.\n", pid);
        exit();
    }

    // Print the pid and old value in the specified format
    printf(1, "%d %d\n", pid, old_value);
    exit();
}
