#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <string.h>

#include "vector.h"
#include "version.h"

struct command {
  const char *cmd;
  int (*call)(struct vector_t *);
};

extern int sub_command_version(struct vector_t *);
extern int sub_command_help(struct vector_t *);
extern int sub_command_install(struct vector_t *);

extern struct command *command_find(const char *cmd_name);

#endif
