#include <SDL2/SDL.h>

#include "input.h"

#include <string.h>
#include <errno.h>

/*
 * convinece function for closing the file descriptor
 * Returns: void
*/

void close_fd(int * fd) {
    close(fd[0]);
    fd[0] = NULL;
    close(fd[1]);
    fd[1] = NULL;
}

/*
 * convinence function, takes the SDK_Keycode and turns it into our local input keycode
 * Returns: int representing the keycode and if there is no corrospondance -1
*/

int sdlk_to_housek(SDL_Keycode sdlk) {
    switch(sdlk) {
        case SDLK_a:
            return P_LEFT;
            break;
        case SDLK_d:
            return P_RIGHT;
            break;
        case default:
            return -1;
            break;
    }
}

int main() {
    //establish connection to processer
    int fd[2];
    if(init_processer_connection(fd, WELL_KNOWN_PIPE) != 0) {
        fprintf("Error connecing to simulator!\n");

        //should be fine just to return here
        return 1;
    }

    //initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());

        return 1;
    }

    //create the window
    SDL_Window * window = NULL;
    window = SDL_CreateWindow("this is a window", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDWO_OPENGL
            );
    if(window == NULL) {
        printf("Error creating window: %s\n", SDL_GetError());

        close_fd(fd);
        return 1;
    }

    //creates renderer form the window 
    SDL_Renderer * renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        printf("Error creating renderer: %s\n", SDL_GetError());

        close_fd(fd);
        SDL_DestroyWindow(window), window = NULL;
        return 1;
    }

    //create shared memory for entities
    int shmd = shmget(KEY, sizeof(struct entity) * MAX_ENTS, IPC_CREAT | 0640);
    if(shmd == -1) {
        fprintf(stderr, "Error creating shared memory: %s\n", strerror(errno));

        close_fd(fd);
        SDL_DestroyWindow(window), window = NULL;
        SDL_DestroyRenderer(renderer);

        return 1;
    }
    struct entity * ents = shmat(shmd, 0, 0);


    bool running = true;
    SDL_Event event;
    while(running) {
        //process events
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                //quitting the game
                case SDL_QUIT:
                    running = false;
                    break;

                //a key is pressed
                case SDL_KEYDOWN:
                    int house_key = sdlk_to_housek(event.key.keysym.sym);
                    if(house_key != -1) {
                        send_input(fd[0], house_key);
                    }
                    break;

                case default:
                    break;
            }
        }
        //50 ms delay which is needed for some reason
        SDL_Delay(50);

        //TODO render the frame from the ents list

    }

    //terminate the program
    shmdt(ents);
    shmctl(shmd, IPC_RMID, 0);

    //sdl stuff
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    //close pipes
    close_fd(fd);

    return 0;
}
