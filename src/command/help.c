#include "command.h"

const char usage_text[] = 
  "bekobrew [--version] [--help]\n";

int cmd_help(int argc, const char** argv) {
  printf(usage_text);
}
