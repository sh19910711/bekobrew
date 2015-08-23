#ifndef BEKOBUILD_H
#define BEKOBUILD_H

#include <yaml.h>

#include "string_vector.h"

struct bekobuild_t {
  yaml_parser_t *parser;
  char *name;
  struct string_vector_t *build;
  struct string_vector_t *package;
};

extern struct bekobuild_t *bekobuild_open(FILE *);
extern void bekobuild_close(struct bekobuild_t *);

#endif
