#include "string_map.h"

struct string_map_t *string_map_new() {
  struct string_map_t *self = (struct string_map_t *) malloc(sizeof(struct string_map_t));
  self->value = NULL;
  self->child = (struct string_map_t **) calloc(256, sizeof(struct string_map_t *));
  return self;
}

void string_map_free(struct string_map_t *self) {
  int i;
  for (i = 0; i < 256; ++i) {
    if (self->child[i]) {
      string_map_free(self->child[i]);
    }
  }
  free(self->child);
  free(self);
}

static inline int is_null(char c) {
  return c == '\0';
}

static struct string_map_t *find(struct string_map_t **self, const char *key, int depth) {
  if (depth > 10) {
    return NULL;
  }
  if (!*self) {
    *self = string_map_new();
  }
  const char c = *key;
  if (is_null(c)) {
    return *self;
  } else {
    return find((*self)->child + c, key + 1, depth + 1);
  }
}

static const struct string_map_t *const_find(const struct string_map_t **self, const char *key, int depth) {
  if (depth > 10) {
    return NULL;
  }
  if (!*self) {
    *self = string_map_new();
  }
  const char c = *key;
  if (is_null(c)) {
    return *self;
  } else {
    return find((*self)->child + c, key + 1, depth + 1);
  }
}

struct string_map_t *string_map_set(struct string_map_t *self, const char *key, const void *value) {
  struct string_map_t *found_node = find(&self, key, 0);
  if (found_node) {
    found_node->value = value;
    return found_node;
  } else {
    return NULL;
  }
}

const char *string_map_get(const struct string_map_t *self, const char *key) {
  const struct string_map_t *found_node = const_find(&self, key, 0);
  if (found_node) {
    return found_node->value;
  } else {
    return NULL;
  }
}

static inline int max(int a, int b) {
  return a > b ? a : b;
}

extern int string_map_get_depth(const struct string_map_t *self) {
  int best = 0;
  int i;
  if (self->value) {
    best = strlen(self->value);
  }
  for (i = 0; i < 256; ++i) {
    if (self->child[i]) {
      best = max(best, string_map_get_depth(self->child[i]));
    }
  }
  return best;
}
