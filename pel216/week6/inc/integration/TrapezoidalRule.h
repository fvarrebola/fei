#pragma once

#ifndef __TRAPEZOIDAL_METHOD_H__
#define __TRAPEZOIDAL_METHOD_H__

#include <inc/Function.h>
#include <inc/IntegrationRule.h>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa o método de integração baseado na regra do trapezóide.<br />
		 *
		 * @author arrebola
		 */
		class TrapezoidalRule : public IntegrationRule {

		protected:

		public:
			/**
			 * Construtor padrão.<br />
			 */
			TrapezoidalRule() : IntegrationRule() {
			};

			/**
			 * @see pel216::week6::IntegrationRule#evaluate()
			 */
			virtual double doEvaluate(Function *function, double a, double b, double intervals) {

				double result = 0.0f;

				double alpha = (b - a) / intervals;

				double a_prime = a;
				double b_prime = a_prime + alpha;
				for (double idx = 0.0f; idx < intervals; idx++) {
					result += alpha * ((function->evaluate(a_prime) + function->evaluate(b_prime)) / 2.0f);
					a_prime += alpha;
					b_prime += alpha;
				}

				return result;

			};

			/**
			 * @see pel216::week6::IntegrationRule#toString()
			 */
			virtual std::string toString() {
				return "Regra do trapezoide: (b - a) * ((f(a) + f(b))/2)";
			};

		}; /* class TrapezoidalRule */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __TRAPEZOIDAL_METHOD_H__ */
