#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#define oops(msg) {perror(msg); exit(1); }

talk_with_server(int fd)
{
	char buf[BUFSIZ];
	int n;

	n= read(fd,buf,BUFSIZ);
	write(1,buf,n);
}
int main(int ac, char* av[])
{
	int fd;
	int portnum = atoi(av[2]);
	fd = connect_to_server(av[1],portnum);

	if( fd  == -1 )
		exit(1);
	talk_with_server(fd);
	close(fd);
}
