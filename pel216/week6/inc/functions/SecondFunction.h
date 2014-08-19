#pragma once

#ifndef __SECOND_FUNCTION_H__
#define __SECOND_FUNCTION_H__

#include <cmath>

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/Function.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa a função f(x) = sqrt(1 - x^2).<br />
		 * A primeira derivada é df/dx = - (x  / sqrt(1 - x^2)).<br />
		 * A segunda derivada é df/dx = - (x  / sqrt(1 - x^2)) - (x^2 / (1 - x^2)^3/2).
		 *
		 * @author arrebola
		 */
		class SecondFunction : public Function {

		private:

		public:
			/**
			 * Construtor.
			 */
			SecondFunction() {
			};

			/**
			 * @see pel216::week6::Function#evaluate()
			 */
			virtual double evaluate(double x) {
				return std::sqrt(1 - std::pow(x, 2.0f));
			};

			/**
			 * @see pel216::week6::Function#evaluatePreciseIntegration()
			 */
			virtual double evaluatePreciseIntegration(double a = -1, double b = -1) {
				return (0.5f * (evaluate(b) * b + std::asin(b))) - (0.5f * (evaluate(a) * a + std::asin(a)));
			};

			/**
			 * @see pel216::week6::Function#toString()
			 */
			virtual std::string toString() {
				return "f(x) = sqrt(1 - x^2)";
			};

		}; /* class SecondFunction */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __SECOND_FUNCTION_H__ */
