#include "eval.h"

/*** public functions ***/

int eval(struct bekobuild_t *bekobuild) {
  char command[512];
  int i;

  sprintf(command, "mkdir -p %s", bekobuild->name);
  system(command);

  for (i = 0; i < bekobuild->build->size; ++i) {
    system(string_vector_at(bekobuild->build, i));
  }
}
