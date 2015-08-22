#include "bekobuild.h"

static struct bekobuild_t *new_bekobuild() {
  return (struct bekobuild_t*) malloc(sizeof(struct bekobuild_t));
}

static struct list_t *new_list() {
  return (struct list_t*) malloc(sizeof(struct list_t));
}

static struct seq_t *new_seq() {
  return (struct seq_t *) malloc(sizeof(struct seq_t));
}

static yaml_parser_t *new_parser() {
  return (yaml_parser_t*) malloc(sizeof(yaml_parser_t));
}

static const char **new_string_array(int n) {
  return (const char **) malloc(sizeof(const char *) * n);
}

static void init_parser(yaml_parser_t *parser, FILE* file) {
  if (!yaml_parser_initialize(parser)) {
    fputs("ERROR: yaml_parser_initialize", stderr);
    exit(1);
  }
  yaml_parser_set_input_file(parser, file);
}

static const char *to_string(yaml_token_t *token) {
  return strdup((const char *) token->data.scalar.value);
}

static size_t list_size(struct list_t *head) {
  size_t n = 0;
  struct list_t *p = head;
  while (p->next) {
    n += 1;
    p = p->next;
  }
  return n;
}

static struct seq_t *convert_list_to_seq(struct list_t *head) {
  struct list_t *p = head;
  struct seq_t *s = new_seq();
  s->n = list_size(head);
  s->data = new_string_array(s->n);
  int i = 0;
  while (p->next) {
    s->data[i++] = p->value;
    p = p->next;
  }
  return s;
}

static struct list_t *list_push(struct list_t *head, const char *value) {
  struct list_t *cur = head;
  struct list_t *next = new_list();
  cur->value = value;
  next->next = NULL;
  cur->next = next;
  return next;
}

static struct list_t *list_free(struct list_t *head) {
  struct list_t *p = head;
  struct list_t *next;
  while (p) {
    next = p->next;
    free(p);
    p = next;
  }
}

static struct seq_t *parse_seq(yaml_parser_t *parser) {
  yaml_token_t token;
  int done = 0;
  struct list_t *head = new_list();
  struct list_t *cur = head;

  while (!done) {
    if (!yaml_parser_scan(parser, &token)) {
      return NULL;
    }

    switch (token.type) {
      case YAML_BLOCK_ENTRY_TOKEN:
        break;

      case YAML_SCALAR_TOKEN:
        cur = list_push(cur, to_string(&token));
        break;

      case YAML_BLOCK_END_TOKEN:
        done = 1;
        break;

      default:
        return NULL;
    }
  }

  struct seq_t *s = convert_list_to_seq(head);
  list_free(head);
  return s;
}

static const char **resolve_item(struct bekobuild_t *self, const char *key) {
  if (!strcmp(key, "name")) {
    return &self->name;
  }
  return NULL;
}

static struct seq_t **resolve_seq(struct bekobuild_t *self, const char *key) {
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
  const char *item_key;
  struct seq_t *s;

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
        }
        flag_key = 0;
        break;

      case YAML_BLOCK_SEQUENCE_START_TOKEN:
        *resolve_seq(self, item_key) = parse_seq(self->parser);
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
  yaml_parser_delete(self->parser);
  free(self->parser);
  free(self);
}
