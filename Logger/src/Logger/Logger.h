#ifndef __LOGGER_H_HEADER__
#define __LOGGER_H_HEADER__

#include <chrono>
#include <functional>
#include "StringFormatter.h"
#include "LoggerType.h"
#include "LoggerData.h"

namespace nkentsuu
{
    using LogCallbackFn = std::function<void(const LoggerData&)>;
    #define BIND_LOG_FN(x, p) std::bind(&x, this, std::placeholders::_##p)

    /**
     * @brief base of all logger
     * 
     */
    class NKENTSUU_API Logger {
        public:
            /**
             * @brief Construct a new Logger object
             * 
             */
            Logger() : m_name("Log")
            {
                SetDefaultDisplayOptions();
            }

            /**
             * @brief Construct a new Logger object
             * 
             * @param name 
             * @param format 
             */
            Logger(std::string name, std::string format) : m_name(name)
            {
                SetDisplayOptions(format);
            }

            /**
             * @brief Construct a new Logger object
             * 
             * @param name 
             */
            Logger(std::string name) : m_name(name)
            {
                SetDefaultDisplayOptions();
            }

            /**
             * @brief Destroy the Logger object
             * 
             */
            virtual ~Logger() = default;

            /**
             * @brief Give the string name of the logger type
             * 
             * @param loggerType 
             * @return std::string 
             */
            static std::string ToString(const LoggerType& loggerType)
            {
                return LoggerTypeToString(loggerType);
            }

            /**
             * @brief Change the name and format of the logger instance
             * 
             * @param name 
             * @param format 
             */
            void Set(std::string name, std::string format)
            {
                this->m_name = name;
                SetDisplayOptions(format);
            }

            /**
             * @brief Set the Name object
             * 
             * @param name 
             */
            void SetName(std::string name)
            {
                this->m_name = name;
            }

            /**
             * @brief Get the Name object
             * 
             * @return const std::string 
             */
            const std::string GetName()
            {
                return m_name;
            }

            /**
             * @brief Set the Display Options object for formatting the string logger message
             * 
             * @param format 
             */
            void SetDisplayOptions(std::string format)
            {
                m_format = format;
            }

            /**
             * @brief Set the Default Display Options object
             * 
             */
            void SetDefaultDisplayOptions()
            {
                m_format = "%D %X | %F > %L > %f | [%N] : ";
            }

            /**
             * @brief Generate the logger message with the specific type
             * 
             * @tparam Args 
             * @param loggerType 
             * @param file 
             * @param ligne 
             * @param function 
             * @param format 
             * @param args 
             */

            Logger& ILog(const char* file, unsigned int ligne, const char* function) {
                m_File = file;
                m_Function = function;
                m_Ligne = ligne;
                return *this;
            }

