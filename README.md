# cpu_stress_test
Stress cpu cores finding primes using pthreads.

## Notes
Compile with:
 
    gcc -std=c99 -Wall -Wextra -pedantic -pthread -o pthread_primes pthread_primes.c

This was my first time playing w/pthreads. I do not claim to know what I'm doing

## Usage
Will return primes up to the number passed on the command line. If no number is passed then ULLONG_MAX will be used. (Useful for stress tests.) The primes will be out of order as different cpus are calculating different blocks.

## Bugs
This will return some threads quicker than others (based on size of numbers in that threads range).
Better would be to do this in blocks, w/mutex of which blocks have been assigned.
