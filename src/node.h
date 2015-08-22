#ifndef NODE_H
#define NODE_H

struct node_t {
  const void *value;
};

extern struct node_t *node_new();
extern void node_set_value(struct node_t *, const void *);
extern const char *node_to_string(struct node_t *);

#endif
