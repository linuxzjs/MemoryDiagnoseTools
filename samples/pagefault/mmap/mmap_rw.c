#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

#define MEM_MMAP_SIZE 100*1024*1024

int main(int argc, char **argv)
{
    char *addr = NULL;
    int i = 0;

    addr = (unsigned long *)mmap(0, MEM_MMAP_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (addr == NULL){
        printf("jinsheng -> mmap failure\n");
        return -1;
    }

    printf("get init memory stat\n");
    system("cat /proc/meminfo | grep anon");
    system("free -m");

    getchar();

 
    printf("read!!!!!!\n");
    for (i = 0; i < 100; i++){
        printf("%d ", addr[1024*1024*i]);
    }
    printf("\n");

    printf("after read!!!!!!\n");
    system("cat /proc/meminfo | grep anon");
    system("free -m");

    getchar();
 
    printf("write!!!!!!\n");
    memset(addr, 0x5A, MEM_MMAP_SIZE);

    printf("after write !!!!\n");
    system("cat /proc/meminfo | grep anon");
    system("free -m");

    getchar();

    munmap(addr, MEM_MMAP_SIZE);

    system("cat /proc/meminfo | grep anon");
    system("free -m");

    return 0;
}