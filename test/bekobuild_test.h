#ifndef BEKOBREW_TEST
#define BEKOBREW_TEST

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

#endif
