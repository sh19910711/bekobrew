#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

struct node_t {
  void *value;
};

extern struct node_t *node_new(void *);
extern void node_free(struct node_t *);
extern const char *node_to_string(struct node_t *);

#endif
