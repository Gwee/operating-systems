#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main() {
    char command[1024];
    char *token;
    char *outfile, *infile;
    int i, fd, amper, redirect, retid, status, input_redirect, append, cd;
    char *argv1[10];
    char * operator;

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


        operator = argv1[i-2];
        /* Does command line end with & */
        //if (argv1[0] )
        if (argv1[0] && ! strcmp(argv1[i - 1], "&")) {
            amper = 1;
            argv1[i - 1] = NULL;
        }
        else
            amper = 0;
//printf("\"%d\"\n", amper);

        if (argv1[0] && ! strcmp(argv1[0], "cd")){
            cd=1;
            if(argv1[1]){
            chdir(argv1[1]);
            }
        } 
        else
            cd=0;
        char * ptr = argv1[1];
        if (argv1[0] && ! strcmp(argv1[0], "quit") ){
            if(!argv1[1]){
            exit(0);
            }
        }
        
        if (argv1[0] && ! strcmp(operator, "<")) {
            input_redirect= 1;
            argv1[i - 2] = NULL;
            infile = argv1[i - 1];

        }
        else
            input_redirect = 0;

        if (argv1[0] && ! strcmp(operator, ">")) {
            redirect = 1;
            argv1[i - 2] = NULL;
            outfile = argv1[i - 1];
        }
        else
            redirect = 0;

        if (argv1[0] && ! strcmp(operator, ">>")) {
            append= 1;
            argv1[i - 2] = NULL;
            outfile = argv1[i - 1];
            
        }
        else
            append = 0;
        /* for commands not part of the shell command language */

        if (fork() == 0) {
            if (input_redirect){
                //printf("%s, %s",argv1[0],argv1);
                fd = open(infile,O_RDONLY);
                dup2(fd,0);
                close(fd);
                char *b[] = {"b", NULL};
            }
            /* redirection of IO ? */
            if (append) { 
                fd = open(outfile, O_APPEND  | O_CREAT | O_RDWR);
                close (STDOUT_FILENO) ;
                dup(fd);
                close(fd);
                /* stdout is now redirected */
                //write(fd,"argv1",5);
            }
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