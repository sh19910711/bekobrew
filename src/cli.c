#include "cli.h"
#include "string_utils.h"
#include "command.h"

#include <stdlib.h>

static const char *get_argument(struct cli_t *self, int k);
static int is_sub_command(const char *s);
static int parse_option(struct cli_t *self, const char *s);

/*** public functions ***/

struct cli_t *cli_new() {
  struct cli_t *self = (struct cli_t *) malloc(sizeof(struct cli_t));
  self->sub_command = NULL;
  self->args = string_vector_new();
  return self;
}

void cli_free(struct cli_t *self) {
  string_vector_free(self->args);
  free(self);
}

struct string_vector_t *get_sub_command_args(struct cli_t *self) {
  struct string_vector_t *args = string_vector_new();
  int i;
  for (i = self->last_index; i < self->args->size; ++i) {
    string_vector_push(args, strdup(string_vector_at(self->args, i)));
  }
  return args;
}

void cli_set_arguments(struct cli_t *self, int argc, char **argv) {
  int i;
  for (i = 0; i < argc; ++i) {
    string_vector_push(self->args, strdup(argv[i]));
  }
}

int cli_run(struct cli_t *self) {
  cli_parse(self);

  struct string_vector_t *sub_args = get_sub_command_args(self);
  int ret;
  if (self->sub_command) {
    ret = command_find(self->sub_command)->call(sub_args);
  } else {
    ret = command_find("help")->call(sub_args);
  }
  string_vector_free(sub_args);

  return ret;
}

int cli_parse(struct cli_t *self) {
  self->command = get_argument(self, 0);

  int n = self->args->size;
  for (self->last_index = 1; self->last_index < n; ++self->last_index) {
    const char *arg = get_argument(self, self->last_index);

    if (is_sub_command(arg)) {
      self->sub_command = arg;
      return 1;
    }

    if (!parse_option(self, arg)) {
      return 0;
    }
  }

  return 1;
}

/*** private functions ***/

static const char *get_argument(struct cli_t *self, int k) {
  return string_vector_at(self->args, k);
}

static int is_sub_command(const char *s) {
  return !string_start_with(s, '-');
}

static int parse_option(struct cli_t *self, const char *s) {
  if (!strcmp("--version", s)) {
    self->sub_command = "version";
    return 1;
  }
  return 0;
}
