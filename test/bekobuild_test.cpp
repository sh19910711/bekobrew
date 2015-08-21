#include "./test_helper.h"

extern "C" {
  #include "bekobuild.h"
}

TEST(BEKOBUILD, LoadFromFile) {
  FILE* fp = fopen("./test/bekobuild_test/BEKOBUILD", "r");
  struct bekobuild_t* bekobuild = open_bekobuild(fp);
  close_bekobuild(bekobuild);
  fclose(fp);
}
