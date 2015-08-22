#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#include "node.h"

struct vector_t {
  int size;
  int capacity;
  struct node_t **data;
};

extern struct vector_t *vector_new();
extern void vector_free(struct vector_t *);
extern void vector_push(struct vector_t *, struct node_t *);
extern struct node_t *vector_at(struct vector_t *, int);

#endif
