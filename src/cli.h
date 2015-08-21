#ifndef BEKOBREW_H
#define BEKOBREW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version.h"
#include "inline_utils.h"
#include "request.h"
#include "command.h"
#include "bekobuild.h"

static int start_with_hyphen(const char*);
static int parse_cli_options(int* argc, const char*** argv);

extern int cli_run(int argc, char** argv);

#endif
