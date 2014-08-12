#pragma once

#ifndef __FIRST_FUNCTION_H__
#define __FIRST_FUNCTION_H__

#include <cstdarg>
#include <cmath>

#include <inc/Logger.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/Function.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week5 {

		/**
		 * Classe que representa a função f(x) = x^2.<br />
		 * Sua primeira derivada é df/dx = 2*x.
		 *
		 * @author arrebola
		 */
		class FirstFunction : public Function {

		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param x0
			 *			o <code>double</double> que representa o ponto inicial
			 */
			FirstFunction(double x0) {
				this->dimensionsCount = ONE;
				this->initialValue = std::vector<double>(ONE);
				this->initialValue[ZERO] = x0;
			};

			/**
			 * @see pel216::week5::Function#evaluate()
			 */
			virtual std::vector<double> evaluate(std::vector<double> params = std::vector<double>(ZERO)) {

				std::vector<double> result(this->dimensionsCount);
				result[ZERO] = std::pow(params[ZERO], 2.0);

				return result;

			};

			/**
			 * @see pel216::week5::Function#derivativeOfX()
			 */
			virtual double derivativeOfX(std::vector<double> params = std::vector<double>(ZERO)) {
				return params[ZERO] * 2.0;
			};

			/**
			 * @see pel216::week5::Function#toString()
			 */
			virtual std::string toString() {
				return "f(x) = x^2";
			};

		}; /* class FirstFunction */

	} /* namespace week5 */

} /* namespace pel216 */

#endif /* __FIRST_FUNCTION_H__ */
