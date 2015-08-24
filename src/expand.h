#ifndef EXPAND_H
#define EXPAND_H

#include <string.h>
#include <stdlib.h>

#include "string_map.h"
#include "string_vector.h"

extern char *expand_string(struct string_map_t *, const char *);
extern struct string_vector_t *expand_string_vector(struct string_map_t *, struct string_vector_t *);

#endif
