#include "./test_helper.h"

extern "C" {
  #include "bekobuild.h"
}

TEST(BEKOBUILD, SimplePackage) {
  FILE* fp = fopen("./test/bekobuild_test/SimplePackage", "r");
  struct bekobuild_t* bekobuild = bekobuild_open(fp);

  EXPECT_STREQ("fake-package", bekobuild->name);
  EXPECT_EQ(2, bekobuild->build->size);
  EXPECT_STREQ("./configure", node_to_string(vector_at(bekobuild->build, 0)));
  EXPECT_STREQ("make", node_to_string(vector_at(bekobuild->build, 1)));
  EXPECT_EQ(1, bekobuild->package->size);
  EXPECT_STREQ("make install", node_to_string(vector_at(bekobuild->package, 0)));

  bekobuild_close(bekobuild);
  fclose(fp);
}
