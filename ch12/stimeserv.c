#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) { perror(msg); exit(1);}
#define h_addr h_addr_list[0]

process_request(int fd)
{
	time_t now;
	char *cp;

	time(&now);
	cp = ctime(&now);
	write(fd,cp,strlen(cp));
}

int main(int ac, char* av[])
{
	int sock, fd;
	int portnum =  atoi(av[2]);
	sock  = make_server_socket(portnum);

	if( sock  == -1 )
		exit(1);
	while(1)
	{ 
		fd= accept(sock,NULL,NULL);
		if(fd == -1) break;

		process_request(fd);
		close(fd);
	}
}
