#include "command.h"
#include <jansson.h>

int cmd_install(int argc, const char** argv) {
  const char* text = "{\"hello\": \"world\"}";
  json_error_t error;
  json_t* root = json_loads(text, 0, &error);
  printf("hello, world\n");
  printf("hello: %s\n", json_string_value(json_object_get(root, "hello")));
  json_decref(root);
}
