#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char **argv){
	int fd=open(argv[1],O_RDWR);
	ioctl(fd,_IO('?',1));
	close(fd);
	return 0;
}
