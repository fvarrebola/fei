#pragma once

#ifndef __INTEGRATION_RULE_H__
#define __INTEGRATION_RULE_H__

#include <inc/Utils.h>
#include <inc/Function.h>

#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa um método de integração numérica.<br />
		 *
		 * @author arrebola
		 */
		class IntegrationRule {

		private:
			double absoluteError;
			double relativeError;

		public:
			/**
			 * Construtor padrão.<br />
			 */
			IntegrationRule() {
				this->absoluteError = 0.0f;
				this->relativeError = 0.0f;
			};

			/**
			 * Executa o método de integração numérica.<br />
			 *
			 * @param function
			 *				o @link{Function} que representa a função a ser integrada
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integração
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integração
			 * @param intervals 
			 *				o <code>double</code> que indica a quantidade de intervalos
			 *
			 * @return o <code>double</code> que representa o valor resultante da integração numérica
			 */
			virtual double doEvaluate(Function *function, double a, double b, double intervals = -1.0f) {
				throw new std::exception(); 
			};

			/**
			 * Executa o método de integração numérica.<br />
			 *
			 * @param function
			 *				o @link{Function} que representa a função a ser integrada
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integração
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integração
			 * @param intervals 
			 *				o <code>double</code> que indica a quantidade de intervalos
			 *
			 * @return o <code>double</code> que representa o valor resultante da integração numérica
			 */
			double evaluate(Function *function, double a, double b, double intervals = -1.0f) {

				if (Utils::isInvalidHandle(function)) {
					throw new IllegalParameterException();
				}

				this->absoluteError = 0.0f;
				this->relativeError = 0.0f;

				// calcula o valor preciso da integração numérica
				double preciseValue = function->evaluatePreciseIntegration(a, b);

				// calcula o resultado aproximado da integração numérica
				double result = doEvaluate(function, a, b, intervals); 

				// calcula o erro absoluto
				this->absoluteError = std::abs(preciseValue - result);

				// calcula o erro relativo
				this->relativeError = (this->absoluteError / std::abs(preciseValue));

				return result;

			};

			/**
			 * Retorna o erro absoluto da integração numérica.<br />
			 *
			 * @return o <code>double</code> que representa o valor de erro absoluto da integração numérica
			 */
			double getAbsoluteError() {
				return this->absoluteError;
			};

			/**
			 * Retorna o erro relativo (em %) da integração numérica.<br />
			 *
			 * @return o <code>double</code> que representa o valor de erro relativo (em %) da integração numérica
			 */
			double getRelativeError() {
				return this->relativeError;
			};

			/**
			 * Retorna uma representação do método de integração.
			 *
			 * @return o <code>std::string</code> que representa o método de integração
			 */
			virtual std::string toString() { 
				throw new std::exception(); 
			};


		}; /* class IntegrationRule */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __INTEGRATION_RULE_H__ */
