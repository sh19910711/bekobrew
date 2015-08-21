#include "command.h"

struct command commands[] = {
  { "version", cmd_version },
  { "help", cmd_help },
  { "install", cmd_install },
};

struct command* command_find(const char* cmd_name) {
  int i;
  for (i = 0; i < ARRAY_SIZE(commands); i++) {
    struct command* p = commands + i;
    if (!strcmp(cmd_name, p->cmd)) {
      return p;
    }
  }
  return NULL;
}
