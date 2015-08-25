#ifndef TEST_HELPER
#define TEST_HELPER

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <sstream>
#include <unistd.h>

static inline void test_capture() {
  testing::internal::CaptureStdout();
}

static inline std::string test_output() {
  return testing::internal::GetCapturedStdout();
}

#endif
