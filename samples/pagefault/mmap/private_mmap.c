#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

#define MEM_MMAP_SIZE 100*1024*1024

int main(int argc, char **argv)
{
    char *addr = NULL;

    addr = (unsigned long *)mmap(0, MEM_MMAP_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (addr == NULL){
        printf("jinsheng -> mmap failure\n");
        return -1;
    }

    system("cat /proc/meminfo | grep anon");

    getchar();

    memset(addr, 0x5A, MEM_MMAP_SIZE);

    system("cat /proc/meminfo | grep anon");

    getchar();

    munmap(addr, MEM_MMAP_SIZE);

    system("cat /proc/meminfo | grep anon");

    return 0;
}