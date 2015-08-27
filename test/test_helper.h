#ifndef TEST_HELPER
#define TEST_HELPER

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

static inline std::string test_cwd() {
  char buf[256];
  getcwd(buf, 256);
  return std::string(buf);
}

static inline void test_cp(std::string src, std::string dst) {
  std::ifstream ifs(src.c_str());
  std::ofstream ofs(dst.c_str());
  ofs << ifs.rdbuf() << std::flush;
}

static inline std::string test_tmpdir() {
  char buf[256] = "/tmp/bekobrew.test.XXXXXX";
  return mkdtemp(buf);
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
