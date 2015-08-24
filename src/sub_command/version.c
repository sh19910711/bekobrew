#include "command.h"
#include "version.h"

#include <stdio.h>

int sub_command_version(struct string_vector_t *args) {
  printf("bekobrew version %s\n", BEKOBREW_VERSION);
  return 0;
}
