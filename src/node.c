#include "node.h"

struct node_t *node_new() {
  return (struct node_t *) malloc(sizeof(struct node_t));
}

void node_set_value(struct node_t *node, const void *value) {
  node->value = value;
}

const char *node_to_string(struct node_t *node) {
  return (const char *)node->value;
}
