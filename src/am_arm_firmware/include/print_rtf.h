#ifndef PRINT_RTF_H
#define PRINT_RTF_H

#include <stdio.h>

// RTF/ANSI Terminal escape sequences for high-reliability telemetry logging
#define RTF_RESET   "\033[0m"
#define RTF_BOLD    "\033[1m"
#define RTF_CYAN    "\033[36m"
#define RTF_GREEN   "\033[32m"
#define RTF_RED     "\033[31m"
#define RTF_YELLOW  "\033[33m"

inline void print_rtf_system_status(const char* task_name, const char* status_msg, int level) {
    if (level == 0) { // Success State Info
        printf("%s[INFO][%s] %s%s\n", RTF_GREEN, task_name, status_msg, RTF_RESET);
    } else if (level == 1) { // High Priority Warning
        printf("%s%s[WARN][%s] %s%s\n", RTF_BOLD, RTF_YELLOW, task_name, status_msg, RTF_RESET);
    } else { // Hard Real-Time Fault Exception
        printf("%s%s[CRITICAL_FAULT][%s] %s%s\n", RTF_BOLD, RTF_RED, task_name, status_msg, RTF_RESET);
    }
}

#endif // PRINT_RTF_H
