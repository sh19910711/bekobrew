#ifndef CLI_TEST_H
#define CLI_TEST_H

extern "C" {
  #include "cli.h"
  #include "version.h"
}

class CLITest : public ::testing::Test {
protected:
  struct cli_t *cli;

  virtual void SetUp() {
    cli = cli_new();
    push("bekobrew");
  }

  virtual void TearDown() {
    cli_free(cli);
  }

  const char *get_argument(int k) {
    return node_to_string(vector_at(cli->args, k));
  }

  void push(const char *arg) {
    vector_push(cli->args, node_new(strdup(arg)));
  }
};

#endif
