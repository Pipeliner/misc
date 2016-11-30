all:
	gcc -g -c -Wall -Werror -fpic foo.c
	gcc -g -shared -o libfoo.so foo.o
	gcc -g -L. -Wall -o test main.c -lfoo
	cp test test2
	#gcc -L. -Wall -o test2 main2.c -lfoo
