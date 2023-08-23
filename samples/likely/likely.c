#include <stdio.h>
#include <stdlib.h>

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)

int main(int argc, char ** argv)
{
	int a = atoi(argv[1]);

	if (likely(a > 0)){
		a = 0x5a;
	}else {
		a = 0xa5;
	}
	
	printf("a = 0x%x\n", a);

	return 0;
}
