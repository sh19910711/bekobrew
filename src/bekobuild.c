#include "bekobuild.h"

static struct bekobuild_t *new_bekobuild() {
  return (struct bekobuild_t *) malloc(sizeof(struct bekobuild_t));
}

static yaml_parser_t *new_parser() {
  return (yaml_parser_t *) malloc(sizeof(yaml_parser_t));
}

static void init_parser(yaml_parser_t *parser, FILE *file) {
  if (!yaml_parser_initialize(parser)) {
    fputs("ERROR: yaml_parser_initialize", stderr);
    exit(1);
  }
  yaml_parser_set_input_file(parser, file);
}

static char *to_string(yaml_token_t *token) {
  return strdup((const char *) token->data.scalar.value);
}

static struct vector_t *parse_seq(yaml_parser_t *parser) {
  yaml_token_t token;
  int done = 0;
  struct vector_t *v = vector_new();

  while (!done) {
    if (!yaml_parser_scan(parser, &token)) {
      return NULL;
    }

    switch (token.type) {
      case YAML_BLOCK_ENTRY_TOKEN:
        break;

      case YAML_SCALAR_TOKEN:
        vector_push(v, node_new(to_string(&token)));
        break;

      case YAML_BLOCK_END_TOKEN:
        done = 1;
        break;

      default:
        return NULL;
    }

    yaml_token_delete(&token);
  }

  return v;
}

static char **resolve_item(struct bekobuild_t *self, const char *key) {
  if (!strcmp(key, "name")) {
    return &self->name;
  }
  return NULL;
}

static struct vector_t **resolve_seq(struct bekobuild_t *self, const char *key) {
  if (!strcmp(key, "build")) {
    return &self->build;
  } else if (!strcmp(key, "package")) {
    return &self->package;
  }
  return NULL;
}

static int parse(struct bekobuild_t *self) {
  yaml_token_t token;
  int done = 0;
  int flag_key = 0;
  char *item_key;

  while (!done) {
    if (!yaml_parser_scan(self->parser, &token)) {
      return 0;
    }

    switch (token.type) {
      case YAML_KEY_TOKEN:
        flag_key = 1;
        break;

      case YAML_SCALAR_TOKEN:
        if (flag_key) {
          item_key = to_string(&token);
        } else {;
          *resolve_item(self, item_key) = to_string(&token);
          free(item_key);
        }
        flag_key = 0;
        break;

      case YAML_BLOCK_SEQUENCE_START_TOKEN:
        *resolve_seq(self, item_key) = parse_seq(self->parser);
        flag_key = 0;
        break;

      case YAML_STREAM_END_TOKEN:
        done = 1;
        break;
    }

    yaml_token_delete(&token);
  }

  return 1;
}

struct bekobuild_t *bekobuild_open(FILE* file) {
  struct bekobuild_t *self = new_bekobuild();
  self->parser = new_parser();
  init_parser(self->parser, file);
  if (!parse(self)) {
    bekobuild_close(self);
    return NULL;
  }
  return self;
}

void bekobuild_close(struct bekobuild_t *self) {
  free(self->name);
  vector_free(self->build);
  vector_free(self->package);
  yaml_parser_delete(self->parser);
  free(self->parser);
  free(self);
}
