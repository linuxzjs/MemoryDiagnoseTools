#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *addr = NULL;
    int i = 0;
    int fd = 0;
    struct stat sb;
	char t;
	const char *filename = "/tmp/hello.txt";

    fd = open(filename, O_RDWR);
    if (fd == -1){
        printf("open hello.txt failure\n");
        return -1;
    }

    if (fstat(fd, &sb) == -1) {          /* To obtain file size */
        printf("get file size failure\n");
        close(fd);
        return -1;
    }
    
	printf("file size = %ld\n", sb.st_size);

    addr = (char *) mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == NULL){
        printf("mmap hello.txt failure\n");
        close(fd);
        return -1;
    }

	close(fd);

    printf("mmap file sucess\n");
    system("cat /proc/meminfo | grep Cached");
    system("cat /proc/meminfo | grep file");
    system("cat /proc/meminfo | grep Mapped");
    system("free -m");
    printf("\n");

	printf("write 0x5a to hello.txt file!!!!!!\n");
	memset(addr, 0x5a, sb.st_size);
	printf("\n");

    printf("after write !!!!!!\n");
    system("cat /proc/meminfo | grep Cached");
    system("cat /proc/meminfo | grep file");
    system("cat /proc/meminfo | grep Mapped");
    system("free -m");
    printf("\n");

    munmap(addr, sb.st_size);

    printf("munmap file & close fd !!!!!!\n");
    system("cat /proc/meminfo | grep Cached");
    system("cat /proc/meminfo | grep file");
    system("cat /proc/meminfo | grep Mapped");
    system("free -m");

    return 0;
}
