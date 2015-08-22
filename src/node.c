#include "node.h"

struct node_t *node_new(const void *value) {
  struct node_t *self = (struct node_t *) malloc(sizeof(struct node_t));
  self->value = value;
  return self;
}

const char *node_to_string(struct node_t *node) {
  return (const char *)node->value;
}
