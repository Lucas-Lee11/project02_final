#include "entll.h"
#include "entity.h"

/*
 * Makes a linked list node
 * Returns: a pointer to said linked list node
*/

struct entll * init_entll(const struct entity * initial_ent) {
    struct entll * out;
    out = malloc(sizeof(struct entll));

    out->next = NULL;
    out->prev = NULL;

    cp_entity(&(out->ent),initial_ent);

    return out;
}

/*
 * Destroys a singal entll node
 * Returns: NULL
*/

struct entll * destroy_entll(struct entll * to_free) {
    free(to_free);

    return NULL;
}

/*
 * Destroys the entll and its children
 * Returns: NULL
*/

struct entll * destroy_entll_children(struct entll * to_free) {
    while(to_free) {
        if(to_free->next == NULL) {
            free(to_free);
            return NULL;
        }

        to_free = to_free->next;
        destroy_entll(to_free->prev);
    }
    return NULL;
}

/*
 * pushes an entity node to the front of the linked list NOTE THE ENT IS COPIED, NOTE ACTUALLY USED
 * Returns: a pointer to the front of the linked list
 */

struct entll * push(struct entll * dest, const struct entity * ent) {
    struct entll * nhead = init_entll(ent);

    dest->prev = nhead;
    nhead->next = dest;

    return nhead;
}

