CC=gcc
USE_SDL_CONFIG=n

ifeq ($(USE_SDL_CONFIG),y) 
	SDL_LINK_FLAGS=`sdl2-config --libs`
	SDL_HEADER_FLAGS=`sdl2-config --cflags`
else 
	SDL_HEADER_FLAGS=-I/usr/local/Cellar/sdl2/2.0.14_1/include
	SDL_LINK_FLAGS=-L/usr/local/Cellar/sdl2/2.0.14_1/lib -lSDL2
endif

CMPNTS = main.o player.o

all: prgrm

prgrm: $(CMPNTS)
	$(CC) -o prgrm main.o player.o $(SDL_LINK_FLAGS) 

main.o: main.c
	$(CC) -c main.c $(SDL_HEADER_FLAGS)

player.o: player.c player.h
	$(CC) -c player.c $(SDL_HEADER_FLAGS)

.PHONY: run clean

run:
	./prgrm

clean:
	rm *.o
