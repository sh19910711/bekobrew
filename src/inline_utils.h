#ifndef INLINE_UTILS_H
#define INLINE_UTILS_H

static inline int start_with_hyphen(const char* s) {
  return s[0] == '-';
}

static inline int skip_prefix(const char* s, const char* prefix,
                              const char** out) {
  do {
    if(!*prefix) {
      *out = s;
      return 1;
    }
  } while(*s++ == *prefix++);

  return 0;
}

#endif
