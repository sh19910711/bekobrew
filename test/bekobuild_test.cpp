#include "./test_helper.h"

extern "C" {
  #include "bekobuild.h"
}

class BekobuildTest : public ::testing::Test {
protected:
  FILE *fp;
  struct bekobuild_t *bekobuild;

  virtual void SetUp() {
    fp = fopen(path(), "r");
    bekobuild = bekobuild_open(fp);
  }

  virtual void TearDown() {
    bekobuild_close(bekobuild);
    fclose(fp);
  }

  virtual const char *path() = 0;
};

class BekobuildSimplePackage : public BekobuildTest {
protected:
  const char *path() {
    return "./test/bekobuild_test/SimplePackage";
  }
};

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
