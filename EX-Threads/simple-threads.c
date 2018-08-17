#include <stdio.h>
#include <pthread/pthread.h>

void * print_xs(void* unused){
    while(1){
        printf("*****");
    }
    return NULL;
} 

int main(int argc, char const *argv[])
{
    pthread_t thread_id;
    pthread_create(&thread_id,NULL,print_xs,NULL);
    while(1){
        printf("$$$$");
    }
    
    return 0;
}
