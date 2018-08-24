#include <malloc.h>

struct job {
	/* Link field for linked list. */
	struct job* next;
	/* Other fields describing work to be done... */
};

/* A linked list of pending jobs. */
struct job* job_queue; //head of the list

/* Process queued jobs until the queue is empty. */

void* thread_function (void* arg)
{
	while (job_queue != NULL) {
		/* Get the next available job. */
		struct job* next_job = job_queue

		/* Remove this job from the list. */
		job_queue = job_queue->next; // Here we can get a segmentation fault if we don't take care of the locks by using a mutex (solving with a mutual exclusion)

		/* Carry out the work. */
		process_job (next_job);

		/* Clean up. */
		free (next_job);
	}

return NULL;

}


void enqueue_job (struct job* new_job)
{
	new_job->next = job_queue;
	job_queue = new_job;
}