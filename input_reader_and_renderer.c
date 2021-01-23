#include <SDL2/SDL.h>

#include "input.h"
#include "simulator.h"

#include <sys/ipc.h>
#include <sys/shm.h>

#include <unistd.h>

#include <string.h>
#include <errno.h>

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
        default:
            return -1;
            break;
    }
}

int main() {

    //create shared memory for entities
    int shmd = shmget(KEY, sizeof(struct entity) * MAX_ENTS, IPC_CREAT | 0640);

    printf("shmd: %d\n", shmd);

    if(shmd == -1) {
        fprintf(stderr, "Error creating shared memory: %s\n", strerror(errno));

        return 1;
    }
    const struct entity * ents = shmat(shmd, 0, 0);


    //establish connection to processer
    int fd[2];
    if(init_processer_connection(fd, WELL_KNOWN_PIPE) != 0) {
        fprintf(stderr, "Error connecing to simulator!\n");

        shmdt(ents);
        shmctl(shmd, IPC_RMID, 0);
        //should be fine just to return here
        return 1;
    }

    //initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());

        shmdt(ents);
        shmctl(shmd, IPC_RMID, 0);

        close(fd[0]), close(fd[1]);
        return 1;
    }

    //create the window
    SDL_Window * window = NULL;
    window = SDL_CreateWindow("this is a window", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_OPENGL
            );
    if(window == NULL) {
        printf("Error creating window: %s\n", SDL_GetError());

        shmdt(ents);
        shmctl(shmd, IPC_RMID, 0);

        close(fd[0]), close(fd[1]);
        return 1;
    }

    //creates renderer form the window 
    SDL_Renderer * renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        printf("Error creating renderer: %s\n", SDL_GetError());

        SDL_DestroyWindow(window), window = NULL;

        shmdt(ents);
        shmctl(shmd, IPC_RMID, 0);

        close(fd[0]), close(fd[1]);

        return 1;
    }

    

    char running = 1;
    SDL_Event event;
    while(running) {
        //process events
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                //quitting the game
                case SDL_QUIT:
                    running = 0;
                    const int term = TERMINATE;
                    send_input(fd[0], &term);
                    break;

                //a key is pressed
                case SDL_KEYDOWN:
                    ;
                    const int house_key = sdlk_to_housek(event.key.keysym.sym);
                    if(house_key != -1) {
                        send_input(fd[0], &house_key);
                    }
                    break;

                default:
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
    close(fd[0]), close(fd[1]);

    return 0;
}
