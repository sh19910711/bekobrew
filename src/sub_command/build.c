#include "command.h"
#include "bekobuild.h"
#include "eval.h"

int sub_command_build(struct string_vector_t *args) {
  FILE *fp = fopen("./BEKOBUILD", "r");
  struct bekobuild_t *src = bekobuild_new();
  bekobuild_open(src, fp);
  struct bekobuild_t *bekobuild = bekobuild_expand(src);
  eval(bekobuild);
  bekobuild_free(src);
  bekobuild_free(bekobuild);
  fclose(fp);
  return 0;
}
