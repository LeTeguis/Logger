#include "LoggerType.h"

namespace nkentsuu {
    std::string LoggerTypeToString(LoggerType type) {
        switch (type) {
            case LoggerType::NONE: return "NONE";
            case LoggerType::TRACE: return "TRACE";
            case LoggerType::DEBUG: return "DEBUG";
            case LoggerType::INFO: return "INFO";
            case LoggerType::WARNING: return "WARNING";
            case LoggerType::ERROR: return "ERROR";
            case LoggerType::CRITICAL: return "CRITICAL";
            case LoggerType::FATAL: return "FATAL";
                #ifdef NKENTSUU_DEBUG
            case LoggerType::ASSERT: return "ASSERT";
                #endif
            default: return "NONE";
        }
    }

    LoggerType LoggerTypeFromString(const std::string& type) {
        if ("NONE" == type) return LoggerType::NONE;
        if ("TRACE" == type) return LoggerType::TRACE;
        if ("DEBUG" == type) return LoggerType::DEBUG;
        if ("INFO" == type) return LoggerType::INFO;
        if ("WARNING" == type) return LoggerType::WARNING;
        if ("ERROR" == type) return LoggerType::ERROR;
        if ("CRITICAL" == type) return LoggerType::CRITICAL;
        if ("FATAL" == type) return LoggerType::FATAL;
        #ifdef NKENTSUU_DEBUG
        if ("ASSERT" == type) return LoggerType::ASSERT;
        #endif
        return LoggerType::NONE;
    }
}