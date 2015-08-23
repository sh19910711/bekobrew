#include "./test_helper.h"
#include "./cli_test.h"

TEST_F(CLITest, CreateWithoutAnyArguments) {
  ASSERT_EQ(cli->args->size, 1);
  ASSERT_STREQ(get_argument(0), "bekobrew");
}

TEST_F(CLITest, RunWithoutArgs) {
  test_capture();
  cli_run(cli);
  ASSERT_TRUE(strstr(test_output(), "--help"));
}

TEST_F(CLITest, RunWithOptionVersion) {
  test_capture();
  push("--version");
  std::stringstream expected;
  expected << "version " << BEKOBREW_VERSION << std::endl;
  ASSERT_TRUE(strstr(test_output(), expected.str().c_str()));
}

TEST_F(CLITest, RunWithSubCommandVersion) {
  test_capture();
  push("version");
  std::stringstream expected;
  expected << "version " << BEKOBREW_VERSION << std::endl;
  ASSERT_TRUE(strstr(test_output(), expected.str().c_str()));
}
