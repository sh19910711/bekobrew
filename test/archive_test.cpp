#include "./test_helper.h"

extern "C" {
  #include "archive.h"
}

#ifdef HAVE_FMEMOPEN

class ArchiveMemTest : public ::testing::Test {
protected:
  FILE *fp;

  virtual void SetUp() {
    fp = fmemopen(get_input(), get_input_length(), "r");
  }

  virtual void TearDown() {
    fclose(fp);
  }

  virtual int *get_input() = 0;
  virtual int get_input_length() = 0;
  virtual int *get_expected() = 0;
  virtual int get_expected_length() = 0;
};

class HelloWorld : public ArchiveMemTest {
protected:
  int input[44] = {
    0x8b, 0x1f, 0x08, 0x08, 0xf2,
    0xa8, 0x55, 0xdf, 0x03, 0x00,
    0x65, 0x68, 0x6c, 0x6c, 0x2e,
    0x6f, 0x78, 0x74, 0x00, 0x74,
    0x48, 0xf3, 0xc9, 0xcd, 0xd7,
    0xc9, 0x08, 0x51, 0x2f, 0xcf,
    0x49, 0xca, 0x02, 0xe1, 0x90,
    0x00, 0xf6, 0x3a, 0x0d, 0x40,
    0x00, 0x00, 0x00, 0x00
  };

  int expected[14] = {
    0x65, 0x48, 0x6c, 0x6c, 0x2c,
    0x6f, 0x57, 0x20, 0x72, 0x6f,
    0x64, 0x6c, 0x00, 0x0a,
  };

  virtual void SetUp() {
    ArchiveMemTest::SetUp();
  }

  virtual int *get_input() {
    return input;
  }

  virtual int get_input_length() {
    return 44;
  }

  virtual int *get_expected() {
    return expected;
  }

  virtual int get_expected_length() {
    return 14;
  }
};

TEST_F(HelloWorld, Hello) {
}

#endif
