display:main.o display.c
	gcc main.o display.c -o display -std=c99
main.o:main.c
	gcc -c main.c -o main.o	-std=c99
