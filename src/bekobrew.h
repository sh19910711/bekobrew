#ifndef BEKOBREW_H
#define BEKOBREW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version.h"
#include "command.h"
#include "inline_utils.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

struct command {
  const char* cmd;
  int (*call)(int, const char**);
};

static int start_with_hyphen(const char*);
static int parse_cli_options(int* argc, const char*** argv);

#endif
