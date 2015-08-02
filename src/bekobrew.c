#include "bekobrew.h"

static struct command commands[] = {
  { "version", cmd_version },
  { "help", cmd_help },
};

static int start_with_hyphen(const char* cmd) {
  return cmd[0] == '-';
}

static struct command* find_command(const char* cmd_name) {
  int i;
  for (i = 0; i < ARRAY_SIZE(commands); i++) {
    struct command* p = commands + i;
    if (!strcmp(cmd_name, p->cmd)) {
      return p;
    }
  }
  return NULL;
}

static int parse_cli_options(int* argc, const char*** argv) {
  const char** prev_argv = *argv;
  while (*argc > 0) {
    const char* option = **argv;

    if (!start_with_hyphen(option)) {
      break;
    }

    if (!strcmp(option, "--version")) {
      break;
    }

    (*argv)++;
    (*argc)--;
  }
  return (*argv) - prev_argv;
}

static void help(int argc, const char** argv) {
  const char* cmd_name = "help";
  struct command* cmd = find_command(cmd_name);
  cmd->call(argc, argv);
}

int main(int argc, char** _argv) {
  const char** argv = (const char**)_argv;

  argv++;
  argc--;
  parse_cli_options(&argc, &argv);

  const char* cmd_name = argv[0];

  if (argc > 0) {
    skip_prefix(argv[0], "--", &argv[0]);
  } else {
    cmd_name = "help";
  }

  struct command* cmd = find_command(cmd_name);
  if (cmd) {
    cmd->call(argc, argv);
  } else {
    help(argc, argv);
  }


  return 0;
}
