#define _POSIX_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SIZE_TAMPON 100
char tampon [SIZE_TAMPON];
char tampon2 [SIZE_TAMPON];
int main (int argc, char* argv []) {
    int fd1, fd2; int n,i;

    fd1 = open (argv[1],O_RDWR|O_CREAT|O_SYNC,0600);
    fd2 = open (argv[1], O_RDWR);
    
    if ( (fd1== -1) || (fd2 == -1)) {
        perror("open");
        return EXIT_FAILURE;    
    }

    if (write (fd1,"abcdef", strlen ("abcdef"))== -1) { /*error*/ }
    if (write (fd2,"123", strlen ("123") ) == -1) { /*error*/}
    if ((n= read (fd2,tampon, SIZE_TAMPON)) <=0 ) { /*error*/ }
    for (i=0 ; i<n; i++)
        printf ("%c\n",tampon [i]);

  
    return EXIT_SUCCESS;

}