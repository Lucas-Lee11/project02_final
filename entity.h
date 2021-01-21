#include <SDL2/SDL.h>

#ifndef ENTITY_H_
#define ENTITY_H_

#define PLAYER_IMG_PATH "./player.bmp"
#define PLAYER_HEIGHT 50
#define PLAYER_WIDTH 50
#define PLAYER_SPEED 3

//action states
enum {
    GROUNDED = 1,
    AIRBORN = 2
};

//

struct entity {
    //x and y positions
    double x;
    double y;
    //more values for physics
    double x_vel;
    double y_vel;
    //more than acceleration seems superfluous
    double x_acc;
    double y_acc;

    //height and width in pixels
    int height;
    int width;

    //a character such that the first 4 bits represent whether there is collision or not
    //ex: 00001111
    //    0000NSEW
    //    so there is collision enabled comming from all sides
    //
    //    00001000
    //    there collison if an entity with collision from the south collides with the top of the rectangle
    char collision;

    //gives the current "state" of the character. Are they grounded? Are they Airborn? Anything else?
    //GROUNDED = 1;
    //AIRBORN = 2
    int action_state;

    //current texture to render
    SDL_Texture * tex;
    //const char * sprite_path;
};

struct entity * init_entity(const char * sprite_path, SDL_Renderer * renderer) {
struct entity * free_entity(struct entity * ent);
//currently this just takes and entity, but it may take more in the future to consider surrounding entities
void update_world_values(struct entity * ent);
void update_position(struct entity * ent);

int render_entity(SDL_Renderer * renderer, struct entity * ent);

#endif
