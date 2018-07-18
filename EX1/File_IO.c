/* argc_argv.c */
#include <stdio.h>
int main (int argc, char* argv[])
{
printf ("The name of this program is '%s'.\n", argv[0]);
printf ("This program was invoked with %d arguments.\n", argc - 1);
/* Were any command-line arguments specified? */
if (argc > 1) { /* Yes, print them. */
   int i;
   printf ("The arguments are:\n");
   for (i = 1; i < argc; ++i)
      printf (" %s\n", argv[i]);
}
return 0;
}
--------------------------------------------------------------------
/* copy_file.c */
#include <sys/stat.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
        int inputFd, outputFd; /* input and output file descriptors */
        int openFlags;         /* open flags (read, write ...) */
        mode_t filePerms;      /* permissions for new file */
        ssize_t numRead;
        char buf[BUF_SIZE];
        if (argc != 3) {
                printf("%s old-file new-file\n", argv[0]);
                exit(1);
        }
/* Open input file */
        inputFd = open(argv[1], O_RDONLY);
        if (inputFd == -1) {
                perror("opening file: ");
                exit(1);
        }
/* Open output file */
        openFlags = O_CREAT | O_WRONLY | O_TRUNC;
        filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                        S_IROTH | S_IWOTH; /* rw-rw-rw- */
        outputFd = open(argv[2], openFlags, filePerms);
        if (outputFd == -1) {
                perror("opening file: ");
                exit(1);
        }
/* Transfer data until we encounter end of input */
        while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
/* If write error */
                if (write(outputFd, buf, numRead) != numRead) {
                        perror("couldn't write whole buffer");
                        exit(1);
                }
        }
/* If read error */
        if (numRead == -1) {
                perror("read");
                exit(1);
        }
        exit(0);
}
