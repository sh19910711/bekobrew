#include "eval.h"

#include <sys/stat.h>

static int calc_script_length(struct string_vector_t *commands);
static void append(char **, const char *);

/*** public functions ***/

int eval(struct bekobuild_t *bekobuild) {
  char command[512];
  char *script;

  mkdir(bekobuild->srcdir, 0755);
  mkdir(bekobuild->pkgdir, 0755);

  script = eval_get_script(bekobuild->build);
  printf("script:\n%s\n", script);
  system(script);
  free(script);
}

char *eval_get_script(struct string_vector_t *commands) {
  int len = calc_script_length(commands);
  char *script = (char *)malloc(sizeof(char) * len);
  char *p = script;
  int i;
  for (i = 0; i < commands->size; ++i) {
    append(&p, string_vector_at(commands, i));
  }
  *p = '\0';
  return script;
}

/*** private functions ***/

static void append(char **t, const char *s) {
  char *p = *t;
  while (*s != '\0') {
    *p = *s;
    ++p;
    ++s;
  }
  *p = '\n';
  ++p;
  *t = p;
}

static int calc_script_length(struct string_vector_t *commands) {
  int len = 1;
  int i;
  for (i = 0; i < commands->size; ++ i) {
    len += strlen(string_vector_at(commands, i)) + 1;
  }
  return len;
}
