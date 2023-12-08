#ifndef __SFORMAT_H_HEADER__
#define __SFORMAT_H_HEADER__

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Platform/Platform.h"

namespace nkentsuu {
	class NKENTSUU_API StringFormatter {
		public:

		static StringFormatter& Instance() {
			static StringFormatter string_formatter;
			return string_formatter;
		}
		/**
		* @brief Get the Content of delimiter : {} > no content, {1} > content is 1 etc. and Get the position of the { and }
		*
		* @param debut
		* @param fin
		* @param index
		* @param content
		* @return int
		*/
		int GetContent(size_t& debut, size_t& fin, int& index, const std::string& content) {
			std::string output = content;

			debut = output.find("{", debut);
			fin = output.find("}", debut);

			if (debut == std::string::npos || fin == std::string::npos)
				return (-1);

			std::string strIndex = output.substr(debut + 1, fin - debut - 1);
			try {
				index = std::stoi(strIndex);
				if (index < 0)
					return (1);
			} catch (const std::invalid_argument&) {
				if (debut + 1 == fin) {
					return (2);
				} else {
					return (3);
				}
			}
			return (0);
		}

		/**
		 * @brief Use GetContent to format entirely string with the args specified
		 *
		 * @tparam Args
		 * @param format
		 * @param args
		 * @return std::string
		 */
		template<typename... Args>
		std::string Format(const std::string& format, Args&&... args) {
			// Initialisation de la chaine de sortie
			std::string output = format;
			// Nombre d'arguments passes
			std::size_t argsCount = sizeof...(args);
			if (argsCount <= 0) return format;
			// Position de l'argument courant dans la chaine de format
			std::size_t argsIndex = 0;
			// liste des arguments deja utilises
			std::vector<std::string> used_args = GetArgs(args...);

			size_t debut = 0;
			size_t fin;
			int index;
			int sortir = 0;

			while ((sortir = GetContent(debut, fin, index, output)) != -1) {
				if (sortir == 0 || sortir == 2) {
					if (sortir == 2) {
						index = argsIndex;
						argsIndex++;
					}

					if (index >= 0 && index < used_args.size()) {
						std::string nouvelleValeur = used_args[index];
						output.replace(debut, fin - debut + 1, nouvelleValeur);
					} else {
						debut++;
					}
				}
			}
			return (output);
		}

		/**
		 * @brief Get the Args object
		 *
		 * @tparam Args
		 * @param args
		 * @return std::vector<std::string>
		 */
		template <typename... Args>
		std::vector<std::string> GetArgs(Args&&... args) {
			std::vector<std::string> result;
			(GetArgsHelper(result, std::forward<Args>(args)), ...);
			return result;
		}

		/**
		 * @brief Get the Args Helper object
		 *
		 * @tparam T
		 * @param result
		 * @param arg
		 */
		template <typename T>
		void GetArgsHelper(std::vector<std::string>& result, T&& arg) {
			std::stringstream ss;
			ss << arg;
			result.push_back(ss.str());
		}

		/**
		 * @brief Replace valeur to nouvelleValeur in format
		 *
		 * @param format
		 * @param valeur
		 * @param nouvelleValeur
		 * @return std::string
		 */
		std::string Replace(const std::string& format, const std::string& valeur, const std::string& nouvelleValeur) {
			std::string output = format;
			size_t pos = output.find(valeur);
			while (pos != std::string::npos) {
				output.replace(pos, valeur.length(), nouvelleValeur);
				pos = output.find(valeur, pos + nouvelleValeur.length());
			}
			return output;
		}

		private:
			StringFormatter(){}
	};

	#define STRING_FORMATTER	StringFormatter::Instance()
}

#endif /* __SFORMAT_H_HEADER__ */
