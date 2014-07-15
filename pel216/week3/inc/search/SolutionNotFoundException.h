#pragma once

#ifndef __SOLUTIONNOTFOUNDEXCEPTION_H__
#define __SOLUTIONNOTFOUNDEXCEPTION_H__

#include <exception>

namespace pel216 {

	namespace week3 {

		/**
		 * Exce��o que indica a aus�ncia de uma solu��o.
		 */
		class SolutionNotFoundException : public std::exception {
		public:
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
