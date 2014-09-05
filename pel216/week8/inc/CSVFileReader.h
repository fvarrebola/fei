#pragma once

#ifndef __CSV_FILE_READER_H__
#define __CSV_FILE_READER_H__

#include <fstream>
#include <vector>
#include <list>

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/BookAttendGrade.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week8 {

		/**
		 * Leitor de arquivos.<br />
		 *
		 * @author arrebola
		 */
		class CSVFileReader {

		private:
			static std::vector<std::string> tokenize(const char *str, char delim = '\t') {
    
				std::vector<std::string> result;

				do {
					const char *begin = str;
					while(*str != delim && *str) {
						str++;
					}
					result.push_back(std::string(begin, str));
				} while (0 != *str++);

				return result;

			};

			static int toInt(std::vector<std::string> data, size_t position) {
				return (position < data.size()) ? atoi(data.at(position).c_str()) : -1;
			};

		public:
			static std::list<BookAttendGrade> load(const char *file) {

				if (Utils::isInvalidHandle((char*)file)) {
					throw new IllegalParameterException();
				}

				std::list<BookAttendGrade> dataList;

				std::ifstream ifstream(file);
				
				// leio o stream enquanto houver caracteres válidos
				while (ifstream.good()) { 

					std::string line;
					std::getline(ifstream, line);

					// a delimitação por tab é feita
					std::vector<std::string> tokens = tokenize(line.c_str());
					if (tokens.size() != 3) {
						continue;
					}

					// um novo elemento é adicionado na lista
					dataList.push_back(
						BookAttendGrade(toInt(tokens, 0), toInt(tokens, 1), toInt(tokens, 2)));

				}

				return dataList;

			};

		}; /* class CSVFileReader */

	} /* namespace week8 */

} /* namespace pel216 */

#endif /* __CSV_FILE_READER_H__ */
