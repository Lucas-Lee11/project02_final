#include <SDL2/SDL.h>

#ifndef ENTITY_H_
#define ENTITY_H_

//action states
#define GROUNDED 1
#define AIRBORN 2

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
    char action_state;

    //Texture For Rendering
    SDL_Texture * texture;

};

struct entity * init_entity(SDL_Renderer * renderer, const char * sprite_path);
struct entity * free_entity(struct entity * ent);
//currently this just takes and entity, but it may take more in the future to consider surrounding entities
void update_world_values(struct entity * ent);

int render_entity(SDL_Renderer * renderer, const struct entity * ent);

#endif
