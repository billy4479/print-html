#include "printhtml.h"
#include <stdio.h>

int main() {
  init();

  struct HtmlPdfMap html_pdf_map = {
      .html_string = "<h1> Hello World </h1>\n",
      .pdf_path = "./test.pdf",
  };

  const char *result = write_pdf(html_pdf_map);
  deinit();

  if (result) {
    printf("Result is not null, an error has occurred: %s\n", result);
    return 1;
  }

  return 0;
}