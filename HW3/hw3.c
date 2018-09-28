#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <malloc/malloc.h>

struct job {
    struct job* next;
};

struct job* job_queue; 

pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t job_queue_count;

void initialize_job_queue (){
    job_queue = NULL;
    sem_init (job_queue_count, 0, 0);
}

void * thread_function (void * arg){
    while(1){
        struct job* next_job;
        sem_wait(job_queue_count);
        pthread_mutex_lock(&job_queue_mutex);
        next_job = job_queue;
        job_queue = job_queue ->next;
		pthread_mutex_unlock (&job_queue_mutex);
		process_job (next_job);
		free(next_job);

    }
    return NULL;
}

void enqueue_job(){
    struct job* new_job;
	new_job = (struct job*) malloc (sizeof (struct job));
	pthread_mutex_lock (&job_queue_mutex);
	new_job->next = job_queue;
	job_queue = new_job;
	sem_post (&job_queue_count);
	pthread_mutex_unlock (&job_queue_mutex);

}

int main(int argc, char const *argv[])
{
    initialize_job_queue;
    //create threads
    
    //open file
While lines in poem.txt
    enqueue_job
    enqueue "END"
    join threads
    free "END"
    print "Finished!"    
    return 0;
}


