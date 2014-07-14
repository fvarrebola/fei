#pragma once

#ifndef __SOLUTIONNOTFOUNDEXCEPTION_H__
#define __SOLUTIONNOTFOUNDEXCEPTION_H__

#include <exception>

namespace pel216 {

	namespace week3 {

		/**
		 * Exceção que indica a ausência de uma solução.
		 */
		class SolutionNotFoundException : public std::exception {

			/**
			 * Mensagem da excecao.
			 */
			virtual const char* what() const throw() {
			    return "Solucao nao suportada";
			}

		}; /* class SolutionNotFoundException */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __SOLUTIONNOTFOUNDEXCEPTION_H__ */
