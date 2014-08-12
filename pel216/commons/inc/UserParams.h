#pragma once

#ifndef __USERPARAMS_H__
#define __USERPARAMS_H__

#include <string>
#include <vector>
#include <algorithm>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace commons {

		/**
		 * Classe de obtenção de parâmetros do usuário.
		 *
		 * @author arrebola
		 */
		class UserParams {

		public:
			/**
			 * Obtém um <code>bool</code> como parâmetro de entrada.
			 *
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 */
			static bool getBoolParam(std::string inputMsg) {

				bool boolParam = false;

				if (pel216::commons::Utils::isInvalidHandle(&inputMsg)) {
					throw new pel216::commons::IllegalParameterException();
				}

				std::string inputString;

				pel216::commons::Logger::log("%s [Y/N]: ", inputMsg.c_str());
				std::cin >> inputString;
				boolParam = (inputString.compare("Y") == 0);

				return boolParam;

			};

			/**
			 * Obtém um int como parâmetro de entrada.
			 *
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 */
			static int getIntParam(std::string inputMsg = NULL) {

				int intParam = -1;

				if (pel216::commons::Utils::isValidHandle(&inputMsg)) {
					pel216::commons::Logger::log("%s: ", inputMsg.c_str());
				} else {
					pel216::commons::Logger::log("Informe um numero: ");
				}

				std::cin >> intParam;

				return intParam;

			};

			/**
			 * Obtém um vetor de int como parâmetro de entrada.
			 *
			 * @param maxVectorSize
			 *				o <code>size_t</code> que representa o tamanho máximo do vetor
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 */
			static std::vector<int> getIntVectorParam(size_t maxVectorSize, std::string inputMsg = NULL) {

				std::vector<int> intVector;

				if (maxVectorSize < 1) {
					throw new pel216::commons::IllegalParameterException();
				}

				if (pel216::commons::Utils::isValidHandle(&inputMsg)) {
					pel216::commons::Logger::log("%s: ", inputMsg.c_str());
				} else {
					pel216::commons::Logger::log("Informe a lista de numeros (separados por virgula): ");
				}

				std::string inputString;
				std::cin >> inputString;

				// remove os espaços
				std::remove(inputString.begin(), inputString.end(), ' '); 

				size_t start = 0;
				size_t end = 0;
				while ((end != std::string::npos) && (intVector.size() != maxVectorSize)) {
					
					end = inputString.find(",", start);
					std::string valueAsStr = inputString.substr(
						start, (end == std::string::npos) ? std::string::npos : end - start);
					intVector.push_back(atoi(valueAsStr.c_str()));
					start = (( end > (std::string::npos - 1) ) ?  std::string::npos  :  end + 1);
				}

				return intVector;

			};

			/**
			 * Obtém um <code>double</code> como parâmetro de entrada.
			 *
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 */
			static double getDoubleParam(std::string inputMsg = NULL) {

				double intParam = 0.0f;

				if (pel216::commons::Utils::isValidHandle(&inputMsg)) {
					pel216::commons::Logger::log("%s: ", inputMsg.c_str());
				} else {
					pel216::commons::Logger::log("Informe um numero: ");
				}

				std::cin >> intParam;

				return intParam;

			};

		}; /* class UserParams */

	} /* namespace commons */

} /* namespace pel216 */

#endif /* __USERPARAMS_H__ */
