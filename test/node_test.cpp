#include <gtest/gtest.h>

extern "C" {
  #include "node.h"
}

class NodeTest : public ::testing::Test {
protected:
  struct node_t *node;

  virtual void SetUp() {
    node = node_new("hello");
  }

  virtual void TearDown() {
    free(node);
  }
};

TEST_F(NodeTest, ToString) {
  ASSERT_STREQ("hello", node_to_string(node));
}
