#include <stdio.h>
#include <pthread/pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5
void * print_thread(void * tid){
    printf("Hello from thread %d\n", tid);
    pthread_exit(NULL);
}

int main(int argc, const char * argv[]){
   pthread_t threads[NUM_THREADS];
    int i;
    for(i=0; i < NUM_THREADS; i++) {
        printf ("before create thread %d\n",i);
        pthread_create(&threads[i], NULL, print_thread, (void *) i);
        } 
        for(i=0; i < NUM_THREADS; i++) {
            printf ("before join thread %d\n",i);
            pthread_join(threads[i], NULL); 
            printf ("after join thread %d\n",i);
            } 
        printf ("Good Bye\n");
        return 0;
}