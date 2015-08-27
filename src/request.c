#include "request.h"

#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

static size_t download(const char *buf, size_t size, size_t n, void *stream);

/*** public functions ***/

void request_download(const char *dst, const char *url) {
  CURL *curl;
  CURLcode status;
  struct curl_slist *headers;

  FILE *fp = fopen(dst, "w");

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  fclose(fp);
}

/*** private functions ***/
