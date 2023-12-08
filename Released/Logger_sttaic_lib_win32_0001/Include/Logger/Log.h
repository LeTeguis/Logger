#ifndef __LOG_H_HEADER__
#define __LOG_H_HEADER__

#pragma once

#include "Platform/Platform.h"
#include "Logger.h"
#include "Assert.h"

namespace nkentsuu {
	class NKENTSUU_API Log {
		public:

			static Log& Instance() {
				static Log unitTest;
				return unitTest;
			}

			std::shared_ptr<Logger> GetLogger() {
				return Logger__;
			}

			std::shared_ptr<Assert> GetAssert() {
				return Assert__;
			}
		private:
			std::shared_ptr<Logger> Logger__;
			std::shared_ptr<Assert> Assert__;
			Log(){
				Logger__ = std::make_shared<Logger>("Nkentsuu");
				Assert__ = std::make_shared<Assert>(Logger__);
			}
	};

	#define LOG				Log::Instance().GetLogger()->ILog(__FILE__, __LINE__, __FUNCTION__)
	#define ASSERT			Log::Instance().GetAssert()->IAssert(__FILE__, __LINE__, __FUNCTION__)
}

#endif /* __LOG_H_HEADER__ */
