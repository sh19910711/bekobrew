#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>

#include "version.h"
#include "inline_utils.h"

extern int cmd_version(int argc, const char** argv);
extern int cmd_help(int argc, const char** argv);
extern int cmd_install(int argc, const char** argv);

#endif
