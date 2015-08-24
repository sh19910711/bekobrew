#include "./test_helper.h"

extern "C" {
  #include "cli.h"
  #include "version.h"
}

static inline void push(struct cli_t *self, const char *arg) {
  string_vector_push(self->args, strdup(arg));
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

TEST_F(CLITest, ParseWithoutArgs) {
  cli_parse(self);
  ASSERT_STREQ("bekobrew", self->command);
  ASSERT_EQ(1, self->last_index);
}

TEST_F(CLITest, ParseWithOptionVersion) {
  push(self, "--version");
  cli_parse(self);
  ASSERT_EQ(2, self->last_index);
  ASSERT_STREQ("version", self->sub_command);
}

TEST_F(CLITest, ParseWithSubCommandVersion) {
  push(self, "version");
  cli_parse(self);
  ASSERT_STREQ("version", self->sub_command);
}

TEST_F(CLITest, RunWithoutArgs) {
  test_capture();
  cli_run(self);
  ASSERT_TRUE(test_output().find("--help", 0) != std::string::npos);
}

TEST_F(CLITest, RunWithOptionVersion) {
  test_capture();
  push(self, "--version");
  cli_run(self);
  std::stringstream expected;
  expected << "version " << BEKOBREW_VERSION;
  ASSERT_TRUE(test_output().find(expected.str(), 0) != std::string::npos);
}

TEST_F(CLITest, RunWithSubCommandVersion) {
  test_capture();
  push(self, "version");
  cli_run(self);
  std::stringstream expected;
  expected << "version " << BEKOBREW_VERSION;
  ASSERT_TRUE(test_output().find(expected.str(), 0) != std::string::npos);
}

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

TEST_F(CLITestWithArgv, Parse) {
  cli_parse(self);
  ASSERT_EQ(2, self->last_index);
  ASSERT_STREQ("version", self->sub_command);
}
