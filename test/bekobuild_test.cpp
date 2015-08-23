#include "./test_helper.h"
#include "./bekobuild_test.h"

TEST_F(BekobuildSimplePackage, Name) {
  ASSERT_STREQ("fake-package", bekobuild->name);
}

TEST_F(BekobuildSimplePackage, Build) {
  ASSERT_EQ(2, bekobuild->build->size);
  ASSERT_STREQ("./configure", node_to_string(vector_at(bekobuild->build, 0)));
  ASSERT_STREQ("make", node_to_string(vector_at(bekobuild->build, 1)));
}

TEST_F(BekobuildSimplePackage, Package) {
  ASSERT_EQ(1, bekobuild->package->size);
  ASSERT_STREQ("make install", node_to_string(vector_at(bekobuild->package, 0)));
}
