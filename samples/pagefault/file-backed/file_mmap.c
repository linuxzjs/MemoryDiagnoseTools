#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MEM_MMAP_SIZE 100*1024*1024

int main(int argc, char **argv)
{
    char *addr = NULL;
    int i = 0;
    int fd = 0;
    struct stat sb;

    fd = open("hello.txt", O_RDWR);
    if (fd == -1){
        printf("open hello.txt failure\n");
        return -1;
    }

    if (fstat(fd, &sb) == -1) {          /* To obtain file size */
        printf("get file size failure\n");
        close(fd);
        return -1;
    }
    
    if (sb.st_size > MEM_MMAP_SIZE){
        printf("get file size invalte\n");
        close(fd);
        return -1;
    }

	printf("file size = %ld\n", sb.st_size);

    addr = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (addr == NULL){
        printf("mmap hello.txt failure\n");
        close(fd);
        return -1;
    }

    printf("mmap file sucess\n");
    system("cat /proc/meminfo | grep file");
    system("free -m");
    printf("\n");

    printf("read !!!!!!\n");
    for (i = 0; i < (sb.st_size/(1024*1024)); i++){
        printf("0x%x ", addr[i]);
    }
    printf("\n\n");

    printf("after read !!!!!!\n");
    system("cat /proc/meminfo | grep file");
    system("free -m");
    printf("\n");

    printf("write 0x5a to hello.txt file!!!!!!\n");
    memset(addr, 0x5a, sb.st_size);
    printf("\n");

    printf("after write !!!!!!\n");
    system("cat /proc/meminfo | grep file");
    system("free -m");
    printf("\n");

    printf("read again !!!!!!\n");
    for (i = 0; i < (sb.st_size/(1024*1024)); i++){
        printf("0x%x ", addr[i]);
    }
    printf("\n\n");

    munmap(addr, sb.st_size);
    close(fd);

    printf("munmap file & close fd !!!!!!\n");
    system("cat /proc/meminfo | grep file");
    system("free -m");

    return 0;
}
