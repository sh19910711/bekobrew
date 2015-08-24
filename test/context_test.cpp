#include "./test_helper.h"

extern "C" {
  #include "context.h"
}

class ExpandTest : public ::testing::Test {
protected:
  struct context_t *context;
  struct string_map_t *map;

  virtual void SetUp() {
    context = context_new();
  }

  virtual void TearDown() {
    context_free(context);
  }
};

class ExpandSingleVariable : public ExpandTest {
protected:
  virtual void SetUp() {
    ExpandTest::SetUp();
    string_map_set(context->map, "name", "value");
    context_calc_max_length(context);
  }
};

TEST_F(ExpandSingleVariable, NoVariables) {
  char *expanded = context_expand_string(context, "hello, world.");
  EXPECT_STREQ("hello, world.", expanded);
  free(expanded);
}

TEST_F(ExpandSingleVariable, Name) {
  char *expanded = context_expand_string(context, "hello, $name.");
  EXPECT_STREQ("hello, value.", expanded);
  free(expanded);
}

TEST_F(ExpandSingleVariable, MissingName) {
  char *expanded = context_expand_string(context, "hello, $missing.");
  EXPECT_STREQ("hello, $missing.", expanded);
  free(expanded);
}

class ExpandMultipleVariables : public ExpandTest {
protected:
  virtual void SetUp() {
    ExpandTest::SetUp();
    string_map_set(context->map, "name", "pkg");
    string_map_set(context->map, "version", "1.2.3");
    context_calc_max_length(context);
  }
};

TEST_F(ExpandMultipleVariables, ExpandPackageName) {
  char *expanded = context_expand_string(context, "$name-$version.tar.gz");
  EXPECT_STREQ("pkg-1.2.3.tar.gz", expanded);
  free(expanded);
}
