#include "./test_helper.h"

extern "C" {
  #include "bekobuild.h"
}

TEST(BEKOBUILD, SimplePackage) {
  FILE* fp = fopen("./test/bekobuild_test/SimplePackage", "r");
  struct bekobuild_t* bekobuild = bekobuild_open(fp);

  EXPECT_STREQ("fake-package", bekobuild_get_name(bekobuild));
  EXPECT_EQ(2, bekobuild_get_build_num(bekobuild));
  EXPECT_STREQ("./configure", bekobuild_get_build(bekobuild)[0]);
  EXPECT_STREQ("make", bekobuild_get_build(bekobuild)[1]);
  EXPECT_EQ(1, bekobuild_get_package_num(bekobuild));
  EXPECT_STREQ("make install", bekobuild_get_package(bekobuild)[0]);

  bekobuild_close(bekobuild);
  fclose(fp);
}
