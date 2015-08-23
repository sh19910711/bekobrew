#ifndef TEST_HELPER
#define TEST_HELPER

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <sstream>

static inline void test_capture() {
  testing::internal::CaptureStdout();
}

static inline const char *test_output() {
  return testing::internal::GetCapturedStdout().c_str();
}

#endif
