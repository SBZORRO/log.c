/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

typedef struct
{
  va_list ap;
  const char *fmt;
  const char *file;
  struct tm *time;
  void *udata;
  int line;
  int level;
} log_Event;

typedef void (*log_LogFn) (log_Event *ev);
typedef void (*log_LockFn) (bool lock, void *udata);

enum
{
  LOG_TRACE,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_FATAL
};

#define log_trace(...) log_log (LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log (LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...) log_log (LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_log (LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log (LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log (LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

/* FILE *db_fp = fopen("db.log", "a"); */
/* FILE *net_fp = fopen("net.log", "a"); */
/* int db_log = log_add_fp(db_fp, LOG_INFO); */
/* int net_log = log_add_fp(net_fp, LOG_INFO); */
/* log_info_id(db_log, "query took %d ms", 42); */
/* log_warn_id(net_log, "connection dropped"); */
#define log_trace_id(id, ...) log_log_id (id, LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug_id(id, ...) log_log_id (id, LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info_id(id, ...) log_log_id (id, LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn_id(id, ...) log_log_id (id, LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error_id(id, ...) log_log_id (id, LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal_id(id, ...) log_log_id (id, LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

const char *log_level_string (int level);
void log_set_lock (log_LockFn fn, void *udata);
void log_set_level (int level);
void log_set_quiet (bool enable);
int log_add_callback (log_LogFn fn, void *udata, int level);
int log_add_fp (FILE *fp, int level);

void log_log (int level, const char *file, int line, const char *fmt, ...);
void log_log_fp (FILE *fp, int level, const char *file, int line, const char *fmt, ...);
void log_log_id (int id, int level, const char *file, int line, const char *fmt, ...);

#endif
