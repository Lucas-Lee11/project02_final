#include <SDL2/SDL.h>

#include "input.h"
#include "simulator.h"
#include "rendering.h"

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
        case SDLK_s:
            return P_DOWN;
        case SDLK_w:
            return P_UP;
        default:
            return -1;
            break;
    }
}

int main() {
    //create shared memory for entities
    int shmd = shmget(KEY, sizeof(struct entity) * MAX_ENTS, IPC_CREAT | 0640);

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
            WINDOW_WIDTH, WINDOW_HEIGHT,
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

    //This is getting a bit cluttered but here is loading all textures as well

    SDL_Texture * texs[NUM_TEXTS];
    //nulls
    texs[R_INVIS] = NULL;
    texs[R_TILE] = NULL;

    //player texture
    SDL_Surface * p_surf = SDL_LoadBMP(PLAYER_IMG_PATH);
    if(p_surf == NULL) {
        fprintf(stderr, "Error loading sprite file: %s\n", SDL_GetError());

        SDL_DestroyWindow(window), window = NULL;

        shmdt(ents);
        shmctl(shmd, IPC_RMID, 0);

        close(fd[0]), close(fd[1]);

        return 1;
    }
    SDL_Texture * p_tex = SDL_CreateTextureFromSurface(renderer, p_surf);
    if(p_tex == NULL) {
        fprintf(stderr, "Error loading sprite file: %s\n", SDL_GetError());

        SDL_DestroyWindow(window), window = NULL;
        SDL_FreeSurface(p_surf);

        shmdt(ents);
        shmctl(shmd, IPC_RMID, 0);

        close(fd[0]), close(fd[1]);

        return 1;
    }
    SDL_FreeSurface(p_surf);

    texs[R_PLAYER] = p_tex;

    //actually run the game
    char running = 1;
    //used to pass frames even if there was no input
    char had_event = 0;

    int pressed_buttons[NUM_INPUTS];
    int but;
    for(but = 0; but < NUM_INPUTS; but++) {
        pressed_buttons[but] = PASS;
    }
    pressed_buttons[NONE] = NONE;

    SDL_Event event;
    while(running) {
        had_event = 0;
        //process events
        while(SDL_PollEvent(&event)) {
            had_event = 1;

            int house_key;
            switch(event.type) {
                //quitting the game
                case SDL_QUIT:
                    running = 0;
                    const int term = TERMINATE;
                    send_input(fd[0], &term);
                    break;

                //a key is pressed
                case SDL_KEYDOWN:
                    house_key = sdlk_to_housek(event.key.keysym.sym);
                    if(house_key != -1) {
                        pressed_buttons[house_key] = house_key;
                    }
                    break;
                case SDL_KEYUP:
                    house_key = sdlk_to_housek(event.key.keysym.sym);
                    if(house_key != -1) {
                        pressed_buttons[house_key] = PASS;
                    }
                    break;
                default:
                    break;
            }
        }
        send_inputs(fd[0], pressed_buttons, NUM_INPUTS);

        //pass frame even if there was no input
        if(!had_event) {
            const int pass = PASS;
            send_input(fd[0], &pass);
        }

        //50 ms delay which is needed for some reason
        SDL_Delay(50);

        //TODO render the frame from the ents list
        //clear last screen

        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);

        const struct entity * cam = ents;
        const struct entity * cur_ent = ents;

        while(cur_ent->type != NULL_ENT) {
            if(render_ent(renderer, texs, cur_ent, cam->x, cam->y, WINDOW_WIDTH, WINDOW_HEIGHT, STAGE_WIDTH, STAGE_HEIGHT, TILE_SIZE) == -1) {
                printf("there has been an error\n");
            }

            cur_ent++;
        }
        SDL_RenderPresent(renderer);

    }

    //terminate the program
    shmdt(ents);
    shmctl(shmd, IPC_RMID, 0);

    //sdl stuff
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    int i;
    for(i = 0; i < NUM_TEXTS; i++) {
        if(texs[i]) {
            SDL_DestroyTexture(texs[i]);
            texs[i] = NULL;
        }
    }

    //close pipes
    close(fd[0]), close(fd[1]);

    return 0;
}
