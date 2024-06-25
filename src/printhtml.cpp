#include "printhtml.hpp"

#include <QApplication>
#include <QTemporaryFile>
#include <QWebEngineView>

PrintHTML::PrintHTML()
    : argv(new char *[] {
        new char[] { "printhtml" }
      }),
      app(argc, argv) {
  QObject::connect(&view, &QWebEngineView::loadFinished, this,
                   &PrintHTML::on_load_finished);
  QObject::connect(&view, &QWebEngineView::pdfPrintingFinished, this,
                   &PrintHTML::on_print_pdf_end);
}

PrintHTML::~PrintHTML() {
  delete[] argv[0];
  delete[] argv;
}

const char *PrintHTML::print(const char *html) {
  tasks += 1;
  QTemporaryFile tempFile;

  write_pdf(html, tempFile.fileName());

  return nullptr;
}

const char *PrintHTML::get_error_string() {
  switch (error) {
  case ErrorType::None:
    return nullptr;
  case ErrorType::AppExec:
    return "qt app returned non zero code";
  case ErrorType::LoadHTML:
    return "load html";
  case ErrorType::WritePDF:
    return "write pdf";
  }

  abort(); // unreachable
  return nullptr;
}

const char *PrintHTML::write_pdf(const char *html, const QString &path) {
  tasks += 1;

  printf("%s\n", html);
  currentPath = &path;
  view.setHtml(html);

  if (app.exec() != 0 && error == ErrorType::None) {
    error = ErrorType::AppExec;
  }

  return get_error_string();
}

void PrintHTML::on_load_finished(bool success) {
  if (!success && error == ErrorType::None) {
    error = ErrorType::LoadHTML;
    return;
  }

  view.printToPdf(*currentPath);
}

void PrintHTML::on_print_pdf_end(const QString &filePath, bool success) {
  (void)filePath;
  if (!success && error == ErrorType::None) {
    error = ErrorType::WritePDF;
  }

  tasks -= 1;

  if (tasks == 0) {
    app.exit();
  }
}
