#include "command.h"

int sub_command_version(struct vector_t *args) {
  printf("bekobrew version %s\n", BEKOBREW_VERSION);
  return 0;
}
