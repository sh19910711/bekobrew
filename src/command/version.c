#include "command.h"

int cmd_version(int argc, const char** argv) {
  printf("bekobrew version %s\n", BEKOBREW_VERSION);
}