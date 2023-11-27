#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_SIZE 4096*1024*10

int main(int argc, char **argv)
{
  char *buffer = NULL;

  buffer = malloc(ALLOC_SIZE);
  if (NULL == buffer)
  {
    printf("alloc buffer faild\n");
    return -1;
  }

  getchar();

  free(buffer);
  buffer = NULL;

  return 0;
}
