#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

struct string_map_t {
  const void *value;
  struct string_map_t **child;
};

extern struct string_map_t *string_map_new();
extern void string_map_free(struct string_map_t *);
extern struct string_map_t *string_map_set(struct string_map_t *, const char *, const void *);
extern const char *string_map_get(struct string_map_t *, const char *);

#endif
