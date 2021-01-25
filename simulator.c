//goal is to no use any sdl stuff here
#include "input.h"
#include "entll.h"
#include "entity.h"
#include "rendering.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#define SIGN(x) ((x) < 0 ? -1 : 1)
#define MAX(x,y) ((x) < (y) (y) : (x))
#define MOVEMENT_EPSILON 0.2
#define COLLISION_EPSILON 0.1


/*
 * rounds small numbers to 0
 * Returns: void
*/

void round_ep(double * n) {
    *n = fabs(*n) < MOVEMENT_EPSILON ? 0 : *n;
}

/*
 * detects collision between entities
 * Returns: 1 on collison 0 on not
*/
int will_collide_x(struct entity * this, struct entity * that){

    if(this == that) return 0;

    double x1_left = this->x + this->x_vel;
    double x1_right = x1_left + this->width;

    double x1_top = this->y;
    double x1_bottom = x1_top+ this->height;

    double x2_left = that->x;
    double x2_right = that->x + that->width;
    double x2_top = that->y;
    double x2_bottom = that->y + that->height;


    if(x1_right > x2_left && x1_left < x2_right && x1_bottom > x2_top && x1_top < x2_bottom){
        return 1;
    }
    return 0;
}

int will_collide_y(struct entity * this, struct entity * that){

    if(this == that) return 0;

    double x1_left = this->x;
    double x1_right = x1_left + this->width;

    double x1_top = this->y + this->y_vel;
    double x1_bottom = x1_top+ this->height;

    double x2_left = that->x;
    double x2_right = that->x + that->width;
    double x2_top = that->y;
    double x2_bottom = that->y + that->height;


    if(x1_right > x2_left && x1_left < x2_right && x1_bottom > x2_top && x1_top < x2_bottom){
        return 1;
    }
    return 0;
}

void handle_collision(struct entity * ent, struct entll * check){
    struct entll * cur_ent = check;

    while(cur_ent) {
        struct entity * other = &(cur_ent->ent);

        int x_colled = will_collide_x(ent, other), y_colled = will_collide_y(ent, other);
        double special_y_v, special_x_v;

        if(x_colled) {
            special_x_v = -(ent->x_vel * COLLISION_EPSILON);
            ent->x_vel *= COLLISION_EPSILON;
        }
        if(y_colled) {
            special_y_v = -(ent->y_vel * COLLISION_EPSILON);
            ent->y_vel *= COLLISION_EPSILON;
        }

        x_colled = will_collide_x(ent, other), y_colled = will_collide_y(ent, other);

        while(will_collide_y(ent, other) || will_collide_x(ent,other)) {
            if(will_collide_x(ent,other)) {
                ent->x += special_x_v;
            }
            if(will_collide_y(ent, other)) {
                ent->y += special_y_v;
            }
        }

        if(x_colled) {
            ent->x_vel = 0;
            ent->x_acc = 0;
        }
        if(y_colled) {
            ent->y_vel = 0;
            ent->y_acc = 0;
        }

        cur_ent = cur_ent->next;
    }

}


/*
 * updates position and surroundings of a player
 * Returns: void
*/

void update_player(struct entity * ent,
        struct entll * loaded, struct entll * unloaded,
        int * gamestate, int input_key) {

    const double dacc = 0.3;
    const double ddacc = 0.1;
    //change  acceleration
    switch(input_key) {
        case P_UP:
            ent->y_acc -= dacc;
            break;
        case P_DOWN:
            ent->y_acc += dacc;
            break;
        case P_RIGHT:
            ent->x_acc += dacc;
            break;
        case P_LEFT:
            ent->x_acc -= dacc;
            break;
        default:
            break;
    }

    handle_collision(ent, loaded);

    ent->x_vel += ent->x_acc;
    ent->x += ent->x_vel;
    ent->y_vel += ent->y_acc;
    ent->y += ent->y_vel;


    ent->x_acc -= ent->x_acc * ddacc;
    ent->x_vel -= ent->x_vel * ddacc;
    ent->y_acc -= ent->y_acc * ddacc;
    ent->y_vel -= ent->y_vel * ddacc;



    //making getting to 0 if you are less than some epsilon
    round_ep(&(ent->x_acc));
    round_ep(&(ent->y_acc));
    round_ep(&(ent->x_vel));
    round_ep(&(ent->y_vel));


}

/*
 * updates both the given entitiy and other entities as needed with one tick of the game
 * this function is badically just to choose the right actual updater function based on type
 * Returns: void
*/

void update_ent(struct entll * ent,
        struct entll * loaded, struct entll * unloaded,
        int * gamestate, int input_key) {

    switch(ent->ent.type) {
        case PLAYER:
            update_player(&(ent->ent), loaded, unloaded, gamestate, input_key);
            break;
        default:
            break;
    }

    return;
}

/*
 * loads tiles onto the front of the given entll
 * Returns: pointer to dest
*/

struct entll * load_tiles(struct entll * dest, const int height, const int width, const int tile_size, const char * level_path) {
    FILE * fp = fopen(level_path, "r");

    if(fp == NULL) {
        fprintf(stderr, "Error loading level_path: %s\n", strerror(errno));

        return dest;
    }

    int tile_code;
    char dump;

    int x, y;
    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            fscanf(fp, "%d", &tile_code);
            if(tile_code == 0) continue;

            struct entity * tmp = init_entity(tile_size, tile_size);
            tmp->type = TILE;
            tmp->x = x * tile_size;
            tmp->y = y * tile_size;
            tmp->rend_id = R_TILE;

            dest = push(dest, tmp);

            free_entity(tmp);
        }

        fscanf(fp, "%c", &dump);
    }

    fclose(fp);

    return dest;
}
