#ifndef CLI_H
#define CLI_H

#include <string.h>

#include "string_utils.h"
#include "command.h"
#include "string_vector.h"

struct cli_t {
  struct string_vector_t *args;
  const char *command;
  const char *sub_command;
  int last_index;
};

extern struct cli_t *cli_new();
extern void cli_free(struct cli_t *);
extern int cli_run(struct cli_t *);
extern int cli_parse(struct cli_t *);
extern void cli_set_arguments(struct cli_t *, int, char **);

#endif
