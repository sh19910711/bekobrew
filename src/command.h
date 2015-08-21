#ifndef COMMAND_H
#define COMMAND_H

#include "common.h"

struct command {
  const char* cmd;
  int (*call)(int, const char**);
};

extern int cmd_version(int argc, const char** argv);
extern int cmd_help(int argc, const char** argv);
extern int cmd_install(int argc, const char** argv);
extern struct command* command_find(const char* cmd_name);

#endif
