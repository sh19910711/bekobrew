#ifndef BEKOBUILD_H
#define BEKOBUILD_H

#include <yaml.h>

#include "string_vector.h"

struct bekobuild_t {
  // System Attributes
  yaml_parser_t *parser;
  char *srcdir;
  char *pkgdir;

  // User Attributes
  char *name;
  char *version;
  struct string_vector_t *sources;
  struct string_vector_t *sums;
  struct string_vector_t *build;
  struct string_vector_t *package;
};

extern struct bekobuild_t *bekobuild_new();
extern void bekobuild_free(struct bekobuild_t *);
extern int bekobuild_open(struct bekobuild_t *, FILE *);
extern struct bekobuild_t *bekobuild_expand(struct bekobuild_t *);

#endif
