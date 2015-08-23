#include "./test_helper.h"

extern "C" {
  #include "string_map.h"
}

class MapTest : public ::testing::Test {
protected:
  struct map_t *self;

  virtual void SetUp() {
    self = map_new();
  }

  virtual void TearDown() {
    map_free(self);
  }
};

TEST_F(MapTest, SetAndGet) {
  ASSERT_TRUE(map_set(self, "hello", "world"));
  ASSERT_TRUE(map_set(self, "world", "hello"));
  ASSERT_STREQ("world", map_get_as_string(self, "hello"));
  ASSERT_STREQ("hello", map_get_as_string(self, "world"));
}

TEST_F(MapTest, OverrideValue) {
  ASSERT_TRUE(map_set(self, "hello", "world"));
  ASSERT_TRUE(map_set(self, "world", "hello"));
  ASSERT_TRUE(map_set(self, "hello", "world2"));
  ASSERT_STREQ("world2", map_get_as_string(self, "hello"));
  ASSERT_STREQ("hello", map_get_as_string(self, "world"));
}

TEST_F(MapTest, NotFound) {
  ASSERT_FALSE(map_get_as_string(self, "not-found"));
}
