#ifndef COMMAND_H
#define COMMAND_H

#include "string_vector.h"

struct command {
  const char *cmd;
  int (*call)(struct string_vector_t *);
};

extern struct command *command_find(const char *cmd_name);

// The below functions are implemented in the "src/sub_command/*.c"
extern int sub_command_version(struct string_vector_t *);
extern int sub_command_help(struct string_vector_t *);
extern int sub_command_install(struct string_vector_t *);
extern int sub_command_build(struct string_vector_t *);

#endif
