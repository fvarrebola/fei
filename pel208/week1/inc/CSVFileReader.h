#pragma once

#ifndef __CSV_FILE_READER_H__
#define __CSV_FILE_READER_H__

#include <fstream>
#include <vector>
#include <list>

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/BookAttendGrade.h>
#include <inc/BoilingPointPressure.h>

using namespace pel216::commons;

namespace pel208 {

	namespace week1 {

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

			/**
			 * Converte em <code>int</code> um elemento em um vetor <code>std::string</code>.
			 *
			 * @param data
			 *				o <code>std::vector</code> de <code>std::string</code> que representa o vetor de dados
			 * @param position
			 *				o <code>size_t</code> que representa a posi��o do vetor
			 *
			 * @return o <code>int</code> que representa o valor convertido
			 */
			static int toInt(std::vector<std::string> data, size_t position) {
				return (position < data.size()) ? atoi(data.at(position).c_str()) : -1;
			};

			/**
			 * Converte em <code>double</code> um elemento em um vetor <code>std::string</code>.
			 *
			 * @param data
			 *				o <code>std::vector</code> de <code>std::string</code> que representa o vetor de dados
			 * @param position
			 *				o <code>size_t</code> que representa a posi��o do vetor
			 *
			 * @return o <code>double</code> que representa o valor convertido
			 */
			static double toDouble(std::vector<std::string> data, size_t position) {
				return (position < data.size()) ? atof(data.at(position).c_str()) : -1.0f;
			};

		public:
			/**
			 * Carrega os dados contidos no arquivo como um <code>std::list</code> de BookAttendGrade.
			 *
			 * @param file
			 *				o <code>char *</code> que representa o nome do arquivo
			 *
			 * @return o <code>std::list</code> de BookAttendGrade que representa a lista de dados
			 */
			static std::list<BookAttendGrade> loadAsBookAttendGrade(const char *file) {

				if (Utils::isInvalidHandle((char*)file)) {
					throw new IllegalParameterException();
				}

				std::list<BookAttendGrade> dataList;

				std::ifstream ifstream(file);
				
				// leio o stream enquanto houver caracteres v�lidos
				while (ifstream.good()) { 

					std::string line;
					std::getline(ifstream, line);

					// a delimita��o por tab � feita
					std::vector<std::string> tokens = tokenize(line.c_str());
					if (tokens.size() != 3) {
						continue;
					}

					// um novo elemento � adicionado na lista
					dataList.push_back(
						BookAttendGrade(toInt(tokens, 0), toInt(tokens, 1), toInt(tokens, 2)));

				}

				return dataList;

			};

			/**
			 * Carrega os dados contidos no arquivo como um <code>std::list</code> de BoiolingPointPressure.
			 *
			 * @param file
			 *				o <code>char *</code> que representa o nome do arquivo
			 *
			 * @return o <code>std::list</code> de BoiolingPointPressure que representa a lista de dados
			 */
			static std::list<BoiolingPointPressure> loadAsBoiolingPointPressure(const char *file) {

				if (Utils::isInvalidHandle((char*)file)) {
					throw new IllegalParameterException();
				}

				std::list<BoiolingPointPressure> dataList;

				std::ifstream ifstream(file);
				
				// leio o stream enquanto houver caracteres v�lidos
				while (ifstream.good()) { 

					std::string line;
					std::getline(ifstream, line);

					// a delimita��o por tab � feita
					std::vector<std::string> tokens = tokenize(line.c_str());
					if (tokens.size() != 3) {
						continue;
					}

					// um novo elemento � adicionado na lista
					dataList.push_back(BoiolingPointPressure(toDouble(tokens, 2), toDouble(tokens, 1)));

				}

				return dataList;

			};

		}; /* class CSVFileReader */

	} /* namespace week1 */

} /* namespace pel208 */

#endif /* __CSV_FILE_READER_H__ */
