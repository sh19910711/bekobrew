#include "vector.h"

static inline int get_capacity(int capacity) {
  return sizeof(struct node_t *) * capacity;
}

static inline int is_full(struct vector_t *self) {
  return self->size >= self->capacity;
}

static void resize(struct vector_t *self) {
  self->capacity *= 2;
  self->data = (struct node_t **) realloc(self->data,
                                          get_capacity(self->capacity));
}

struct vector_t *vector_new() {
  struct vector_t *self = (struct vector_t *) malloc(sizeof(struct vector_t));
  self->size = 0;
  self->capacity = 1;
  self->data = (struct node_t **) malloc(get_capacity(self->capacity));
  return self;
}

void vector_free(struct vector_t *self) {
  int i;
  for (i = 0; i < self->size; ++i) {
    node_free(self->data[i]);
  }
  free(self->data);
  free(self);
}

void vector_push(struct vector_t *self, struct node_t *node) {
  if (is_full(self)) {
    resize(self);
  }
  self->data[self->size++] = node;
}

struct node_t *vector_at(struct vector_t *self, int k) {
  return self->data[k];
}
