#ifndef BEKOBUILD_H
#define BEKOBUILD_H

#include <yaml.h>

#include "vector.h"

struct bekobuild_t {
  yaml_parser_t *parser;
  const char *name;
  struct vector_t *build;
  struct vector_t *package;
};

extern struct bekobuild_t *bekobuild_open(FILE *);
extern void bekobuild_close(struct bekobuild_t *);

#endif
