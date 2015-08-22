#include "./test_helper.h"

extern "C" {
  #include "bekobuild.h"
}

TEST(BEKOBUILD, SimplePackage) {
  FILE* fp = fopen("./test/bekobuild_test/SimplePackage", "r");
  struct bekobuild_t* bekobuild = bekobuild_open(fp);

  EXPECT_STREQ("fake-package", bekobuild->name);
  EXPECT_EQ(2, bekobuild->build->n);
  EXPECT_STREQ("./configure", bekobuild->build->data[0]);
  EXPECT_STREQ("make", bekobuild->build->data[1]);
  EXPECT_EQ(1, bekobuild->package->n);
  EXPECT_STREQ("make install", bekobuild->package->data[0]);

  bekobuild_close(bekobuild);
  fclose(fp);
}
