#include "./test_helper.h"

extern "C" {
  #include "bekobuild.h"
}

class BekobuildTest : public ::testing::Test {
protected:
  FILE *fp;
  struct bekobuild_t *self;

  virtual void SetUp() {
    fp = fopen(path(), "r");
    self = bekobuild_new();
    bekobuild_open(self, fp);
  }

  virtual void TearDown() {
    bekobuild_free(self);
    fclose(fp);
  }

  virtual const char *path() = 0;
};

class BekobuildSimplePackage : public BekobuildTest {
protected:
  const char *path() {
    return "./test/bekobuild_test/simple_package.yml";
  }
};

TEST_F(BekobuildSimplePackage, Name) {
  ASSERT_TRUE(self->name);
  ASSERT_STREQ("fake-package", self->name);
}

TEST_F(BekobuildSimplePackage, Sources) {
  ASSERT_TRUE(self->sources);
  ASSERT_EQ(1, self->sources->size);
  ASSERT_STREQ("http://localhost:8080/path/to/package.tar.gz",
               string_vector_at(self->sources, 0));
}

TEST_F(BekobuildSimplePackage, Sums) {
  ASSERT_TRUE(self->sums);
  ASSERT_EQ(1, self->sums->size);
  ASSERT_STREQ("SHA-256", string_vector_at(self->sums, 0));
}

TEST_F(BekobuildSimplePackage, Build) {
  ASSERT_TRUE(self->build);
  ASSERT_EQ(2, self->build->size);
  ASSERT_STREQ("./configure", string_vector_at(self->build, 0));
  ASSERT_STREQ("make", string_vector_at(self->build, 1));
}

TEST_F(BekobuildSimplePackage, Package) {
  ASSERT_TRUE(self->package);
  ASSERT_EQ(1, self->package->size);
  ASSERT_STREQ("make install", string_vector_at(self->package, 0));
}

class BekobuildEvalTest : public BekobuildTest {
protected:
  struct bekobuild_t *expanded;

  virtual void SetUp() {
    BekobuildTest::SetUp();
    expanded = bekobuild_expand(self);
  }

  virtual void TearDown() {
    bekobuild_free(expanded);
    BekobuildTest::TearDown();
  }

  const char *path() {
    return "./test/bekobuild_test/eval_test.yml";
  }
};

TEST_F(BekobuildEvalTest, SourceBuild) {
  ASSERT_TRUE(self->build);
  ASSERT_EQ(2, self->build->size);
  ASSERT_STREQ("echo build: $name", string_vector_at(self->build, 0));
  ASSERT_STREQ("echo build: $version", string_vector_at(self->build, 1));
}

TEST_F(BekobuildEvalTest, SourcePackage) {
  ASSERT_TRUE(self->package);
  ASSERT_EQ(2, self->package->size);
  ASSERT_STREQ("echo package: $name", string_vector_at(self->package, 0));
  ASSERT_STREQ("echo package: $version", string_vector_at(self->package, 1));
}

TEST_F(BekobuildEvalTest, ExpandedName) {
  ASSERT_TRUE(expanded->name);
  ASSERT_STREQ("package-name", expanded->name);
}

TEST_F(BekobuildEvalTest, ExpandedVersion) {
  ASSERT_TRUE(expanded->version);
  ASSERT_STREQ("1.2.3", expanded->version);
}

TEST_F(BekobuildEvalTest, ExpandedBuild) {
  ASSERT_TRUE(expanded->build);
  ASSERT_EQ(2, expanded->build->size);
  ASSERT_STREQ("echo build: package-name", string_vector_at(expanded->build, 0));
  ASSERT_STREQ("echo build: 1.2.3", string_vector_at(expanded->build, 1));
}

TEST_F(BekobuildEvalTest, ExpandedPackage) {
  ASSERT_TRUE(expanded->package);
  ASSERT_EQ(2, expanded->package->size);
  ASSERT_STREQ("echo package: package-name", string_vector_at(expanded->package, 0));
  ASSERT_STREQ("echo package: 1.2.3", string_vector_at(expanded->package, 1));
}
