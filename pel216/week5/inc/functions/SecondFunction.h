#pragma once

#ifndef __SECOND_FUNCTION_H__
#define __SECOND_FUNCTION_H__

#include <inc/Function.h>

namespace pel216 {

	namespace week5 {

		/**
		 * Classe que representa a função f(x) = x^3 - 2x^2	+ 2.<br />
		 * A primeira derivada é df/dx = 3x^2 - 4x.<br />
		 *
		 * @author arrebola
		 */
		class SecondFunction : public Function {

		private:

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param x0
			 *			o <code>double</double> que representa o ponto inicial
			 */
			SecondFunction(double x0) {
				this->dimensionsCount = ONE;
				this->initialValue = std::vector<double>(this->dimensionsCount);
				this->initialValue[ZERO] = x0;
			};

			/**
			 * @see pel216::week5::Function#evaluate()
			 */
			virtual std::vector<double> evaluate(std::vector<double> params = std::vector<double>(0)) {

				std::vector<double> result(this->dimensionsCount);

				double x = params[ZERO];
				result[ZERO] = (std::pow(x, 3.0) - (2 * (std::pow(x, 2.0))) + 2);

				return result;

			};

			/**
			 * @see pel216::week5::Function#derivativeOfX()
			 */
			virtual double derivativeOfX(std::vector<double> params = std::vector<double>(0)) {
				double x = params[ZERO];
				return (3.0 * std::pow(x, 2.0)) - (4 * x);
			};

			/**
			 * @see pel216::week5::Function#toString()
			 */
			virtual std::string toString() {
				return "f(x) = x^3 - 2x^2 + 2";
			};

		}; /* class SecondFunction */

	} /* namespace week5 */

} /* namespace pel216 */

#endif /* __SECOND_FUNCTION_H__ */