            /**
             * @brief Generate the logger message with the Info type of logger
             *
             * @tparam Args
             * @param file
             * @param ligne
             * @param function
             * @param format
             * @param args
             */
            template<typename... Args>
            void Info(const char* format = "", Args&&... args) {
                std::string formattedMessage = STRING_FORMATTER.Format(format, args...);
                m_Header = formatOptionString(m_File.c_str(), m_Ligne, m_Function.c_str());
                m_LogType = LoggerType::INFO;
                if (m_Callback != nullptr) {
					m_Callback({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                }
                if (!m_StopDefaultWriting)
                    write(LoggerType::INFO, m_Header, formattedMessage);
            }

            #ifdef NKENTSUU_DEBUG
            /**
             * @brief Generate the logger message with the Assert type of logger
             *
             * @tparam Args
             * @param file
             * @param ligne
             * @param function
             * @param format
             * @param args
             */
            template<typename... Args>
            void Assert(const char* format = "", Args&&... args) {
                std::string formattedMessage = STRING_FORMATTER.Format(format, args...);
                m_Header = formatOptionString(m_File.c_str(), m_Ligne, m_Function.c_str());
                m_LogType = LoggerType::ASSERT;
                if (m_Callback != nullptr) {
					m_Callback({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                }
                if (!m_StopDefaultWriting)
                    write(LoggerType::ASSERT, m_Header, formattedMessage);
            }
            #endif

            /**
             * @brief Generate the logger message with the Error type of logger
             *
             * @tparam Args
             * @param file
             * @param ligne
             * @param function
             * @param format
             * @param args
             */
            template<typename... Args>
            void Error(const char* format = "", Args&&... args) {
                std::string formattedMessage = STRING_FORMATTER.Format(format, args...);
                m_Header = formatOptionString(m_File.c_str(), m_Ligne, m_Function.c_str());
                m_LogType = LoggerType::ERROR;
                if (m_Callback != nullptr) {
					m_Callback({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                }
                if (!m_StopDefaultWriting)
                    write(LoggerType::ERROR, m_Header, formattedMessage);
            }

            /**
             * @brief Generate the logger message with the Warning type of logger
             *
             * @tparam Args
             * @param file
             * @param ligne
             * @param function
             * @param format
             * @param args
             */
            template<typename... Args>
            void Warning(const char* format = "", Args&&... args) {
                std::string formattedMessage = STRING_FORMATTER.Format(format, args...);
                m_Header = formatOptionString(m_File.c_str(), m_Ligne, m_Function.c_str());
                m_LogType = LoggerType::WARNING;
                if (m_Callback != nullptr) {
					m_Callback({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                }
                if (!m_StopDefaultWriting)
                    write(LoggerType::WARNING, m_Header, formattedMessage);
            }

            /**
             * @brief Generate the logger message with the Debug type of logger
             *
             * @tparam Args
             * @param file
             * @param ligne
             * @param function
             * @param format
             * @param args
             */
            template<typename... Args>
            void Debug(const char* format = "", Args&&... args) {
                std::string formattedMessage = STRING_FORMATTER.Format(format, args...);
                m_Header = formatOptionString(m_File.c_str(), m_Ligne, m_Function.c_str());
                m_LogType = LoggerType::DEBUG;
                if (m_Callback != nullptr) {
					m_Callback({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                }
                if (!m_StopDefaultWriting)
                    write(LoggerType::DEBUG, m_Header, formattedMessage);
            }

            /**
             * @brief Generate the logger message with the Trace type of logger
             *
             * @tparam Args
             * @param file
             * @param ligne
             * @param function
             * @param format
             * @param args
             */
            template<typename... Args>
            void Trace(const char* format = "", Args&&... args) {
                std::string formattedMessage = STRING_FORMATTER.Format(format, args...);
                m_Header = formatOptionString(m_File.c_str(), m_Ligne, m_Function.c_str());
                m_LogType = LoggerType::TRACE;
                if (m_Callback != nullptr) {
					m_Callback({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                }
                if (!m_StopDefaultWriting)
                    write(LoggerType::TRACE, m_Header, formattedMessage);
            }

            /**
             * @brief Generate the logger message with the Critical type of logger
             *
             * @tparam Args
             * @param file
             * @param ligne
             * @param function
             * @param format
             * @param args
             */
            template<typename... Args>
            void Critical(const char* format = "", Args&&... args) {
                std::string formattedMessage = STRING_FORMATTER.Format(format, args...);
                m_Header = formatOptionString(m_File.c_str(), m_Ligne, m_Function.c_str());
                m_LogType = LoggerType::CRITICAL;
                if (m_Callback != nullptr) {
					m_Callback({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                }
                if (!m_StopDefaultWriting)
                    write(LoggerType::CRITICAL, m_Header, formattedMessage);
            }

            /**
             * @brief Generate the logger message with the Fatal type of logger
             *
             * @tparam Args
             * @param file
             * @param ligne
             * @param function
             * @param format
             * @param args
             */
            template<typename... Args>
            void Fatal(const char* format = "", Args&&... args) {
                std::string formattedMessage = STRING_FORMATTER.Format(format, args...);
                m_Header = formatOptionString(m_File.c_str(), m_Ligne, m_Function.c_str());
                m_LogType = LoggerType::FATAL;
                if (m_Callback != nullptr) {
					m_Callback({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                }
                if (!m_StopDefaultWriting)
                    write({ m_name, m_LogType, m_File, m_Function, m_Ligne, m_Header, formattedMessage });
                    //write(LoggerType::FATAL, m_Header, formattedMessage);
            }

            std::string GetHeader() { return m_Header; }
            std::string GetFile() { return m_File; }
            std::string GetFunction() { return m_Function; }
            unsigned int GetLine() { return m_Ligne; }

            void SetCallBack(LogCallbackFn callback) {
                m_Callback = callback;
            }

            void StopDefaultWriting(bool stop){
                m_StopDefaultWriting = stop;
            }

            bool IsDefaultWritingStop(){
                return m_StopDefaultWriting;
            }

        protected:
            /**
             * @brief abstract write method for diffrent logging like consol, file, etc
             * 
             * @param loggerType 
             * @param entete 
             * @param message 
             */
            virtual void write(LoggerType loggerType, const std::string& entete, const std::string& message){
                std::string beginColor = GetColorCode(loggerType);
                std::string endColor = "\033[0m";

                #ifdef NKENTSUU_PLATFORM_ANDROID
                __android_log_print(ANDROID_LOG_INFO, "", " %s [%s%s%s] %s", entete.c_str(), beginColor, Logger::ToString(loggerType).c_str(), endColor, message.c_str());
                return;
                #endif
                std::cout << entete << " [" << beginColor << Logger::ToString(loggerType) << endColor << "] >> " << message << std::endl;
            }

            /**
             * @brief abstract write method for diffrent logging like consol, file, etc
             * 
             * @param loggerType 
             * @param entete 
             * @param message 
             */
            virtual void write(const LoggerData& logger_data){
                std::string beginColor = GetColorCode(logger_data.LDType);
                std::string endColor = "\033[0m";

                std::string logType = Logger::ToString(logger_data.LDType);
                std::string header = logger_data.LDHeader;
                std::string message = logger_data.LDMessage;

                #ifdef NKENTSUU_PLATFORM_ANDROID
                __android_log_print(ANDROID_LOG_INFO, "", " %s [%s%s%s] %s", header.c_str(), beginColor, logType.c_str(), endColor, message.c_str());
                return;
                #endif
                std::cout << header << " [" << beginColor << logType << endColor << "] >> " << message << std::endl;
            }

            std::string GetColorCode(LoggerType type)
            {
                switch (type)
                {
                case LoggerType::ERROR:    return "\033[1;31m"; // Red
                case LoggerType::WARNING:  return "\033[1;33m"; // Yellow
                case LoggerType::DEBUG:    return "\033[1;34m"; // Blue
                case LoggerType::TRACE:    return "\033[1;36m"; // Cyan
                case LoggerType::CRITICAL: return "\033[1;35m"; // Purple
                case LoggerType::INFO:     return "\033[1;32m"; // Green
                case LoggerType::FATAL: return "\033[1;41m"; // Dark Red
                #ifdef NKENTSUU_DEBUG
                case LoggerType::ASSERT: return "\033[1;41m"; // Dark Red
                #endif
                }
                return "";
            }

        private:
            // Nom du journal
            std::string m_name;
            // Options d'affichage
            std::string m_format;

            std::string m_File;
            std::string m_Function;
            unsigned int m_Ligne;

            std::string m_Header;

            LoggerType m_LogType;

            LogCallbackFn m_Callback;

            bool m_StopDefaultWriting = false;
        private:
            

            /**
             * @brief Convert the Chrono object to string representation
             * 
             * @param now_c 
             * @param ch 
             * @return std::string 
             */
            std::string GetChrono(std::time_t& now_c, const char* ch)
            {
                std::stringstream ss;
                ss << std::put_time(std::localtime(&now_c), ch);
                return ss.str();
            }

            /**
             * @brief formating the date and time
             * 
             * @param file 
             * @param ligne 
             * @param function 
             * @return std::string 
             */
            std::string formatOptionString(const char* file, int ligne, const char* function)
            {
                std::string output = m_format;

                // Obtention du temps actuel
                auto now = std::chrono::system_clock::now();
                // Conversion en timestamp
                auto timestamp = std::chrono::system_clock::to_time_t(now);
                // Obtention des milli secondes
                auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
                // Affichage de l'heure et des milli secondes
                std::time_t now_c = std::chrono::system_clock::to_time_t(now);

                std::string date = GetChrono(now_c, "%Y-%m-%d");
                std::string anne = GetChrono(now_c, "%Y");
                std::string mois = GetChrono(now_c, "%m");
                std::string jour = GetChrono(now_c, "%d");
                std::string temps = GetChrono(now_c, "%H:%M:%S") + ":" + std::to_string(milli);
                std::string heure = GetChrono(now_c, "%H");
                std::string minutes = GetChrono(now_c, "%M");
                std::string seconde = GetChrono(now_c, "%S");

                // Recuperation du nom du fichier sans le chemin
                std::string filename(file);
                size_t lastSlash = filename.find_last_of("\\/");
                if (std::string::npos != lastSlash)
                {
                    filename.erase(0, lastSlash + 1);
                }

                // Remplacement des options de format dans la cha�ne de format
                output = STRING_FORMATTER.Replace(output, "%F", filename);
                output = STRING_FORMATTER.Replace(output, "%L", std::to_string(ligne));
                output = STRING_FORMATTER.Replace(output, "%f", function);
                output = STRING_FORMATTER.Replace(output, "%D", date);
                output = STRING_FORMATTER.Replace(output, "%Y", anne);
                output = STRING_FORMATTER.Replace(output, "%m", mois);
                output = STRING_FORMATTER.Replace(output, "%d", jour);
                output = STRING_FORMATTER.Replace(output, "%X", temps);
                output = STRING_FORMATTER.Replace(output, "%H", heure);
                output = STRING_FORMATTER.Replace(output, "%S", minutes);
                output = STRING_FORMATTER.Replace(output, "%M", seconde);
                output = STRING_FORMATTER.Replace(output, "%P", std::to_string(milli));
                output = STRING_FORMATTER.Replace(output, "%N", m_name);

                return output;
            }
    }; 
} // namespace nkentsuu


#endif /* __LOGGER_H_HEADER__ */
