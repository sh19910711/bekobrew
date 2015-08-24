#ifndef MAP_H
#define MAP_H

struct string_map_t {
  const void *value;
  struct string_map_t **child;
};

extern struct string_map_t *string_map_new();
extern void string_map_free(struct string_map_t *);
extern struct string_map_t *string_map_set(struct string_map_t *, const char *, const void *);
extern const char *string_map_get(const struct string_map_t *, const char *);
extern int string_map_get_depth(const struct string_map_t *);

#endif
