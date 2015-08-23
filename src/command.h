#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <string.h>

#include "string_vector.h"
#include "version.h"

struct command {
  const char *cmd;
  int (*call)(struct string_vector_t *);
};

extern int sub_command_version(struct string_vector_t *);
extern int sub_command_help(struct string_vector_t *);
extern int sub_command_install(struct string_vector_t *);

extern struct command *command_find(const char *cmd_name);

#endif
