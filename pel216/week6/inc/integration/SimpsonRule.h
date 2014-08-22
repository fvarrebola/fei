#pragma once

#ifndef __SIMPSON_METHOD_H__
#define __SIMPSON_METHOD_H__

#include <inc/Function.h>
#include <inc/IntegrationRule.h>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa o método de integração baseado na regra de Simpson.<br />
		 *
		 * @author arrebola
		 */
		class SimpsonRule : public IntegrationRule {

		public:
			/**
			 * Construtor padrão.<br />
			 */
			SimpsonRule() : IntegrationRule() {
			};

			/**
			 * @see pel216::week6::IntegrationRule#evaluate()
			 */
			virtual double doEvaluate(Function *function, double a, double b, size_t intervals) {

				double result = 0.0f;

				double alpha = (b - a) / intervals;

				double a_prime = a;
				double b_prime = a_prime + alpha;
				for (size_t idx = 0; idx < intervals; idx++) {
					double a_plus_b_div_2 = (a_prime + b_prime) / 2;
					result += ((b_prime - a_prime) / 6) * (function->evaluate(a_prime) + 4 * function->evaluate(a_plus_b_div_2) + function->evaluate(b_prime));
					a_prime += alpha;
					b_prime += alpha;
				}


				return result;

			};

			/**
			 * @see pel216::week6::IntegrationRule#toString()
			 */
			virtual std::string toString() {
				return "Regra de Simpson: (b - a)/6 * [f(a) + 4*f((a + b)/2) + f(b)]";
			};

		}; /* class SimpsonRule */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __SIMPSON_METHOD_H__ */
