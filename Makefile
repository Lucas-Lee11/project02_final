all: main.o player.o
	gcc -o prgrm -I/usr/local/Cellar/sdl2/2.0.14_1/include  -L/usr/local/Cellar/sdl2/2.0.14_1/lib -lSDL2 main.o player.o

main.o: main.c
	gcc -c -I/usr/local/Cellar/sdl2/2.0.14_1/include  main.c

player.o: player.c player.h
	gcc -c -I/usr/local/Cellar/sdl2/2.0.14_1/include  player.c

run: prgrm
	./prgrm
