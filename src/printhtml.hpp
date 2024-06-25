#pragma once

#include <QApplication>
#include <QWebEngineView>

class PrintHTML : public QObject {
  Q_OBJECT
public:
  PrintHTML();
  ~PrintHTML();

  const char *print(const char *html_cstr);
  const char *write_pdf(const char *html_cstr, const QString &path);

private slots:
  void on_load_finished(bool success);
  void on_print_pdf_end(const QString &filePath, bool success);

private:
  int argc = 1;
  char **argv;
  QApplication app;
  QWebEngineView view;
  uint32_t tasks = 0;
  const QString *currentPath = nullptr;

  enum class ErrorType {
    None,
    AppExec,
    LoadHTML,
    WritePDF,
  };
  ErrorType error = ErrorType::None;

  const char *get_error_string();
};
