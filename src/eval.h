#ifndef EVAL_H
#define EVAL_H

#include "bekobuild.h"

extern int eval(const struct bekobuild_t *);
extern char *eval_get_script(const struct string_vector_t *);

#endif
