#include "./test_helper.h"
#include "./cli_test.h"

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

TEST_F(CLITestWithArgv, Parse) {
  cli_parse(self);
  ASSERT_EQ(2, self->last_index);
  ASSERT_STREQ("version", self->sub_command);
}
