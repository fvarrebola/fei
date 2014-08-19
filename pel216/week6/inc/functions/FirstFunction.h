#pragma once

#ifndef __FIRST_FUNCTION_H__
#define __FIRST_FUNCTION_H__

#include <cstdarg>
#include <cmath>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/Function.h>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa a fun��o f(x) = e^x.<br />
		 *
		 * @author arrebola
		 */
		class FirstFunction : public Function {

		private:

		public:
			/**
			 * Construtor padr�o.<br />
			 */
			FirstFunction() {
			};

			/**
			 * @see pel216::week6::Function#evaluate()
			 */
			virtual double evaluate(double x) {
				double result = std::exp(x);
				return isnan(result) ? 0.0f : result;
			};

			/**
			 * @see pel216::week6::Function#evaluatePreciseIntegration()
			 */
			virtual double evaluatePreciseIntegration(double a = -1, double b = -1) {
				return evaluate(b) - evaluate(a);
			};

			/**
			 * @see pel216::week6::Function#toString()
			 */
			virtual std::string toString() {
				return "f(x) = e^x";
			};

		}; /* class FirstFunction */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __FIRST_FUNCTION_H__ */
