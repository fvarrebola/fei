#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <stdexcept>
#include <string>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa uma fun��o matem�tica.<br />
		 *
		 * @author arrebola
		 */
		class Function {

		public:
			/**
			 * Construtor padr�o.<br />
			 */
			Function() {
			};

			/**
			 * Avalia a fun��o considerando os par�metros informados.<br />
			 *
			 * @param x 
			 *			o <code>double</code> que representa o x
			 * @param y 
			 *			o <code>double</code> que representa o y
			 * @param z 
			 *			o <code>double</code> que representa o z
			 *
			 * @return o <code>double</code> que representa o resultado da avalia��o
			 */
			virtual double evaluate(double x, double y = 0.0f, double z = 0.0f) { 
				throw new std::exception(); 
			};

			/**
			 * Avalia a integra��o <quote>precisa</quote> da fun��o considerando os par�metros informados.<br />
			 *
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integra��o
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integra��o
			 *
			 * @return o <code>double</code> que representa o resultado da avalia��o
			 */
			virtual double evaluatePreciseIntegration(double a = -1, double b = -1) { 
				throw new std::exception(); 
			};
			
			/**
			 * Retorna uma representa��o da fun��o.<br />
			 *
			 * @return o <code>std::string</code> que representa a fun��o
			 */
			virtual std::string toString() { 
				throw new std::exception(); 
			};

		}; /* class Function */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __FUNCTION_H__ */
