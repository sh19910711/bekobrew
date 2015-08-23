#include "./test_helper.h"

extern "C" {
  #include "string_vector.h"
}

class VectorTest : public ::testing::Test {
protected:
  struct string_vector_t *v;

  virtual void SetUp() {
    v = string_vector_new();
  }

  virtual void TearDown() {
    string_vector_free(v);
  }

  void push_fake_nodes() {
    const char *fake_items[] = { "item-0", "item-1", "item-2" };
    for (int i = 0; i < 3; ++i) {
      string_vector_push(v, strdup(fake_items[i]));
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
  ASSERT_STREQ("item-0", string_vector_at(v, 0));
  ASSERT_STREQ("item-1", string_vector_at(v, 1));
  ASSERT_STREQ("item-2", string_vector_at(v, 2));
}
