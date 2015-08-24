#ifndef REQUEST_H
#define REQUEST_H

struct write_result {
  char *data;
  int pos;
};

extern char *request(const char*);

#endif
