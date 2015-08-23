#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

struct map_t {
  const void *value;
  struct map_t **child;
};

extern struct map_t *map_new();
extern void map_free(struct map_t *);
extern struct map_t *map_set(struct map_t *, const char *, const void *);
extern const void *map_get(struct map_t *, const char *);
extern const char *map_get_as_string(struct map_t *, const char *);

#endif
