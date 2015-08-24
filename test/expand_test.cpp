#include "./test_helper.h"

extern "C" {
  #include "expand.h"
}

class ExpandTest : public ::testing::Test {
protected:
  struct string_map_t *context;

  virtual void SetUp() {
    context = string_map_new();
  }

  virtual void TearDown() {
    string_map_free(context);
  }
};

class ExpandSingleVariable : public ExpandTest {
protected:
  virtual void SetUp() {
    ExpandTest::SetUp();
    string_map_set(context, "name", "value");
  }
};

TEST_F(ExpandSingleVariable, NoVariables) {
  char *expanded = expand_string(context, "hello, world.");
  EXPECT_STREQ("hello, world.", expanded);
  free(expanded);
}

TEST_F(ExpandSingleVariable, Name) {
  char *expanded = expand_string(context, "hello, $name.");
  EXPECT_STREQ("hello, value.", expanded);
  free(expanded);
}

TEST_F(ExpandSingleVariable, MissingName) {
  char *expanded = expand_string(context, "hello, $missing.");
  EXPECT_STREQ("hello, $missing.", expanded);
  free(expanded);
}

class ExpandMultipleVariables : public ExpandTest {
protected:
  virtual void SetUp() {
    ExpandTest::SetUp();
    string_map_set(context, "name", "pkg");
    string_map_set(context, "version", "1.2.3");
  }
};

TEST_F(ExpandMultipleVariables, ExpandPackageName) {
  char *expanded = expand_string(context, "$name-$version.tar.gz");
  EXPECT_STREQ("pkg-1.2.3.tar.gz", expanded);
  free(expanded);
}
