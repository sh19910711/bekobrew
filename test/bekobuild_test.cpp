#include "./test_helper.h"

extern "C" {
  #include "bekobuild.h"
}

TEST(BEKOBUILD, LoadFromFile) {
  FILE* fp = fopen("./test/bekobuild_test/BEKOBUILD", "r");
  struct bekobuild_t* bekobuild = bekobuild_open(fp);
  ASSERT_STREQ(bekobuild_get_name(bekobuild), "fake-package");
  ASSERT_STREQ(bekobuild_get_build(bekobuild)[0], "./configure");
  ASSERT_STREQ(bekobuild_get_build(bekobuild)[1], "make");
  ASSERT_STREQ(bekobuild_get_package(bekobuild)[0], "make install");
  bekobuild_close(bekobuild);
  fclose(fp);
}
