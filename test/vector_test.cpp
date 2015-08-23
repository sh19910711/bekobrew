#include "./test_helper.h"
#include "./vector_test.h"

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
