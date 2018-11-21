#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>
#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) { perror(msg); exit(1);}
#define h_addr h_addr_list[0]
/*
struct hostent {
	char*h_name;
	char**h_aliases;
	int h_addrtype;
	int h_length;
	char**h_addr_list;
};


struct sockaddr{
	unsigned short sa_family;
	char sa_data[14];
};

struct in_addr{
	unsigned long s_addr;
};

struct sockaddr_in{
	unsigned short sin_family;
	unsigned short sin_port;
	struct in_addr sin_addr;
	char sin_zero[8];
};*/

int main(int ac, char* av[])
{
	struct sockaddr_in saddr;
	struct hostent *hp;
	char hostname[HOSTLEN];
	int sock_id , sock_fd;
	FILE* sock_fp;
	char *ctime();
	time_t thetime;

	sock_id = socket(PF_INET ,  SOCK_STREAM, 0);
	if ( sock_id == -1)
		oops("socket");
	bzero( (void*) &saddr, sizeof(saddr) );

	gethostname( hostname , HOSTLEN);
	hp = gethostbyname(hostname);

	bcopy( (void*)hp->h_addr, (void*)&saddr.sin_addr, hp->h_length);
	saddr.sin_port = htons(PORTNUM);
	saddr.sin_family = AF_INET;

	if(bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0)
		oops("bind");

	if( listen(sock_id, 1) != 0)
		oops("listen");

	while(1)
	{
		sock_fd = accept(sock_id,NULL,NULL);
		printf("Wow got a call! \n");
		if( sock_id == -1)
			oops("accept");

		sock_fp = fdopen(sock_fd,"w");

		if( sock_fp == NULL)
			oops("fdopen");

		thetime = time(NULL);

		fprintf(sock_fp, "The time here is.. " );
		fprintf(sock_fp,"%s", ctime(&thetime));

		fclose(sock_fp);
	}
}

