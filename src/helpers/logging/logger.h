#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_NONE  // Disable logging
} LogLevel;

/**
 * Sets the current logging level.
 * Messages with a level lower than this will be ignored.
 * @param level The logging level to set.
 */
void log_set_level(LogLevel level);

/**
 * Logs a message at the specified logging level.
 * @param level The logging level of the message.
 * @param format The format string (like printf).
 * @param ... Additional arguments for the format string.
 */
void log_msg(LogLevel level, const char *format, ...);

#endif
