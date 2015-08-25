#include "eval.h"

#include <sys/stat.h>

static int calc_script_length(struct string_vector_t *commands);

/*** public functions ***/

int eval(struct bekobuild_t *bekobuild) {
  char command[512];
  int i;

  mkdir(bekobuild->srcdir, 0755);
  mkdir(bekobuild->pkgdir, 0755);

  for (i = 0; i < bekobuild->build->size; ++i) {
    system(string_vector_at(bekobuild->build, i));
  }
}

static void append(char **t, const char *s) {
  while (*s != '\0') {
    **t = *s;
    ++(*t);
    ++s;
  }
  **t = '\n';
  ++(*t);
}

char *eval_get_script(struct string_vector_t *commands) {
  int len = calc_script_length(commands);
  char *script = (char *)malloc(sizeof(char) * len);
  char *p = script;
  int i;
  for (i = 0; i < commands->size; ++i) {
    printf("%d: %s\n", i, string_vector_at(commands, i));
    append(&p, string_vector_at(commands, i));
  }
  *p = '\0';
  printf("script: %s\n", script);
  return script;
}

/*** private functions ***/

static int calc_script_length(struct string_vector_t *commands) {
  int len = 1;
  int i;
  for (i = 0; i < commands->size; ++ i) {
    len += strlen(string_vector_at(commands, i)) + 1;
  }
  return len;
}
