#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct HtmlPdfMap {
  const char *html_string;
  const char *pdf_path;
};

void init();
void deinit();

const char *print(const char *html);
const char *write_pdf(struct HtmlPdfMap);

const char *print_many(const char **html_strings, size_t length);
const char *write_many_pdf(const struct HtmlPdfMap *html_pdf_map,
                           size_t length);

#ifdef __cplusplus
}
#endif
