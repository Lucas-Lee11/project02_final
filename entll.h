#ifndef ENTLL_H_
#define ENTLL_H_

#include "entity.h"
#include "stage.h"

struct entll {
    struct entity ent;
    struct entll * next;
    struct entll * prev;
};

struct entll * init_entll(const struct entity * initial_ent);
struct entll * destroy_entll(struct entll * to_free);
struct entll * destroy_entll_children(struct entll * to_free);

struct entll * push(struct entll * dest, const struct entity * ent);

#endif
