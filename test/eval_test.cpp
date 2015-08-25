#include "./test_helper.h"

extern "C" {
  #include "eval.h"
}

class EvalTest : public ::testing::Test {
protected:
  FILE *fp;
  struct bekobuild_t *bekobuild;

  virtual void SetUp() {
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

class CapturedEvalTest : public EvalTest {
protected:
  virtual void SetUp() {
    test_capture();
    EvalTest::SetUp();
  }
};

class EvalHelloWorld : public CapturedEvalTest {
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

class EvalHelloPackage : public CapturedEvalTest {
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
  std::string tmpdir;

  virtual void SetUp() {
    tmpdir = test_tmpdir();
    chdir(tmpdir.c_str());
    EvalTest::SetUp();
  }

  virtual void TearDown() {
    EvalTest::TearDown();
    test_rmdir(tmpdir.c_str());
  }

  const char *path() {
    return "./test/eval_test/hello/BEKOBUILD";
  }
};

TEST_F(EvalGNUHello, Install) {
  std::cout << "test_tmpdir: " << tmpdir << std::endl;
}

class GetScriptTest : public ::testing::Test {
protected:
  struct string_vector_t *commands;
  char *script;

  virtual void SetUp() {
    commands = string_vector_new();
  }

  virtual void TearDown() {
    string_vector_free(commands);
    free(script);
  }
};

class ScriptHelloWorld : public GetScriptTest {
protected:
  virtual void SetUp() {
    GetScriptTest::SetUp();
    string_vector_push(commands, strdup("echo hello"));
    string_vector_push(commands, strdup("echo world"));
    script = eval_get_script(commands);
  }
};

TEST_F(ScriptHelloWorld, Test) {
  ASSERT_TRUE(strstr(script, "echo hello\n") != NULL);
  ASSERT_TRUE(strstr(script, "echo world\n") != NULL);
}
