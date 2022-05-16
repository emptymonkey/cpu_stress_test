# cpu_stress_test
Stress cpu cores using number factorization and pthreads.

## Notes
Compile with:
 
  gcc -std=c99 -Wall -Wextra -pedantic -pthread -o pthread_factor pthread_factor.c

Call without args to run against ULLONG_MAX. Good for stress tests.

This was my first time playing w/pthreads. I do not claim to know what I'm doing

## Bugs
This will return some threads quicker than others (based on size of numbers in that threads range).
Better would be to do this in blocks, w/mutex of which blocks have been assigned.
