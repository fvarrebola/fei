#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa uma função matemática.<br />
		 *
		 * @author arrebola
		 */
		class Function {

		public:
			/**
			 * Construtor padrão.<br />
			 */
			Function() {
			};

			/**
			 * Avalia a função considerando os parâmetros informados.<br />
			 *
			 * @param x 
			 *			o <code>double</code> que representa o x
			 *
			 * @return o <code>double</code> que representa o resultado da avaliação
			 */
			virtual double evaluate(double x) { 
				throw new _exception(); 
			};
			
			/**
			 * Avalia a integração <quote>precisa</quote> da função considerando os parâmetros informados.<br />
			 *
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integração
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integração
			 *
			 * @return o <code>double</code> que representa o resultado da avaliação
			 */
			virtual double evaluatePreciseIntegration(double a = -1, double b = -1) { 
				throw new _exception(); 
			};
			
			/**
			 * Retorna uma representação da função.<br />
			 *
			 * @return o <code>std::string</code> que representa a função
			 */
			virtual std::string toString() { 
				throw new _exception(); 
			};

		}; /* class Function */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __FUNCTION_H__ */
