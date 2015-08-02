#ifndef REQUEST_H
#define REQUEST_H

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE  (256 * 1024)  /* 256 KB */
#define URL_SIZE     256

struct write_result
{
  char *data;
  int pos;
};

extern char* request(const char*);

#endif
