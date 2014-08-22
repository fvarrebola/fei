#pragma once

#ifndef __INTEGRATION_RULE_H__
#define __INTEGRATION_RULE_H__

#include <inc/Utils.h>
#include <inc/Function.h>

#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa um m�todo de integra��o num�rica.<br />
		 *
		 * @author arrebola
		 */
		class IntegrationRule {

		private:
			double absoluteError;
			double relativeError;

		public:
			/**
			 * Construtor padr�o.<br />
			 */
			IntegrationRule() {
				this->absoluteError = 0.0f;
				this->relativeError = 0.0f;
			};

			/**
			 * Executa o m�todo de integra��o num�rica.<br />
			 *
			 * @param function
			 *				o @link{Function} que representa a fun��o a ser integrada
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integra��o
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integra��o
			 * @param intervals 
			 *				o <code>double</code> que indica a quantidade de intervalos
			 *
			 * @return o <code>double</code> que representa o valor resultante da integra��o num�rica
			 */
			virtual double doEvaluate(Function *function, double a, double b, double intervals = -1.0f) {
				throw new std::exception(); 
			};

			/**
			 * Executa o m�todo de integra��o num�rica.<br />
			 *
			 * @param function
			 *				o @link{Function} que representa a fun��o a ser integrada
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integra��o
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integra��o
			 * @param intervals 
			 *				o <code>double</code> que indica a quantidade de intervalos
			 *
			 * @return o <code>double</code> que representa o valor resultante da integra��o num�rica
			 */
			double evaluate(Function *function, double a, double b, double intervals = -1.0f) {

				if (Utils::isInvalidHandle(function)) {
					throw new IllegalParameterException();
				}

				this->absoluteError = 0.0f;
				this->relativeError = 0.0f;

				// calcula o valor preciso da integra��o num�rica
				double preciseValue = function->evaluatePreciseIntegration(a, b);

				// calcula o resultado aproximado da integra��o num�rica
				double result = doEvaluate(function, a, b, intervals); 

				// calcula o erro absoluto
				this->absoluteError = std::abs(preciseValue - result);

				// calcula o erro relativo
				this->relativeError = (this->absoluteError / std::abs(preciseValue));

				return result;

			};

			/**
			 * Retorna o erro absoluto da integra��o num�rica.<br />
			 *
			 * @return o <code>double</code> que representa o valor de erro absoluto da integra��o num�rica
			 */
			double getAbsoluteError() {
				return this->absoluteError;
			};

			/**
			 * Retorna o erro relativo (em %) da integra��o num�rica.<br />
			 *
			 * @return o <code>double</code> que representa o valor de erro relativo (em %) da integra��o num�rica
			 */
			double getRelativeError() {
				return this->relativeError;
			};

			/**
			 * Retorna uma representa��o do m�todo de integra��o.
			 *
			 * @return o <code>std::string</code> que representa o m�todo de integra��o
			 */
			virtual std::string toString() { 
				throw new std::exception(); 
			};


		}; /* class IntegrationRule */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __INTEGRATION_RULE_H__ */
