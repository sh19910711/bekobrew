#include "./test_helper.h"

extern "C" {
  #include "bekobuild.h"
}

TEST(BEKOBUILD, SimplePackage) {
  const char* input =
    "name: pkg\n"
    "build:\n"
    "  - ./configure\n"
    "  - make\n"
    "package:\n"
    "  - make install";
  FILE* fp = fmemopen((void*) input, strlen(input), "r");
  struct bekobuild_t* bekobuild = open_bekobuild(fp);
  close_bekobuild(bekobuild);
  fclose(fp);
}

TEST(BEKOBUILD, LoadFromFile) {
  FILE* fp = fopen("./test/bekobuild_test/BEKOBUILD", "r");
  struct bekobuild_t* bekobuild = open_bekobuild(fp);
  close_bekobuild(bekobuild);
  fclose(fp);
}
