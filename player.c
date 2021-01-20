#include <SDL2/SDL.h>

#include "player.h"

/*
Allocates and creates player struct
Returns pointer to struct
*/
struct player * init_player(SDL_Renderer * renderer){
    struct player * player = malloc(sizeof(struct player));

    player->height = PLAYER_HEIGHT;
    player->width = PLAYER_WIDTH;

    player->x = 50;
    player->y = 25;
    player->dx = 0;
    player->dy = 0;

    return player;
}

/*
Frees player struct
Returns null pointer
*/
struct player * free_player(struct player * player){
    free(player);

    return NULL;
}

/*
Renders player struct
Returns 0 on success, -1 on failure
*/

int render_player(SDL_Renderer * renderer, struct player * player){
    //Update player location
    player->x += player->dx;
    player->y += player->dy;

    player->dx = 0;
    player->dy = 0;

    SDL_Surface * image = SDL_LoadBMP(PLAYER_IMG_PATH);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, image);


    SDL_FreeSurface(image);

    //creates a rectangle to render based on player location and size
    SDL_Rect dstrect = {player->x, player->y, player->height, player->width};


    int out = SDL_RenderCopy(renderer, tex, NULL, &dstrect);
    SDL_DestroyTexture(tex);

    return  out;


}
