#include "context.h"

struct context_t *context_new() {
  struct context_t *self = (struct context_t *) malloc(sizeof(struct context_t));
  self->map = string_map_new();
  return self;
}

void context_free(struct context_t *self) {
  string_map_free(self->map);
  free(self);
}

void context_calc_max_length(struct context_t *self) {
  self->max_length = string_map_get_depth(self->map);
}

static inline int is_valid_char(char c) {
  return c != '\0' && (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_');
}

static char *get_key(const char **s) {
  char *key = (char *)malloc(sizeof(char) * 32);
  char *t = key;
  while (is_valid_char(**s)) {
    *t = **s;
    ++(*s);
    ++t;
  }
  *t = '\0';
  return key;
}

static void append(char **t, const char *s) {
  const char *p = s;
  while (*p != '\0') {
    *(*t) = *p;
    ++(*t);
    ++p;
  }
}

char *context_expand_string(struct context_t *context, const char *src) {
  int capacity = strlen(src) + context->max_length + 1;
  char *expanded = (char *) malloc(sizeof(char) * capacity);
  const char *s = src;
  char *t = expanded;

  while (*s != '\0') {
    if (*s == '$') {
      ++s;
      char *key = get_key(&s);
      const char *value = string_map_get(context->map, key);
      if (value) {
        append(&t, value);
      } else {
        append(&t, "$");
        append(&t, key);
      }
      free(key);
    } else {
      *t = *s;
      ++s;
      ++t;
    }
  }
  *t = '\0';

  return expanded;
}

struct string_vector_t *context_expand_string_vector(struct context_t *context, struct string_vector_t *src) {
  if (src) {
    struct string_vector_t *expanded = string_vector_new();
    int i;
    for (i = 0; i < src->size; ++i) {
      string_vector_push(expanded, context_expand_string(context, string_vector_at(src, i)));
    }
    return expanded;
  }
  return NULL;
}
