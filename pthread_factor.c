
// emptymonkey's first threaded factorization program. >.<
// compile with: gcc -std=c99 -Wall -Wextra -pedantic -pthread -o pthread_factor pthread_factor.c
// try it with: 23356734894
// Call without args to run against ULLONG_MAX. Good for stress tests.
//
// XXX This will return some threads quicker than others (based on size of numbers in that threads range).
// XXX Better would be to do this in blocks, w/mutex of which blocks have been assigned.

#include <errno.h>
#include <error.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>


void *thread_start(void *arg);

struct args {
	unsigned long long target;
	unsigned long long start;
	unsigned long long stop;
};


int main(int argc, char **argv){

	int i;
	int retval;
	int procs_online;

	unsigned long long number = 0, quotient;

	struct args *this_arg;

	pthread_t *tids;

	if(argc != 2){
		number = ULLONG_MAX;
	}else{
		errno = 0;
		number = strtoull(argv[1], NULL, 10);	
		if(errno){
			error(-1, errno, "strtoull(%s)", argv[1]);
		}
	}

	if((procs_online = sysconf(_SC_NPROCESSORS_ONLN)) == -1){
		error(-1, errno, "sysconf(_SC_NPROCESSORS_ONLN)");
	}

	if(number < 2){
		error(-1, 0, "only numbers greater than one, please!");
	}

	quotient = number / procs_online;

	tids = (pthread_t *) calloc(procs_online, sizeof(pthread_t));

	for(i = 0; i < procs_online; i++){

		this_arg = (struct args *) calloc(1, sizeof(struct args));
		this_arg->target = number;

		if(!i){
			this_arg->start = 2;
		}else{
			this_arg->start = i * quotient;
		}

		if((i + 1) == procs_online){
			this_arg->stop = number;
		}else{
			this_arg->stop = (i + 1) * quotient;
		}

		retval = pthread_create(tids + i, NULL, thread_start, this_arg);

		if(retval){
			error(-1, retval, "pthread_create(tids + %d, NULL, %lx, NULL)", i, (unsigned long) thread_start);
		}
	}


	for(i = 0; i < procs_online; i++){
		pthread_join(tids[i], NULL);
	}

	return(0);
}

void *thread_start(void *arg){
	unsigned long long i;
	struct args *this_arg = (struct args *) arg;

	for(i = this_arg->start; i < this_arg->stop; i++){
		if(!(this_arg->target % i)){
			printf("%lld\n", i);
		}
	}

	return(NULL);
}
