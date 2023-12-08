#ifndef __LOGGERTYPE_H_HEADER__
#define __LOGGERTYPE_H_HEADER__

#include "Platform/Platform.h"
#include <string>

namespace nkentsuu
{
    enum class NKENTSUU_API LoggerType {
    //enum class LoggerType {
        NONE = 0,
        INFO,
        TRACE,
        DEBUG,
        WARNING,
        ERROR,
        CRITICAL,
        FATAL
        #ifdef NKENTSUU_DEBUG
        , ASSERT
        #endif
    };

    std::string NKENTSUU_API LoggerTypeToString(LoggerType type);
    LoggerType NKENTSUU_API LoggerTypeFromString(const std::string& type);
}

#endif /* __LOGGERTYPE_H_HEADER__ */
