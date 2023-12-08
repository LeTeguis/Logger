#ifndef __ASSERT_H_HEADER__
#define __ASSERT_H_HEADER__

#include "Platform/Platform.h"

#include <string>
#include <memory>
#include "Logger.h"

namespace nkentsuu {
	// class NKENTSUU_API Assert {
	class Assert {
		public:
		Assert() {
			//m_Logger = std::make_shared<Logger>("Assert");
		}

		Assert(std::shared_ptr<Logger> logger) {
			m_Logger = logger == nullptr ? std::make_shared<Logger>("Assert") : logger;
		}

		void SetLogger(std::shared_ptr<Logger> logger) {
			m_Logger = logger;
		}

		virtual ~Assert() {
			// m_Logger.reset();
		}

		Assert& IAssert(const char* file, unsigned int ligne, const char* function){
			m_File = file;
			m_Function = function;
			m_Ligne = ligne;
			return *this;
		}

		template<typename... Args>
		Assert& False(bool compare, Args&&... args) {
			Assertion(compare == false, args...);
			return *this;
		}

		template<typename... Args>
		Assert& True(bool compare, Args&&... args) {
			Assertion(compare == true, args...);
			return *this;
		}

		template<typename T, typename... Args>
		Assert& Equal(T first, T second, Args&&... args) {
			Assertion(first == second, args...);
			return *this;
		}

		template<typename... Args>
		Assert& Null(void* ptr, Args&&... args) {
			Assertion(ptr == nullptr, args...);
			return *this;
		}

		template<typename T, typename... Args>
		Assert& Different(T first, T second, Args&&... args) {
			Assertion(first != second, args...);
			return *this;
		}

		private:

		template<typename... Args>
		void Assertion(bool compare, Args&&... args) {
			#ifdef NKENTSUU_DEBUG
			if (compare) {
				m_Logger->ILog(m_File.c_str(), m_Ligne, m_Function.c_str()).Assert("Assertion Echouer: {0}", args...);
				NKENTSUU_ASSERT_BREAK 
			}
			#endif
		}
		std::shared_ptr<Logger> m_Logger;
		std::string m_File;
		std::string m_Function;
		uint32_t m_Ligne;
	};
}

#endif /* __ASSERT_H_HEADER__ */