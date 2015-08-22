#include <gtest/gtest.h>

extern "C" {
  #include "node.h"
}

TEST(Node, String) {
  const char *input = "hello";
  struct node_t node;
  node_set_value(&node, input);
  ASSERT_STREQ("hello", node_to_string(&node));
}
