#include <SDL2/SDL.h>

#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

#include "entity.h"
#include "rendering.h"


/*
 * Allocates and creates entity struct. The sprite path is a bmp file. Initializes all fields to 0
 * Returns: pointer to the created struct or NULL on failier
*/
struct entity * init_entity(const int height, const int width) {
    struct entity * ent = malloc(sizeof(struct entity));

    int fd = open("/dev/urandom", O_RDONLY);
    if(fd == -1) {
        fprintf(stderr, "Error opening /dev/urandom: %s\n", strerror(errno));

        free(ent);

        return NULL;
    }

    read(fd, &(ent->id), sizeof(ent->id));

    ent->height = height;
    ent->width = width;

    ent->x = 0;
    ent->y = 0;
    ent->x_vel = 0;
    ent->y_vel = 0;
    ent->x_acc = 0;
    ent->y_acc = 0;

    ent->type = GENERIC;
    ent->rend_id = R_INVIS;

    close(fd);

    return ent;
}

/*
 * Frees an entity
 * Returns: null pointer
*/

struct entity * free_entity(struct entity * ent) {
    free(ent);

    return NULL;
}

/*
 * Updates velocity and position once
 * Returns: void
*/

void update_position(struct entity * ent) {
    ent->x_vel += ent->x_acc;
    ent->y_vel += ent->y_acc;

    ent->x += ent->x_vel;
    ent->y += ent->y_vel;
}

/*
 * copies entity from src to dest
 * Retruns: void
*/

void cp_entity(struct entity * dest, const struct entity * src) {
    dest->id = src->id;
    dest->type = src->type;
    dest->rend_id = src->rend_id;

    dest->x = src->x;
    dest->y = src->y;
    dest->x_vel = src->x_vel;
    dest->y_vel = src->y_vel;
    dest->x_acc = src->x_acc;
    dest->y_acc = src->y_acc;

    dest->height = src->height;
    dest->width = src->width;

    dest->collision = src->collision;
    dest->action_state = src->action_state;

}
