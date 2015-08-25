#ifndef TEST_HELPER
#define TEST_HELPER

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <sstream>
#include <unistd.h>

static inline std::string test_tmpdir() {
  char buf[256];

  FILE *proc = popen("mktemp", "r");
  fgets(buf, 256, proc);
  pclose(proc);

  return std::string(buf);
}

static inline void test_rmdir(const char *path) {
  std::stringstream ss;
  ss << "rm -r " << path;
  system(ss.str().c_str());
}

static inline void test_capture() {
  testing::internal::CaptureStdout();
}

static inline std::string test_output() {
  return testing::internal::GetCapturedStdout();
}

#endif
