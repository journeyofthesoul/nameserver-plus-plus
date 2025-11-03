#include "logger.h"

static LogLevel current_level = LOG_DEBUG;

void log_set_level(LogLevel level) {
    current_level = level;
}

void log_msg(LogLevel level, const char *format, ...) {
    if (level < current_level || level == LOG_NONE)
        return;

    const char *level_str;
    switch (level) {
        case LOG_DEBUG: 
            level_str = "DEBUG"; 
            break;
        case LOG_INFO:  
            level_str = "INFO"; 
            break;
        case LOG_WARN:  
            level_str = "WARN"; 
            break;
        case LOG_ERROR: 
            level_str = "ERROR"; 
            break;
        default: 
            level_str = "LOG"; 
            break;
    }

    va_list args;
    va_start(args, format);
    printf("[%s] ", level_str);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}
