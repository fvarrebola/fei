#pragma once

#ifndef __THIRD_FUNCTION_WEEK7_H__
#define __THIRD_FUNCTION_WEEK7_H__

#include <cmath>

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/Function.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week7 {

		/**
		 * Classe que representa a função f(x) = sqrt(x + sqrt(x)).<br />
		 *
		 * @author arrebola
		 */
		class ThirdFunction : public pel216::week6::Function {

		private:
			/**
			 * Avalia a integral precisa da função, dada por (1/12 * ((sqrt(x + sqrt(x)) * (8*x + 2*sqrt(x) - 3)) + 1/8 * log(2*sqrt(x) + 2*sqrt(x + sqrt(x) + 1))).<br />
			 *
			 * @param x 
			 *			o <code>double</code> que representa o x
			 *
			 * @return o <code>double</code> que representa o resultado da avaliação
			 */
			double _evaluatePreciseIntegration(double x) {
				double x_sqrt = std::sqrt(x);
				double sqrt_x_plus_x_sqrt = std::sqrt(x + x_sqrt);
				return (sqrt_x_plus_x_sqrt * (8 * x + 2 * x_sqrt - 3) / 12.0f) + (std::log(2 * x_sqrt + 2 * sqrt_x_plus_x_sqrt + 1) / 8.0f);
			};

		public:
			/**
			 * Construtor padrão.<br />
			 */
			ThirdFunction() {
			};

			/**
			 * @see pel216::week6::Function#evaluate()
			 */
			virtual double evaluate(double x, double y = 0.0f, double z = 0.0f) {
				double result = std::sqrt(x + std::sqrt(x));
				return isnan(result) ? 0.0f : result;
			};

			/**
			 * @see pel216::week6::Function#evaluatePreciseIntegration()
			 */
			virtual double evaluatePreciseIntegration(double a = -1, double b = -1) {
				return _evaluatePreciseIntegration(b) - _evaluatePreciseIntegration(a);
			};

			/**
			 * @see pel216::week6::Function#toString()
			 */
			virtual std::string toString() {
				return "f(x) = sqrt(x + sqrt(x))";
			};

		}; /* class ThirdFunction */

	} /* namespace week7 */

} /* namespace pel216 */

#endif /* __THIRD_FUNCTION_WEEK7_H__ */
