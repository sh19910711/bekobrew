#ifndef MAP_TEST_H
#define MAP_TEST_H

extern "C" {
  #include "map.h"
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

#endif
