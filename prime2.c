#include "types.h"
#include "stat.h"
#include "user.h"

void find_primes() {
    int i, j;
    int prime_count = 0;  // Counter for the number of primes detected

    for (i = 2; prime_count < 1000; i++) {  // Stop after finding 1000 primes
        int is_prime = 1;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            prime_count++;  // Increment the prime counter
            printf(1, "PID %d: Prime %d\n", getpid(), prime_count);
        }
        sleep(1);  // Slow down to make output readable
    }

    // Print completion message when the prime count reaches 1000
    printf(1, "PID %d: prime has finished executing\n", getpid());
}

int main(void) {
    int pid;

    // Create child processes with different priorities
    int i;
    for (i = 5; i > 2; i--) {
        if ((pid = fork()) == 0) {
            nice(getpid(), i);  // Set different priorities for each child
            find_primes();      // Each child process computes primes
            exit();
        }
    }

    // Parent waits for all children to finish
    for (i = 2; i < 5; i++) {
        wait();
    }
    exit();
}
