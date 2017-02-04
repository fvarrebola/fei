#pragma once

#ifndef __RECTANGLE_METHOD_H__
#define __RECTANGLE_METHOD_H__

#include <inc/Function.h>
#include <inc/IntegrationRule.h>

#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa o m�todo de integra��o baseado na regra do ret�ngulo.<br />
		 *
		 * @author arrebola
		 */
		class RectangleRule : public IntegrationRule  {

		protected:

		public:
			/**
			 * Construtor padr�o.<br />
			 */
			RectangleRule() : IntegrationRule() {
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
					double a_plus_b_div_2 = (a_prime + b_prime) / 2;
					result += (b_prime - a_prime) * function->evaluate(a_plus_b_div_2);
					a_prime += alpha;
					b_prime += alpha;
				}

				return result;

			};

			/**
			 * @see pel216::week6::IntegrationRule#toString()
			 */
			virtual std::string toString() {
				return "Regra do retangulo: (b - a) * (f(a + b)/2)";
			};

		}; /* class RectangleRule */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __RECTANGLE_METHOD_H__ */
