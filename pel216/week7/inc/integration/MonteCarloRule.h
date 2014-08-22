#pragma once

#ifndef __MONTE_CARLO_RULE_H__
#define __MONTE_CARLO_RULE_H__

#include <chrono>
#include <random>

#include <inc/Utils.h>
#include <inc/Function.h>
#include <inc/IntegrationRule.h>

#include <inc/ex/IllegalParameterException.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week7 {

		static const size_t MAX_SAMPLES = 100000000;
		static const size_t MIN_STEP_COUNT = 2;

		/**
		 * Classe que representa um método de integração numérica.<br />
		 *
		 * @author arrebola
		 */
		class MonteCarloRule : public pel216::week6::IntegrationRule {

		private:
			bool debug;

		public:
			/**
			 * Construtor padrão.<br />
			 *
			 * @param debug
			 *				indica se os valores considerados na integração numérica devem ser salvos em arquivo
			 */
			MonteCarloRule(bool debug = false) : IntegrationRule() {
				this->debug = debug;
			};

			/**
			 * @see pel216::week6::IntegrationRule#evaluate()
			 */
			virtual double doEvaluate(pel216::week6::Function *function, double a, double b, size_t intervals = -1) {

				if (Utils::isInvalidHandle(function)) {
					throw new IllegalParameterException();
				}

				// cria o gerador aleatório
				std::random_device generator;
				std::uniform_real_distribution<double> distribution(a, b);

				// calcula o resultado aproximado da integração numérica
				double sum = 0.0f;
				for (size_t idx = 0; idx < intervals; idx++) {
					
					register double random = distribution(generator);
					register double value = function->evaluate(random);
					
					if (this->debug) {
						Logger::logToFile("%.5f, %.5f\n", random, value);
					}
					
					sum += value;

				}

				return ((b - a) * (sum / intervals));

			};

			/**
			 * @see pel216::week6::IntegrationRule#toString()
			 */
			virtual std::string toString() { 
				return "Monte Carlo";
			};

		}; /* class MonteCarloRule */

	} /* namespace week7 */

} /* namespace pel216 */

#endif /* __MONTE_CARLO_RULE_H__ */
