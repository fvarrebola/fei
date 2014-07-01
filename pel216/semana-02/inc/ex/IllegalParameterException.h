#pragma once

#ifndef _ILLEGALPARAMETEREXCEPTION_H_
#define _ILLEGALPARAMETEREXCEPTION_H_

#include <exception>

namespace pel216 {

	namespace week2 {

		/**
		 * Excecao que representa um parametro ilegal.
		 */
		class IllegalParameterException : public std::exception {

			/**
			 * Mensagem da excecao.
			 */
			virtual const char* what() const throw() {
			    return "Parametro ilegal";
			}

		}; /* class UnsuuportedOperationException */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _ILLEGALPARAMETEREXCEPTION_H_ */
