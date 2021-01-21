#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "entity.h"
#include "stage.h"


int main(int argc, const char **argv) {

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(-1);
    }
    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Final Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );
    if(window == NULL){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(-1);
    }

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if(renderer == NULL){
        printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(-1);
    }

    //load in player texture
    SDL_Surface * player_surf = SDL_LoadBMP(PLAYER_IMG_PATH);
    if(player_surf == NULL) {
        fprintf(stderr, "Error loading sprite file: %s\n", SDL_GetError());

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture * player_tex = SDL_CreateTextureFromSurface(renderer, player_surf);
    if(player_tex == NULL) {
        fprintf(stderr, "Error loading sprite file: %s\n", SDL_GetError());

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_FreeSurface(player_surf);
        SDL_Quit();
        return 1;
    }

    // Initial renderer color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    struct stage * stage = init_stage("./level1.dat");

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
                //printf("keycode: %s\n", key);
                //move back and forth using A and D
                if(strcmp(key, "A") == 0) stage->camera.x += -PLAYER_SPEED;
                if(strcmp(key, "D") == 0) stage->camera.x += PLAYER_SPEED;
                if(strcmp(key, "S") == 0) stage->camera.y += PLAYER_SPEED;
                if(strcmp(key, "W") == 0) stage->camera.y += -PLAYER_SPEED;
            }
        }



        render_stage(renderer, stage, player_tex);

    }

    // Release resources
    free_stage(stage);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
