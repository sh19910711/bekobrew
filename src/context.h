#ifndef CONTEXT_H
#define CONTEXT_H

#include "string_map.h"
#include "string_vector.h"

struct context_t {
  struct string_map_t *map;
  int max_length;
};

extern struct context_t *context_new();
extern void context_free(struct context_t *);
extern void context_calc_max_length(struct context_t *self);
extern char *context_expand_string(struct context_t *, const char *);
extern struct string_vector_t *context_expand_string_vector(struct context_t *, struct string_vector_t *);

#endif
