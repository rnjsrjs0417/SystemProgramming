#include <socklib.h>

talk_with_server(int);

main()
{
	int fd;
	fd = connect_to_server(host, port);
	if(fd == -1)
		eixt(1);

	talk_with_server(fd);
	close(fd);
}

talk_with_server(fd)
{
	char buf[LEN];
	int n;
	
	n= read(fd,buf,LEN);
	write(1,buf,n);
}
