#include "printhtml.h"
#include "printhtml.hpp"

static PrintHTML *print_html = nullptr;

extern "C" void init() {
  if (print_html) {
    abort();
  }

  print_html = new PrintHTML();
}

extern "C" void deinit() {
  delete print_html;
  print_html = nullptr;
}

extern "C" const char *print(const char *html) {
  return print_html->print(html);
}

extern "C" const char *write_pdf(HtmlPdfMap html_pdf_map) {
  return print_html->write_pdf(html_pdf_map.html_string, html_pdf_map.pdf_path);
}

extern "C" const char *print_many(const char **html_strings, size_t length) {
  (void)html_strings;
  (void)length;
  // TODO: implement this
  abort();
}

extern "C" const char *write_many_pdf(const HtmlPdfMap *html_pdf_map,
                                      size_t length) {
  (void)html_pdf_map;
  (void)length;
  // TODO: implement this
  abort();
}