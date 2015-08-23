#include "cli.h"

struct cli_t *cli_new() {
  struct cli_t *self = (struct cli_t *) malloc(sizeof(struct cli_t));
  self->args = vector_new();
  return self;
}

void cli_free(struct cli_t *self) {
  vector_free(self->args);
  free(self);
}

int cli_run(struct cli_t *self) {
  return 0;
}
