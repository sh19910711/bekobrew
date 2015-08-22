#ifndef BEKOBUILD_H
#define BEKOBUILD_H

#include <yaml.h>

struct list_t {
  const char *value;
  struct list_t *next;
};

struct seq_t {
  int n;
  const char **data;
};

struct bekobuild_t {
  yaml_parser_t *parser;
  const char *name;
  int build_num;
  struct seq_t *build;
  int package_num;
  struct seq_t *package;
};

extern struct bekobuild_t *bekobuild_open(FILE *);
extern void bekobuild_close(struct bekobuild_t *);

#endif
