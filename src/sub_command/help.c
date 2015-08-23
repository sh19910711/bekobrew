#include "command.h"

const char usage_text[] = "bekobrew [--version] [--help]\n";

int sub_command_help(struct vector_t *args) {
  printf(usage_text);
}
