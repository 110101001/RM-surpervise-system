display:main.o display.a
	gcc main.o display.a -o display
main.o:main.c
	gcc -c main.c -o main.o	-std=c99
