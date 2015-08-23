#include "cli.h"

int main(int argc, char **argv) {
  struct cli_t *cli = cli_new();
  cli_set_arguments(cli, argc, argv);
  int ret = cli_run(cli);
  cli_free(cli);
  return ret;
}
