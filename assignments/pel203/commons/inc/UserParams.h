#pragma once

#ifndef __USERPARAMS_H__
#define __USERPARAMS_H__

#include <string>
#include <vector>
#include <algorithm>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/ex/IllegalParameterException.h>

namespace pel203 {

	namespace commons {

		/**
		 * Classe de obten��o de par�metros do usu�rio.
		 *
		 * @author arrebola
		 */
		class UserParams {

		public:
			/**
			 * Obt�m um <code>std::string</code> como par�metro de entrada.<br />
			 *
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 *
			 * @return o <code>std::string</code> informado pelo usu�rio
			 */
			PUBLIC static std::string getStringParam(IN std::string inputMsg) {

				if (Utils::isInvalidHandle(&inputMsg)) {
					throw new IllegalParameterException();
				}

				std::string inputString;

				Logger::log("%s: ", inputMsg.c_str());
				std::cin >> inputString;

				return inputString;

			};
			
			/**
			 * Obt�m um <code>bool</code> como par�metro de entrada.
			 *
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 */
			PUBLIC static bool getBoolParam(IN std::string inputMsg) {

				bool boolParam = false;

				if (Utils::isInvalidHandle(&inputMsg)) {
					throw new IllegalParameterException();
				}

				std::string inputString;

				Logger::log("%s [Y/N]: ", inputMsg.c_str());
				std::cin >> inputString;
				boolParam = (inputString.compare("Y") == 0);

				return boolParam;

			};

			/**
			 * Obt�m um int como par�metro de entrada.
			 *
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 */
			PUBLIC static int getIntParam(IN std::string inputMsg = NULL) {

				int intParam = -1;

				if (Utils::isValidHandle(&inputMsg)) {
					Logger::log("%s: ", inputMsg.c_str());
				} else {
					Logger::log("Informe um numero: ");
				}

				std::cin >> intParam;

				return intParam;

			};

			/**
			 * Obt�m um vetor de int como par�metro de entrada.
			 *
			 * @param maxVectorSize
			 *				o <code>size_t</code> que representa o tamanho m�ximo do vetor
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 */
			PUBLIC static std::vector<int> getIntVectorParam(IN size_t maxVectorSize, IN std::string inputMsg = NULL) {

				std::vector<int> intVector;

				if (maxVectorSize < 1) {
					throw new IllegalParameterException();
				}

				if (Utils::isValidHandle(&inputMsg)) {
					Logger::log("%s: ", inputMsg.c_str());
				} else {
					Logger::log("Informe a lista de numeros (separados por virgula): ");
				}

				std::string inputString;
				std::cin >> inputString;

				// remove os espa�os
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
			 * Obt�m um <code>double</code> como par�metro de entrada.
			 *
			 * @param inputMsg
			 *				o <code>std::string</code> que representa a mensagem exibida para o usuario
			 */
			PUBLIC static double getDoubleParam(IN std::string inputMsg = NULL) {

				double intParam = 0.0f;

				if (Utils::isValidHandle(&inputMsg)) {
					Logger::log("%s: ", inputMsg.c_str());
				} else {
					Logger::log("Informe um numero: ");
				}

				std::cin >> intParam;

				return intParam;

			};

		}; /* class UserParams */

	} /* namespace commons */

} /* namespace pel203 */

#endif /* __USERPARAMS_H__ */
