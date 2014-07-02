#pragma once

#ifndef _UNSUPPORTEDOPERATIONEXCEPTION_H_
#define _UNSUPPORTEDOPERATIONEXCEPTION_H_

#include <exception>

namespace pel216 {

	namespace commons {

		/**
		 * Excecao que representa uma operacao nao suportada.
		 */
		class UnsupportedOperationException : public std::exception {

			/**
			 * Mensagem da excecao.
			 */
			virtual const char* what() const throw() {
			    return "Operacao nao suportada";
			}

		}; /* class UnsupportedOperationException */

	} /* namespace commons */

} /* namespace pel216 */

#endif /* _UNSUPPORTEDOPERATIONEXCEPTION_H_ */
