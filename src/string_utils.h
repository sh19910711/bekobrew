#ifndef STRING_UTILS_H
#define STRING_UTILS_H

static inline int string_start_with(const char *s, const char c) {
  return s[0] == c;
}

static inline int string_skip_prefix(const char *s, const char *prefix,
                                     const char **out) {
  do {
    if(!*prefix) {
      *out = s;
      return 1;
    }
  } while(*s++ == *prefix++);

  return 0;
}

#endif
