#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "player.h"


int main(int argc, const char **argv) {

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(-1);
    }
    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Final Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        620, 480,
        SDL_WINDOW_OPENGL
    );
    if(window == NULL){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(-1);
    }

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(-1);
    }

    // Initial renderer color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    struct player * player = init_player(renderer);

    bool running = true;
    SDL_Event event;
    while(running) {
        // Process events
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }

            if(event.type == SDL_KEYDOWN){
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                printf("keycode: %s\n", key);
                //move back and forth using A and D
                if(strcmp(key, "A") == 0) player->dx -= PLAYER_SPEED;
                if(strcmp(key, "D") == 0) player->dx += PLAYER_SPEED;
            }
        }

        //Wipe the previous screen
        printf("rendering...\n");
        SDL_RenderClear(renderer);

        render_player(renderer, player);


        //Present updated render
        SDL_RenderPresent(renderer);

        //add a slight delay between frames
        SDL_Delay(50);
    }

    // Release resources
    free_player(player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
