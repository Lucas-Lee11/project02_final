CC=gcc
USE_SDL_CONFIG=y

ifeq ($(USE_SDL_CONFIG),y)
	SDL_LINK_FLAGS=`sdl2-config --libs`
	SDL_HEADER_FLAGS=`sdl2-config --cflags`
else
	#or whatever you want these to be
	SDL_HEADER_FLAGS=-I/usr/local/Cellar/sdl2/2.0.14_1/include
	SDL_LINK_FLAGS=-L/usr/local/Cellar/sdl2/2.0.14_1/lib -lSDL2
endif

CMPNTS = main.o entity.o input.o entll.o stage.o

all: prgrm

prgrm: $(CMPNTS)
	$(CC) -o prgrm $(CMPNTS) $(SDL_LINK_FLAGS)

main.o: main.c
	$(CC) -c main.c $(SDL_HEADER_FLAGS)

entity.o: entity.c entity.h
	$(CC) -c entity.c $(SDL_HEADER_FLAGS)

stage.o: stage.c stage.h
	$(CC) -c stage.c $(SDL_HEADER_FLAGS)


#doesn't need sdl things, just sets up pipe stuff
input.o: input.c input.h
	$(CC) -c input.c

entll.o: entll.c entll.h
	$(CC) -c entll.c

.PHONY: run clean

run:
	./prgrm

clean:
	rm *.o
