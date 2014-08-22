#pragma once

#ifndef __FIRST_FUNCTION_WEEK7_H__
#define __FIRST_FUNCTION_WEEK7_H__

#include <cstdarg>
#include <cmath>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/Function.h>

namespace pel216 {

	namespace week7 {

		/**
		 * Classe que representa a fun��o f(x) = sqrt(x).<br />
		 *
		 * @author arrebola
		 */
		class FirstFunction : public pel216::week6::Function {

		private:
			/**
			 * Avalia a integral precisa da fun��o, dada por (2 * x^3/2) /3.<br />
			 *
			 * @param x 
			 *			o <code>double</code> que representa o x
			 *
			 * @return o <code>double</code> que representa o resultado da avalia��o
			 */
			double _evaluatePreciseIntegration(double x) {
				return ((2.0f * std::pow(x, 3.0f /2.0f)) / 3.0f);
			};

		public:
			/**
			 * Construtor padr�o.<br />
			 */
			FirstFunction() {
			};

			/**
			 * @see pel216::week6::Function#evaluate()
			 */
			virtual double evaluate(double x, double y = 0.0f, double z = 0.0f) {
				double result = std::sqrt(x);
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
				return "f(x) = sqrt(x)";
			};

		}; /* class FirstFunction */

	} /* namespace week7 */

} /* namespace pel216 */

#endif /* __FIRST_FUNCTION_WEEK7_H__ */
