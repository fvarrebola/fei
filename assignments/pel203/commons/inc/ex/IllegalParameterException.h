#pragma once

#ifndef _ILLEGALPARAMETEREXCEPTION_H_
#define _ILLEGALPARAMETEREXCEPTION_H_

#include <exception>

namespace pel203 {

	namespace commons {

		/**
		 * Excecao que representa um parametro ilegal.
		 */
		class IllegalParameterException : public std::exception {
		public:
			/**
			 * Mensagem da excecao.
			 */
			virtual const char* what() const throw() {
			    return "Parametro ilegal";
			}

		}; /* class IllegalParameterException */

	} /* namespace commons */

} /* namespace pel203 */

#endif /* _ILLEGALPARAMETEREXCEPTION_H_ */
