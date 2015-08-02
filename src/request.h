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

static size_t write_response(void *ptr, size_t size, size_t nmemb, void *stream);

extern char* request(const char*);

#endif
