#include <stdio.h>
#include <unistd.h>


void foo(void)
{
	while (1) {
		puts("Hello, I'm a shared library");
		sleep(1);

	}
}
