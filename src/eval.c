#include "eval.h"

/*** public functions ***/

int eval(struct bekobuild_t *bekobuild) {
  int i;
  for (i = 0; i < bekobuild->build->size; ++i) {
    system(string_vector_at(bekobuild->build, i));
  }
}
