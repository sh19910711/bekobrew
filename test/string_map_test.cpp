#include "./test_helper.h"

extern "C" {
  #include "string_map.h"
}

class MapTest : public ::testing::Test {
protected:
  struct string_map_t *self;

  virtual void SetUp() {
    self = string_map_new();
  }

  virtual void TearDown() {
    string_map_free(self);
  }
};

TEST_F(MapTest, SetAndGet) {
  ASSERT_TRUE(string_map_set(self, "hello", "world"));
  ASSERT_TRUE(string_map_set(self, "world", "hello"));
  ASSERT_STREQ("world", string_map_get(self, "hello"));
  ASSERT_STREQ("hello", string_map_get(self, "world"));
}

TEST_F(MapTest, OverrideValue) {
  ASSERT_TRUE(string_map_set(self, "hello", "world"));
  ASSERT_TRUE(string_map_set(self, "world", "hello"));
  ASSERT_TRUE(string_map_set(self, "hello", "world2"));
  ASSERT_STREQ("world2", string_map_get(self, "hello"));
}

TEST_F(MapTest, NotFound) {
  ASSERT_FALSE(string_map_get(self, "not-found"));
}
