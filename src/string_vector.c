#include "string_vector.h"

#include <stdlib.h>

static inline int get_capacity(int capacity);
static inline int is_full(struct string_vector_t *self);
static void resize(struct string_vector_t *self);

/*** public functions ***/

struct string_vector_t *string_vector_new() {
  struct string_vector_t *self = (struct string_vector_t *) malloc(sizeof(struct string_vector_t));
  self->size = 0;
  self->capacity = 1;
  self->data = (char **) malloc(get_capacity(self->capacity));
  return self;
}

void string_vector_free(struct string_vector_t *self) {
  int i;
  for (i = 0; i < self->size; ++i) {
    free(self->data[i]);
  }
  free(self->data);
  free(self);
}

void string_vector_push(struct string_vector_t *self, char *item) {
  if (is_full(self)) {
    resize(self);
  }
  self->data[self->size++] = item;
}

const char *string_vector_at(struct string_vector_t *self, int k) {
  return self->data[k];
}

/*** private functions ***/

static inline int get_capacity(int capacity) {
  return sizeof(char *) * capacity;
}

static inline int is_full(struct string_vector_t *self) {
  return self->size >= self->capacity;
}

static void resize(struct string_vector_t *self) {
  self->capacity *= 2;
  void *tmp = realloc(self->data, get_capacity(self->capacity));
  if (!tmp) {
    free(self->data);
  } else {
    self->data = (char **)tmp;
  }
}
