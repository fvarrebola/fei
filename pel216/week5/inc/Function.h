#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>

namespace pel216 {

	namespace week5 {

		/**
		 * Classe que representa uma fun��o matem�tica.
		 *
		 * @author arrebola
		 */
		class Function {

		protected:
			size_t dimensionsCount;
			std::vector<double> initialValue;

		public:
			/**
			 * Construtor padr�o.
			 */
			Function() {
			};

			/**
			 * Retorna a quantidade de dimens�es que a fun��o possui.
			 *
			 * @return o <code>size_t</code> que representa a quantiodade de dimens�es
			 */
			size_t getDimesionsCount() {
				return this->dimensionsCount;
			};

			/**
			 * Obt�m o valor inicial.
			 *
			 * @return o <code>std::vector<double></code> que representa o valor inicial
			 */
			std::vector<double> getInitialValue() {
				return this->initialValue;
			};

			/**
			 * Avalia a fun��o considerando os par�metros informados.
			 *
			 * @param params 
			 *			o <code>std::vector<double></code> que representa os par�metros da fun��o
			 *
			 * @return o <code>std::vector<double></code> que representa o resultados da avalia��o
			 */
			virtual std::vector<double> evaluate(std::vector<double> params) { 
				throw new _exception(); 
			};
			
			/**
			 * Avalia a primeira derivada em x fun��o considerando os par�metros informados.
			 *
			 * @param params 
			 *			o <code>std::vector<double></code> que representa os par�metros da fun��o
			 * 
			 * @return o <code>double</code> que representa o resultados da avalia��o
			 */
			virtual double derivativeOfX(std::vector<double> params) { 
				throw new _exception(); 
			};
			
			/**
			 * Avalia a primeira derivada em y fun��o considerando os par�metros informados.
			 *
			 * @param params 
			 *			o <code>std::vector<double></code> que representa os par�metros da fun��o
			 * 
			 * @return o <code>double</code> que representa o resultados da avalia��o
			 */
			virtual double derivativeOfY(std::vector<double> params) { 
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

	} /* namespace week5 */

} /* namespace pel216 */

#endif /* __FUNCTION_H__ */
