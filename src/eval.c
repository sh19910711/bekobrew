#include "eval.h"
#include "request.h"

#include <url.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

static int calc_script_length(struct string_vector_t *commands);
static void append(char **, const char *);
static void get_sources(const char *, struct string_vector_t *, struct string_vector_t *);
static int mkdir_p(const char *path, const mode_t mode);

/*** public functions ***/

static void eval_script(const struct string_vector_t *commands) {
  if (!commands) {
    return;
  }
  char *script = eval_get_script(commands);
  system(script);
  free(script);
}

int eval(const struct bekobuild_t *bekobuild) {
  char command[512];
  char *script;

  mkdir_p(bekobuild->srcdir, 0755);
  mkdir_p(bekobuild->pkgdir, 0755);

  get_sources(bekobuild->srcdir, bekobuild->sources, bekobuild->sums);

  eval_script(bekobuild->build);
  eval_script(bekobuild->package);
}

char *eval_get_script(const struct string_vector_t *commands) {
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

static void write_file(const char *srcdir, const char *name, const char *body) {
  if (strchr(name, '/')) {
    fputs("ERROR: the file name doesn't contain slash.", stderr);
    return;
  }

  char path[256];
  sprintf(path, "%s/%s", srcdir, name);

  FILE *fp = fopen(path, "w");
  fwrite(body, sizeof(char), strlen(body), fp);
  fclose(fp);
}

static char *parent_dir(const char *path) {
  const char *slash = strrchr(path, '/');
  return strndup(path, slash - path);
}

static void decompress(const char *path) {
  char command[256];
  char *parent = parent_dir(path);
  sprintf(command, "tar -C %s -zxf %s", parent, path);
  system(command);
  free(parent);
}

static void get_sources(const char *srcdir, struct string_vector_t *sources,
                        struct string_vector_t *sums) {
  if (!sources) {
    return;
  }

  int i;
  for (i = 0; i < sources->size; ++i) {
    const char *url_str = string_vector_at(sources, i);
    struct url_t *url = url_parse(url_str);
    char path[256];
    sprintf(path, "%s/%s", srcdir, url_get_filename(url));
    request_download(path, url_str);
    decompress(path);
    url_free(url);
  }
}

static int is_directory(const char *path) {
  struct stat st;
  return !stat(path, &st) && S_ISDIR(st.st_mode);
}

static int mkdir_p(const char *path, const mode_t mode) {
  if (is_directory(path)) {
    return 0;
  }

  char *s = strdup(path);
  char *p = s;
  char *q;

  while (q = strchr(p, '/')) {
    *q = '\0';
    if (*s != '\0') {
      mkdir(s, mode);
    }
    *q = '/';
    p = q + 1;
  }
  mkdir(s, mode);

  free(s);
}
