#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa uma fun��o matem�tica.
		 *
		 * @author arrebola
		 */
		class Function {

		public:
			/**
			 * Construtor padr�o.
			 */
			Function() {
			};

			/**
			 * Avalia a fun��o considerando os par�metros informados.
			 *
			 * @param x 
			 *			o <code>double</code> que representa o x
			 *
			 * @return o <code>double</code> que representa o resultado da avalia��o
			 */
			virtual double evaluate(double x) { 
				throw new _exception(); 
			};
			
			/**
			 * Avalia a integra��o <quote>precisa</quote> da fun��o considerando os par�metros informados.
			 *
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integra��o
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integra��o
			 *
			 * @return o <code>double</code> que representa o resultado da avalia��o
			 */
			virtual double evaluatePreciseIntegration(double a = -1, double b = -1) { 
				throw new _exception(); 
			};
			
			/**
			 * Retorna uma representa��o da fun��o.
			 *
			 * @return o <code>std::string</code> que representa a fun��o
			 */
			virtual std::string toString() { 
				throw new _exception(); 
			};

		}; /* class Function */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __FUNCTION_H__ */
