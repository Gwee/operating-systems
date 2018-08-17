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
char *argv1[10]; // pointers array

while (1)
{
    printf("hello: ");
	//fgets -bget string
    fgets(command, 1024, stdin);// command - pointer to buffer array, 1024-buffer size, stdin-lo leityahes 
    command[strlen(command) - 1] = '\0';// remove '/n' char and puts '\0' char instaed of '/n'
//printf("\"%s\"\n", command);
//exit(0);
    /* parse command line */
    argv1[0] = NULL;
    i = 0;
    token = strtok (command," ");0 // strtok - string token return pointer to first string array 
    while (token!= NULL)
    {
        argv1[i] = token;
//printf ("%s\n",token);
        token = strtok (NULL, " ");// returns next string pointer from command array 
        i++;
    }
    argv1[i] = NULL;
//for (i=0; argv1[i] != NULL; i++)
//    printf("\"%s\"\n", argv1[i]);
//exit(0);

    /* Does command line end with & */// check if exists & sign at the end of the string??????????? 
    if (argv1[0] && ! strcmp(argv1[i - 1], "&")) //argv1[0] check if  argv1 not empty and check if exists & sign at the end of the string???????????   
	{
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

    if (fork() == 0) //create new procecc by fork command, fork command returns 0 for child and not 0 for another process, so by this row only child process will execute code inside if statment
	{ 
        /* redirection of IO ? */
        if (redirect) {
            fd = creat(outfile, 0660); 
            close (STDOUT_FILENO) ; 
            dup(fd); 
            close(fd); 
            /* stdout is now redirected */
        } 
        execvp(argv1[0], argv1);// child process execute command entered by user with help of execvp function
    }
    /* parent continues here */
    if (amper == 0)// amper - ampersent  
        retid = wait(&status);
}
}