#ifndef BEKOBREW_H
#define BEKOBREW_H

#include "common.h"
#include "command.h"

struct command {
  const char* cmd;
  int (*call)(int, const char**);
};

static int start_with_hyphen(const char*);
static int parse_cli_options(int* argc, const char*** argv);

#endif
