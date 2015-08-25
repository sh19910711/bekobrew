#include "./test_helper.h"

extern "C" {
  #include "eval.h"
}

class EvalTest : public ::testing::Test {
protected:
  FILE *fp;
  struct bekobuild_t *bekobuild;

  virtual void SetUp() {
    test_capture();
    fp = fopen(path(), "r");
    struct bekobuild_t *bekobuild_src = bekobuild_new();
    bekobuild_open(bekobuild_src, fp);
    bekobuild = bekobuild_expand(bekobuild_src);
    bekobuild_free(bekobuild_src);
    eval(bekobuild);
  }

  virtual void TearDown() {
    bekobuild_free(bekobuild);
    fclose(fp);
  }

  virtual const char *path() = 0;
};

class EvalHelloWorld : public EvalTest {
protected:
  const char *path() {
    return "./test/eval_test/hello_world.yml";
  }
};

TEST_F(EvalHelloWorld, Hello) {
  ASSERT_TRUE(test_output().find("hello", 0) != std::string::npos);
}

TEST_F(EvalHelloWorld, World) {
  ASSERT_TRUE(test_output().find("world", 0) != std::string::npos);
}

class EvalHelloPackage : public EvalTest {
protected:
  const char *path() {
    return "./test/eval_test/hello_package.yml";
  }
};

TEST_F(EvalHelloPackage, Hello) {
  ASSERT_TRUE(test_output().find("hello", 0) != std::string::npos);
}

TEST_F(EvalHelloPackage, Package) {
  ASSERT_TRUE(test_output().find("hello-package", 0) != std::string::npos);
}

class EvalGNUHello : public EvalTest {
protected:
  const char *path() {
    return "./test/eval_test/hello/BEKOBUILD";
  }
};

TEST_F(EvalGNUHello, Install) {
  std::cout << test_output() << std::endl;
}
