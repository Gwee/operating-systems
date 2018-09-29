#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <malloc.h>
#include <string.h>

#define bufSize 1024
#define THREADS 3

struct job {
    struct job* next;
    char line[1024];
};

struct job* job_queue;
char buf[bufSize];
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t job_queue_count;

void initialize_job_queue (){
    job_queue = NULL;
    sem_init (&job_queue_count, 0, 0);
}

void * thread_function (){
    while(strcmp(job_queue->line,"END")!=0){
        struct job* next_job;
        sem_wait(job_queue_count);
        pthread_mutex_lock(&job_queue_mutex);
        next_job = job_queue;
        job_queue = job_queue ->next;
		pthread_mutex_unlock (&job_queue_mutex);
		printf("%s",next_job->line);
		free(next_job);

    }
}

void enqueue_job(char * line){
    struct job* new_job;
	new_job = (struct job*) malloc (sizeof (struct job));
	pthread_mutex_lock (&job_queue_mutex);
	strcpy(new_job->line , line);
	new_job->next = job_queue;
	job_queue = new_job;
	sem_post (&job_queue_count);
	pthread_mutex_unlock (&job_queue_mutex);

}
void * enqueue_file(void * fp){
    while (fgets(buf, sizeof(buf),(FILE *)fp)){
        //printf ("%s",buf);
        enqueue_job(buf);
    }
}
int main()
{
    initialize_job_queue();
    pthread_t tid[THREADS];
    FILE * fp = fopen("poem.txt","r");
    enqueue_job("END");
    enqueue_file(fp);
    fclose(fp);
    for (int i = 0; i < THREADS; ++i) {
        pthread_create(&tid[i],NULL,thread_function,NULL);
    }
    for (int i = 0; i < THREADS; ++i) {
        pthread_join(tid[i],NULL);
    }
    free(job_queue);
    printf("Finished!");
    return 0;
}