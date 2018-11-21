#include <socklib.h>
main()
{
	int fd;
	fd = connect_to_server(host, port);
	if(fd == -1)
		eixt(1);

	talk_with_server(fd);
	close(fd);
}
