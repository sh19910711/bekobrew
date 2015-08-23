#ifndef CLI_TEST_H
#define CLI_TEST_H

extern "C" {
  #include "cli.h"
  #include "version.h"
}

static inline void push(struct cli_t *self, const char *arg) {
  vector_push(self->args, node_new(strdup(arg)));
}

class CLITestBase : public ::testing::Test {
protected:
  struct cli_t *self;

  virtual void SetUp() {
    self = cli_new();
  }

  virtual void TearDown() {
    cli_free(self);
  }
};

class CLITest : public CLITestBase {
protected:
  virtual void SetUp() {
    CLITestBase::SetUp();
    push(self, "bekobrew");
  }
};

class CLITestWithArgv : public CLITestBase {
protected:
  int argc;
  char **argv;

  virtual void SetUp() {
    CLITestBase::SetUp();

    argc = 2;
    argv = (char **)malloc(sizeof(char *) * argc);
    argv[0] = strdup("bekobrew");
    argv[1] = strdup("--version");

    cli_set_arguments(self, argc, argv);
  }

  virtual void TearDown() {
    CLITestBase::TearDown();
    free(argv[0]);
    free(argv[1]);
    free(argv);
  }
};

#endif
