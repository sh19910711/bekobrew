#include <gtest/gtest.h>

extern "C" {
  #include "vector.h"
}

const char *fake_items[] = { "item-0", "item-1", "item-2" };

class VectorTest : public ::testing::Test {
protected:
  struct vector_t *v;

  virtual void SetUp() {
    v = vector_new();
  }

  virtual void TearDown() {
    vector_free(v);
  }

  void push_fake_nodes() {
    for (int i = 0; i < 3; ++i) {
      vector_push(v, node_new(fake_items[i]));
    }
  }
};

TEST_F(VectorTest, AttrsBeforePushNodes) {
  ASSERT_EQ(0, v->size);
  ASSERT_EQ(1, v->capacity);
}

TEST_F(VectorTest, AttrsAfterPushNodes) {
  push_fake_nodes();
  ASSERT_EQ(3, v->size);
  ASSERT_EQ(4, v->capacity);
}

TEST_F(VectorTest, CheckNodes) {
  push_fake_nodes();
  ASSERT_STREQ("item-0", node_to_string(vector_at(v, 0)));
  ASSERT_STREQ("item-1", node_to_string(vector_at(v, 1)));
  ASSERT_STREQ("item-2", node_to_string(vector_at(v, 2)));
}
