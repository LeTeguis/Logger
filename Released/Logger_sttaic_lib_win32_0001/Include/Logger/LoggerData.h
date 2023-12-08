#ifndef __LOGGERDATA_H_HEADER__
#define __LOGGERDATA_H_HEADER__

#include "Platform/Platform.h"
#include "StringFormatter.h"
#include <string>

namespace nkentsuu
{
    struct NKENTSUU_API LoggerData {
		std::string		LDName;         // name
		LoggerType		LDType;         // type
		std::string		LDFile;         // file
		std::string		LDFunction;     // function
		uint32_t		LDLine;         // line
		std::string		LDHeader;       // header
		std::string		LDMessage;      // message

		LoggerData(const std::string& name, LoggerType type, const std::string& file,
				   const std::string& function, uint32_t line,
				   const std::string& header, const std::string& message)
			: LDName(name), LDType(type), LDFile(file), LDFunction(function),
			LDLine(line), LDHeader(header), LDMessage(message) {}

		std::string GetLine() {
			return STRING_FORMATTER.Format("{0}", LDLine);
		}

		std::string GetType() {
            return (LoggerTypeToString(LDType));
		}

	};
}

#endif /* __LOGGERDATA_H_HEADER__ */
