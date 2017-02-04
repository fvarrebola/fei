#pragma once

#ifndef __SECOND_FUNCTION_WEEK7_H__
#define __SECOND_FUNCTION_WEEK7_H__

#include <cstdarg>
#include <cmath>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/Function.h>

namespace pel216 {

	namespace week7 {

		/**
		 * Classe que representa a função f(x) = 4 / (1 + x^2).<br />
		 *
		 * @author arrebola
		 */
		class SecondFunction : public pel216::week6::Function {

		private:
			/**
			 * Avalia a integral precisa da função, dada por (4 * arctan(x)).<br />
			 *
			 * @param x 
			 *			o <code>double</code> que representa o x
			 *
			 * @return o <code>double</code> que representa o resultado da avaliação
			 */
			double _evaluatePreciseIntegration(double x) {
				return (4 * std::atan(x));
			};

		public:
			/**
			 * Construtor padrão.<br />
			 */
			SecondFunction() {
			};

			/**
			 * @see pel216::week6::Function#evaluate()
			 */
			virtual double evaluate(double x, double y = 0.0f, double z = 0.0f) {
				double result = 4 / (1 + std::pow(x, 2));
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
				return "f(x) = 4 / (1 + x^2)";
			};

		}; /* class SecondFunction */

	} /* namespace week7 */

} /* namespace pel216 */

#endif /* __SECOND_FUNCTION_WEEK7_H__ */
