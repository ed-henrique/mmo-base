#ifndef LOGGER_H
#define LOGGER_H

#ifndef MAX_LOG_SIZE
#define MAX_LOG_SIZE 1024
#endif

#ifndef MAX_LOGTIME_SIZE
#define MAX_LOGTIME_SIZE 26
#endif

void logger(const char *tag, const char *message);
void log_info(const char *message);
void log_warning(const char *message);
void log_error(const char *message);

// Formatted
void flogger(const char *tag, const char *format, ...);
void flog_info(const char *format, ...);
void flog_warning(const char *format, ...);
void flog_error(const char *format, ...);

#endif /* LOGGER_H */
