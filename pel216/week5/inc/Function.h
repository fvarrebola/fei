#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>

#include <inc/Point.h>

namespace pel216 {

	namespace week5 {

		/**
		 * Classe que representa uma função matemática.
		 *
		 * @author arrebola
		 */
		class Function {

		protected:
			size_t dimensionsCount;
			std::vector<double> initialValue;

		public:
			/**
			 * Construtor padrão.
			 */
			Function() {
			};

			/**
			 * Retorna a quantidade de dimensões que a função possui.
			 *
			 * @return o <code>size_t</code> que representa a quantiodade de dimensões
			 */
			size_t getDimesionsCount() {
				return this->dimensionsCount;
			};

			/**
			 * Obtém o valor inicial.
			 *
			 * @return o <code>std::vector<double></code> que representa o valor inicial
			 */
			std::vector<double> getInitialValue() {
				return this->initialValue;
			};

			/**
			 * Avalia a função considerando os parâmetros informados.
			 *
			 * @param params 
			 *			o <code>std::vector<double></code> que representa os parâmetros da função
			 *
			 * @return o <code>std::vector<double></code> que representa o resultados da avaliação
			 */
			virtual std::vector<double> evaluate(std::vector<double> params) { 
				throw new _exception(); 
			};
			
			/**
			 * Avalia a primeira derivada em x função considerando os parâmetros informados.
			 *
			 * @param params 
			 *			o <code>std::vector<double></code> que representa os parâmetros da função
			 * 
			 * @return o <code>double</code> que representa o resultados da avaliação
			 */
			virtual double derivativeOfX(std::vector<double> params) { 
				throw new _exception(); 
			};
			
			/**
			 * Avalia a primeira derivada em y função considerando os parâmetros informados.
			 *
			 * @param params 
			 *			o <code>std::vector<double></code> que representa os parâmetros da função
			 * 
			 * @return o <code>double</code> que representa o resultados da avaliação
			 */
			virtual double derivativeOfY(std::vector<double> params) { 
				throw new _exception(); 
			};

			/**
			 * Retorna uma representação da função.
			 *
			 * @return o <code>std::string</code> que representa a função
			 */
			virtual std::string toString() { 
				throw new _exception(); 
			};

		}; /* class Function */

	} /* namespace week5 */

} /* namespace pel216 */

#endif /* __FUNCTION_H__ */
