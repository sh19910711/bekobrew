#include "node.h"

struct node_t *node_new(void *value) {
  struct node_t *self = (struct node_t *) malloc(sizeof(struct node_t));
  self->value = value;
  return self;
}

void node_free(struct node_t *self) {
  free(self->value);
  free(self);
}

const char *node_to_string(struct node_t *node) {
  return (const char *)node->value;
}
