#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>

int main() {
char command[1024];
char *token;
char *outfile;
int i, fd, amper, redirect, retid, status;
char *argv1[10];

while (1)
{
    printf("hello: ");
    fgets(command, 1024, stdin);
    command[strlen(command) - 1] = '\0';
//printf("\"%s\"\n", command);
//exit(0);
    /* parse command line */
    argv1[0] = NULL;
    i = 0;
    token = strtok (command," ");
    while (token!= NULL)
    {
        argv1[i] = token;
//printf ("%s\n",token);
        token = strtok (NULL, " ");
        i++;
    }
    argv1[i] = NULL;
//for (i=0; argv1[i] != NULL; i++)
//    printf("\"%s\"\n", argv1[i]);
//exit(0);

    /* Does command line end with & */ 
    if (argv1[0] && ! strcmp(argv1[i - 1], "&")) {
        amper = 1;
        argv1[i - 1] = NULL;
        }
    else 
        amper = 0; 
//printf("\"%d\"\n", amper);

    if (argv1[0] && ! strcmp(argv1[i - 2], ">")) {
        redirect = 1;
        argv1[i - 2] = NULL;
        outfile = argv1[i - 1];
        }
    else 
        redirect = 0; 

    /* for commands not part of the shell command language */ 

    if (fork() == 0) { 
        /* redirection of IO ? */
        if (redirect) {
            fd = creat(outfile, 0660); 
            close (STDOUT_FILENO) ; 
            dup(fd); 
            close(fd); 
            /* stdout is now redirected */
        } 
        execvp(argv1[0], argv1);
    }
    /* parent continues here */
    if (amper == 0)
        retid = wait(&status);
}
}