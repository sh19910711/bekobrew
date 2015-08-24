#include "expand.h"

char *expand_string(struct string_map_t *context, const char *src) {
  int capacity = strlen(src) + 1;
  char *expanded = (char *)malloc(sizeof(char) * capacity);
  const char *s = src;
  char *t = expanded;
  while (*s != '\0') {
    *t = *s;
    ++s;
    ++t;
  }
  *t = '\0';
  return expanded;
}

struct string_vector_t *expand_string_vector(struct string_map_t *context, struct string_vector_t *src) {
  if (src) {
    struct string_vector_t *expanded = string_vector_new();
    int i;
    for (i = 0; i < src->size; ++i) {
      string_vector_push(expanded, expand_string(context, string_vector_at(src, i)));
    }
    return expanded;
  }
  return NULL;
}
