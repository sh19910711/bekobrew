#include "command.h"
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

/*** public functions ***/

struct command *command_find(const char *cmd_name) {
  static struct command sub_commands[] = {
    { "version", sub_command_version },
    { "help", sub_command_help },
    { "install", sub_command_install },
    { "build", sub_command_build },
  };

  int i;
  for (i = 0; i < ARRAY_SIZE(sub_commands); i++) {
    struct command *p = sub_commands + i;
    if (!strcmp(cmd_name, p->cmd)) {
      return p;
    }
  }

  return NULL;
}
