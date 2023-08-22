#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define barrier() __asm__ __volatile__("":::"memory")

static int x = 0;
static int y = 0;

static int a = 0;
static int b = 0;

static unsigned int count = 0;

static void *thread1(void *arg)
{
	x = 1;
//	barrier();
	a = y;
}

static void *thread2(void *arg)
{
	y = 1;
//	barrier();
	b = x;
}

void judge_function(void)
{
	count++;
	printf("count = %d a = %d b = %d\n", count, a, b);

	if (0 == a && 0 == b)
	{
		printf("count = %d a = %d, b = %d, issue coming\n", count, a, b);
		return;
	}
}

void init(void)
{
	x = 0;
	y = 0;
	a = 0;
	b = 0;
}
int main(int argc, char **argv)
{
	int retv = 0;
	pthread_t t1, t2;
	cpu_set_t cpuset;

	retv = pthread_create(&t1, NULL, thread1, NULL);
	if (retv < 0)
	{
		printf("create thread 1 fail\n");
		return -1;
	}

	retv = pthread_create(&t2, NULL, thread2, NULL);
	if (retv < 0)
	{
		printf("create thread 2 fail\n");
		return -1;
	}

	CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    retv = pthread_setaffinity_np(t1, sizeof(cpuset), &cpuset);
    if (retv < 0){
        printf("pthread_setaffinity_np thread 1 bind cpu 0 fail\n");
        return -1;
    }

	CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    retv = pthread_setaffinity_np(t2, sizeof(cpuset), &cpuset);
    if (retv < 0){
        printf("pthread_setaffinity_np thread 2 bind cpu 0 fail\n");
        return -1;
    }

	while(1)
	{
		//init();
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	//	usleep(100000);
		judge_function();
	}

	return 0;
}
