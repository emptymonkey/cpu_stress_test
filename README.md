# cpu_stress_test
Stress cpu cores using factorization and pthreads.

## Notes
Compile with:
 
    gcc -std=c99 -Wall -Wextra -pedantic -pthread -o pthread_factor pthread_factor.c

This was my first time playing w/pthreads. I do not claim to know what I'm doing

## Usage
Will return factors of the number passed on the command line. If no number is passed then ULLONG_MAX will be used. (Useful for stress tests.) 

The threads will each be given a workload of sequential blocks of size / cpus.
The factors will be out of order as different cpus are calculating different blocks.

## Bugs
This will return some threads quicker than others (based on size of numbers in that threads range).
Better would be to do this in smaller blocks, reassigning a new block to a thread when it completes the previous block, w/mutex to allow for tracking of which blocks have been assigned.
