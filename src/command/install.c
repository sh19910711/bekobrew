#include "command.h"

int cmd_install(int argc, const char** argv) {
  char* text = request("https://api.github.com/repos/u-aizu/bekobrew/commits");;;;
  json_error_t error;
  json_t* root = json_loads(text, 0, &error);
  json_t* item;
  json_t* sha;
  json_t* commit;
  json_t* message;
  free(text);

  int i;
  for (i = 0; i < json_array_size(root); i++) {
    item = json_array_get(root, i);
    sha = json_object_get(item, "sha");
    commit = json_object_get(item, "commit");
    message = json_object_get(commit, "message");
    printf("%s: %s\n", json_string_value(sha), json_string_value(message));
  }

  json_decref(root);
}
