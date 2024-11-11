// // Mutual exclusion lock.
// struct spinlock {
//   uint locked;       // Is the lock held?

//   // For debugging:
//   char *name;        // Name of lock.
//   struct cpu *cpu;   // The cpu holding the lock.
//   uint pcs[10];      // The call stack (an array of program counters)
//                      // that locked the lock.
// };
#ifndef SPINLOCK_H
#define SPINLOCK_H

// Define the struct spinlock here
struct spinlock {
    uint locked;       // Is the lock held?
    // For debugging:
    char *name;        // Name of lock.
    struct cpu *cpu;   // The CPU holding the lock.
    uint pcs[10];      // Call stack (an array of program counters) that locked the lock.
};

// Function prototypes for spinlock functions
void acquire(struct spinlock*);
void release(struct spinlock*);
void initlock(struct spinlock*, char*);

#endif  // SPINLOCK_H

