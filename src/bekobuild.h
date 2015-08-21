#ifndef BEKOBUILD_H
#define BEKOBUILD_H

#include <yaml.h>

struct list_t {
  const char *value;
  struct list_t *next;
};

struct bekobuild_t {
  yaml_parser_t *parser;
  const char *name;
  struct list_t *build;
};

extern struct bekobuild_t *open_bekobuild(FILE*);
extern void close_bekobuild(struct bekobuild_t*);

#endif
