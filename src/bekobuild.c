#include "bekobuild.h"
#include "context.h"

static yaml_parser_t *new_parser();
static void init_parser(yaml_parser_t *, FILE *);
static char *to_string(yaml_token_t *);
static struct string_vector_t *parse_seq(yaml_parser_t *);
static char **resolve_item(struct bekobuild_t *, const char *);
static struct string_vector_t **resolve_seq(struct bekobuild_t *, const char *);
static int parse(struct bekobuild_t *);
static struct context_t *get_context(struct bekobuild_t *);
static char *copy_attribute(const char *);
static inline void free_string(void *);
static inline void free_seq(void *);
static inline void free_attributes(struct bekobuild_t *);
static inline void free_parser(void *);

/*** public functions ***/

struct bekobuild_t *bekobuild_new() {
  return (struct bekobuild_t *) calloc(1, sizeof(struct bekobuild_t));
}

void bekobuild_free(struct bekobuild_t *self) {
  free_string(self->name);
  free_string(self->version);
  free_seq(self->build);
  free_seq(self->package);
  free_parser(self->parser);
  free(self);
}

int bekobuild_open(struct bekobuild_t *self, FILE* file) {
  self->parser = new_parser();
  init_parser(self->parser, file);
  return parse(self);
}

struct bekobuild_t *bekobuild_expand(struct bekobuild_t *self) {
  struct context_t *context = get_context(self);
  struct bekobuild_t *expanded = bekobuild_new();

  expanded->name    = copy_attribute(self->name);
  expanded->version = copy_attribute(self->version);
  expanded->build   = context_expand_string_vector(context, self->build);
  expanded->package = context_expand_string_vector(context, self->package);

  context_free(context);
  return expanded;
}

/*** private functions ***/

static char *to_string(yaml_token_t *token) {
  return strdup((const char *) token->data.scalar.value);
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

static struct string_vector_t *parse_seq(yaml_parser_t *parser) {
  yaml_token_t token;
  int done = 0;
  struct string_vector_t *v = string_vector_new();

  while (!done) {
    if (!yaml_parser_scan(parser, &token)) {
      return NULL;
    }

    switch (token.type) {
      case YAML_BLOCK_ENTRY_TOKEN:
        break;

      case YAML_SCALAR_TOKEN:
        string_vector_push(v, to_string(&token));
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
  } else if (!strcmp(key, "version")) {
    return &self->version;
  }
  return NULL;
}

static struct string_vector_t **resolve_seq(struct bekobuild_t *self, const char *key) {
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
      case YAML_STREAM_START_TOKEN:
        break;

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

      case YAML_VALUE_TOKEN:
        break;

      case YAML_BLOCK_SEQUENCE_START_TOKEN:
        *resolve_seq(self, item_key) = parse_seq(self->parser);
        free(item_key);
        flag_key = 0;
        break;

      case YAML_BLOCK_MAPPING_START_TOKEN:
        break;

      case YAML_BLOCK_END_TOKEN:
        break;

      case YAML_STREAM_END_TOKEN:
        done = 1;
        break;

      case YAML_ALIAS_TOKEN:
        break;

      default:
        fprintf(stderr, "WARN: YAML Unknown Token: %d\n", token.type);
        break;

    }

    yaml_token_delete(&token);
  }

  return 1;
}

static struct context_t *get_context(struct bekobuild_t *self) {
  struct context_t *context = context_new();
  if (self->name) {
    string_map_set(context->map, "name", self->name);
  }
  if (self->version) {
    string_map_set(context->map, "version", self->version);
  }
  context_calc_max_length(context);
  return context;
}

static char *copy_attribute(const char *s) {
  return s ? strdup(s) : NULL;
}

static inline void free_string(void *attr) {
  if (attr) {
    free(attr);
  }
}

static inline void free_seq(void *seq) {
  if (seq) {
    string_vector_free(seq);
  }
}

static inline void free_parser(void *parser) {
  if (parser) {
    yaml_parser_delete(parser);
    free(parser);
  }
}
