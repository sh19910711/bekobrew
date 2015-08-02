#include "command.h"
#include <jansson.h>
#include <curl/curl.h>

#define BUFFER_SIZE  (256 * 1024)  /* 256 KB */

#define URL "https://api.github.com/repos/u-aizu/bekobrew/commits"
#define URL_SIZE     256

struct write_result
{
  char *data;
  int pos;
};

static size_t write_response(void *ptr, size_t size, size_t nmemb, void *stream)
{
  struct write_result *result = (struct write_result *)stream;

  if(result->pos + size * nmemb >= BUFFER_SIZE - 1)
  {
    fprintf(stderr, "error: too small buffer\n");
    return 0;
  }

  memcpy(result->data + result->pos, ptr, size * nmemb);
  result->pos += size * nmemb;

  return size * nmemb;
}

static char *request(const char *url)
{
  CURL *curl = NULL;
  CURLcode status;
  struct curl_slist *headers = NULL;
  char *data = NULL;
  long code;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(!curl)
    goto error;

  data = malloc(BUFFER_SIZE);
  if(!data)
    goto error;

  struct write_result write_result = {
    .data = data,
    .pos = 0
  };

  curl_easy_setopt(curl, CURLOPT_URL, url);

  /* GitHub commits API v3 requires a User-Agent header */
  headers = curl_slist_append(headers, "User-Agent: Jansson-Tutorial");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_result);

  status = curl_easy_perform(curl);
  if(status != 0)
  {
    fprintf(stderr, "error: unable to request data from %s:\n", url);
    fprintf(stderr, "%s\n", curl_easy_strerror(status));
    goto error;
  }

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
  if(code != 200)
  {
    fprintf(stderr, "error: server responded with code %ld\n", code);
    goto error;
  }

  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);
  curl_global_cleanup();

  /* zero-terminate the result */
  data[write_result.pos] = '\0';

  return data;

error:
  if(data)
    free(data);
  if(curl)
    curl_easy_cleanup(curl);
  if(headers)
    curl_slist_free_all(headers);
  curl_global_cleanup();
  return NULL;
}

int cmd_install(int argc, const char** argv) {
  char* text = request(URL);
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
