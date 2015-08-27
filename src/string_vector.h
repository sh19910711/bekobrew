#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H

struct string_vector_t {
  int size;
  int capacity;
  char **data;
};

extern struct string_vector_t *string_vector_new();
extern void string_vector_free(struct string_vector_t *);
extern void string_vector_push(struct string_vector_t *, char *);
extern const char *string_vector_at(const struct string_vector_t *, int);

#endif
