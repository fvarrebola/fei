#pragma once

#ifndef _PRISM_H_
#define _PRISM_H_

#include <inc/Utils.h>

namespace pel216 {

	namespace week2 {

		class Prism {
		private:
		public:
			/**
			 * Construtor.
			 */
			Prism();


			/**
			 * Destrutor.
			 */
			virtual ~Prism();


			/**
			 * Retorna a representacao da classe.
			 *
			 * @return o <code>std::string</code> que representa a classe
			 */
			std::string pel216::week2::Prism::toString() {

				std::string stringRep;
				stringRep.resize(MAX_PATH * 2);
				//sprintf_s((char*)stringRep.c_str(), MAX_PATH * 2, "(%d, %d, %d)", this->x, this->y, this->z);
				return stringRep;

			}

		}; /* class Prism */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _PRISM_H_ */
