#include "entll.h"
#include "entity.h"

/*
 * Makes a linked list node
 * Returns: a pointer to said linked list node
*/

struct entll * init_entll() {
    struct entll * out;
    out = malloc(sizeof(struct entll));

    out->next = NULL;
    out->prev = NULL;

    return out;
}

/*
 * Destroys a linked list node
 * Returns: NULL
*/

struct entll * destroy_entll(struct entll * to_free) {
    free_entity(&(to_free->ent));
    free(to_free);

    return NULL;
}
