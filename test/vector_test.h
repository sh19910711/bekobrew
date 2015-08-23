#ifndef VECTOR_TEST
#define VECTOR_TEST

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
      vector_push(v, node_new(strdup(fake_items[i])));
    }
  }
};

#endif
