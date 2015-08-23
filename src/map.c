#include "map.h"

struct map_t *map_new() {
  struct map_t *self = (struct map_t *) malloc(sizeof(struct map_t));
  self->value = NULL;
  self->child = (struct map_t **) calloc(256, sizeof(struct map_t *));
  return self;
}

void map_free(struct map_t *self) {
  int i;
  for (i = 0; i < 256; ++i) {
    if (self->child[i]) {
      map_free(self->child[i]);
    }
  }
  free(self->child);
  free(self);
}

static inline int is_null(char c) {
  return c == '\0';
}

static struct map_t *find(struct map_t **self, const char *key, int depth) {
  if (depth > 10) {
    return NULL;
  }
  if (!*self) {
    *self = map_new();
  }
  const char c = *key;
  if (is_null(c)) {
    return *self;
  } else {
    return find((*self)->child + c, key + 1, depth + 1);
  }
}

struct map_t *map_set(struct map_t *self, const char *key, const void *value) {
  struct map_t *found_node = find(&self, key, 0);
  if (found_node) {
    found_node->value = value;
    return found_node;
  } else {
    return NULL;
  }
}

const void *map_get(struct map_t *self, const char *key) {
  struct map_t *found_node = find(&self, key, 0);
  if (found_node) {
    return found_node->value;
  } else {
    return NULL;
  }
}

const char *map_get_as_string(struct map_t *self, const char *key) {
  return (const char *) map_get(self, key);
}
