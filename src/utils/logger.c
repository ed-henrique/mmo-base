#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

char lt[MAX_LOG_SIZE];
char l[MAX_LOG_SIZE];

void logger(const char *tag, const char *message) {
  time_t now;
  time(&now);
  strftime(lt, MAX_LOGTIME_SIZE, "%Y-%m-%d %H:%M:%S", localtime(&now));
  printf("%s [%s]: %s\n", lt, tag, message);
}

void log_info(const char *message) {
  logger("INFO", message);
}

void log_warning(const char *message) {
  logger("WARNING", message);
}

void log_error(const char *message) {
  logger("ERROR", message);
}

void flogger(const char *tag, const char *format, ...) {
  time_t now;
  time(&now);

  va_list args;
  va_start(args, format);
  vsnprintf(l, MAX_LOG_SIZE, format, args);
  va_end(args);

  strftime(lt, MAX_LOGTIME_SIZE, "%Y-%m-%d %H:%M:%S", localtime(&now));
  printf("%s [%s]: %s\n", lt, tag, l);
}

void flog_info(const char *format, ...) {
  va_list args;
  va_start(args, format);
  flogger("INFO", format, args);
  va_end(args);
}

void flog_warning(const char *format, ...) {
  va_list args;
  va_start(args, format);
  flogger("WARNING", format, args);
  va_end(args);
}

void flog_error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  flogger("ERROR", format, args);
  va_end(args);
}
