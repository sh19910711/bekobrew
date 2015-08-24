#include "command.h"

#include <stdio.h>

const char usage_text[] = "bekobrew [--version] [--help]\n";

int sub_command_help(struct string_vector_t *args) {
  printf(usage_text);
  return 0;
}
