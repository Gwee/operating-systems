-----------------------------------------------------
\n New Line
\r Carriage Return
\t Tab
\0 Null
-----------------------------------------------------
/* hexdump.c */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main (int argc, char* argv[])
{
unsigned char buffer[16];
int offset = 0;
int bytes_read;
int i;
/* Open the file for reading. */
int fd = open (argv[1], O_RDONLY);
/* Read from the file one chunk at a time.
Continue until reads less than we asked for.
This indicates that we’ve hit the end of the file. */
do {
/* Read the next line’s worth of bytes. */
bytes_read = read (fd, buffer, sizeof (buffer));
/* Print the offset in the file, followed by the bytes themselves. */
printf ("0x%06x : ", offset);
for (i = 0; i < bytes_read; ++i)
printf ("%02x ", buffer[i]);
printf ("\n");
/* Keep count of our position in the file. */
offset += bytes_read;
}
while (bytes_read == sizeof (buffer));
/* All done. */
close (fd);
return 0;
}
-----------------------------------------------------

#include <ctype.h>
if( isprint( theChar ) )
  printf( "%c", theChar )
else
  switch( theChar )
  {
  case '\n':
     printf( "\\n" );
     break;
  ... repeat for other interesting control characters ...
  default:
     printf( "%02x", theChar ); // print octal representation of character.
     break;
  }