#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void* thread_function (void* arg)
{
	fprintf (stderr, "child thread pid is %d\n", (int) getpid ());
	/* Spin forever. */
	while (1);
	return NULL;
}

int main ()
{
	pthread_t thread;
	fprintf (stderr, "main thread pid is %d\n", (int) getpid ());
	pthread_create (&thread, NULL, &thread_function, NULL); //The last param is the function arguments and when you want to pass multiple args you can pass a struct
	/* Spin forever. */
	while (1);
	return 0;
}

//gcc thread-pid.c -o thread-pid -lpthread
//./thread-pid &

//ps -u user
//ps -O lwp,psr -T -p ...