#ifndef CLI_H
#define CLI_H

#include <string.h>

#include "string_utils.h"
#include "command.h"
#include "vector.h"

struct cli_t {
  struct vector_t *args;
};

extern struct cli_t *cli_new();
extern void cli_free(struct cli_t *);
extern int cli_run(struct cli_t *);

#endif
