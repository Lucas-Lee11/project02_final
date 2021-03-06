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

#what does each of the things need to compile

TEST_CMPNTS = stage.o main.o entity.o entll.o simulator.o

INPUT_READER_RENDERER_CMPNTS = entity.o input.o entll.o simulator.o input_reader_and_renderer.o rendering.o

SIMULATION_CMPNTS = entity.o input.o entll.o simulator.o  simulation.o rendering.o

MAIN_CMPNT = input_reader_renderer simulation main.o $(INPUT_READER_RENDERER_CMPNTS) $(SIMULATION_CMPNTS)

#here is everything to compile
all: input_reader_renderer simulation main

#all the different copiled processes
main: $(MAIN_CMPNT)
	$(CC) -o main main.o

input_reader_renderer: $(INPUT_READER_RENDERER_CMPNTS)
	$(CC) -o input_reader_renderer $(INPUT_READER_RENDERER_CMPNTS) $(SDL_LINK_FLAGS)

simulation: $(SIMULATION_CMPNTS)
	$(CC) -o simulation $(SIMULATION_CMPNTS) $(SDL_LINK_FLAGS)

test: $(TEST_CMPNTS)
	$(CC) -o test $(TEST_CMPNTS) $(SDL_LINK_FLAGS)

#making all those .o files
entity.o: entity.c entity.h
	$(CC) -c entity.c $(SDL_HEADER_FLAGS)

stage.o: stage.c stage.h 
	$(CC) -c stage.c $(SDL_HEADER_FLAGS)

input_reader_and_renderer.o: input_reader_and_renderer.c input.h rendering.h
	$(CC) -c input_reader_and_renderer.c $(SDL_HEADER_FLAGS)

rendering.o: rendering.c rendering.h entity.h
	$(CC) -c rendering.c $(SDL_HEADER_FLAGS)

#doesn't need sdl things
input.o: input.c input.h
	$(CC) -c input.c

entll.o: entll.c entll.h
	$(CC) -c entll.c

simlation.o: simulation.c simulator.h input.h stage.h
	$(CC) -c simlation.c

simlator.o: simulator.c simulator.h input.h rendering.h
	$(CC) -c simlator.c

main.o: 
	$(CC) -c main.c

.PHONY: run clean

run:
	./main

clean:
	rm *.o
