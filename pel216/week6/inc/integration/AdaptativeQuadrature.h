#pragma once

#ifndef __ADAPTATIVE_QUADRATURE_H__
#define __ADAPTATIVE_QUADRATURE_H__

#include <string>

#include <inc/Utils.h>
#include <inc/Function.h>
#include <inc/IntegrationRule.h>
#include <inc/ex/IllegalParameterException.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa a integração numérica utilizando a quadratura adaptativa.<br />
		 *
		 * @author arrebola
		 */
		class AdaptativeQuadrature {

		private:
			double absoluteError;
			double relativeError;

			/**
			 * Calcula a integração numérica utilizando a quadratura adaptativa.<br />
			 * Esta é a uma aobrdagem básica na qual a estimativa inicial é calculada com um único intervalo e a precisão aceitável é de 10^-12.<br />
			 *
			 * @param rule
			 *				o @link{IntegrationRule} que representa a regra a ser utilizada
			 * @param function
			 *				o @link{Function} que representa a função a ser integrada
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integração
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integração
			 * @param tau
			 *				o <code>double</code> que representa a precisão de erro
			 *
			 * @return o <code>double</code> que representa o resultado da avaliação
			 */
			double doEvaluate(IntegrationRule *rule, Function *function, double a, double b, double tau = 0.000000000001f) {

				double a_prime = a;
				double b_prime = b;

				double S1 = 0.0f;
				double S2 = 0.0f;

				// enquanto a diferença absoluta entre as integrações da função no [a,b] e nos intervalos [a,m] e [m,b]
				// for inferior a tau, o algoritmo continua a executar
				do {
					
					register double m = (a_prime + b_prime) / 2;
					register double a_to_m_integral =  rule->evaluate(function, a_prime, m, ONE);
					register double m_to_b_integral =  rule->evaluate(function, m, b_prime, ONE);
					
					S1 = rule->evaluate(function, a_prime, b_prime, ONE);
					S2 = a_to_m_integral + m_to_b_integral;
					
					b_prime = m;

				} while (std::abs(S1 - S2) > tau);
				
				// calcula o valor preciso da integração numérica
				double preciseValue = function->evaluatePreciseIntegration(a, b);

				// após encontrar o menor b_prime, calculamos a quantidade de intervalos
				// e, em seguida, calcula o resultado aproximado da integração numérica
				size_t intervals = ((b_prime > 0.0f) ? ((size_t)((a + b) / b_prime)) : ONE);
				double result = rule->evaluate(function, a, b, intervals);

				// calcula o erro absoluto
				this->absoluteError = std::abs(preciseValue - result);

				// calcula o erro relativo
				this->relativeError = (this->absoluteError / std::abs(preciseValue));

				return result;

			};

		public:
			/**
			 * Construtor padrão.
			 */
			AdaptativeQuadrature() {
			};

			/**
			 * Realiza a integração numérica utilizando a quadratura adaptativa.
			 *
			 * @param rule
			 *				o @link{IntegrationRule} que representa a regra a ser utilizada
			 * @param function
			 *				o @link{Function} que representa a função a ser integrada
			 * @param a
			 *				o <code>double</code> que representa o valor do limite inferior da integração
			 * @param b
			 *				o <code>double</code> que representa o valor do limite superior da integração
			 * @param tau
			 *				o <code>double</code> que representa a precisão de erro
			 *
			 * @return o <code>double</code> que representa o resultado da avaliação
			 */
			double evaluate(IntegrationRule *rule, Function *function, double a, double b, double tau = 0.000000000001f) { 

				if (Utils::isInvalidHandle(rule) || Utils::isInvalidHandle(function)) {
					throw new IllegalParameterException();
				}

				return doEvaluate(rule, function, a, b, tau);

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

		}; /* class AdaptativeQuadrature */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __ADAPTATIVE_QUADRATURE_H__ */
