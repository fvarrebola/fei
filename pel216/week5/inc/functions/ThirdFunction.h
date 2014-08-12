#pragma once

#ifndef __THIRD_FUNCTION_H__
#define __THIRD_FUNCTION_H__

#include <inc/Function.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week5 {

		/**
		 * Classe que representa a função f(x, y) = (1 - x)^2 + 100*(y - x^2)^2.<br />
		 * A primeira derivada em função de x é df/dx = −400*x*(y − x^2) − 2*(1 − x).
		 * A primeira derivada em função de y é df/dy = 200*(y - x^2).
		 *
		 * @author arrebola
		 */
		class ThirdFunction : public Function {

		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param x0
			 *			o <code>double</double> que representa o ponto inicial
			 * @param y0
			 *			o <code>double</double> que representa o ponto inicial
			 */
			ThirdFunction(double x0 = 0.0f, double y0 = 0.0f) {
				this->dimensionsCount = TWO;
				this->initialValue = std::vector<double>(this->dimensionsCount);
				this->initialValue[ZERO] = x0;
				this->initialValue[ONE] = y0;
			};

			/**
			 * @see pel216::week5::Function#evaluate()
			 */
			virtual std::vector<double> evaluate(std::vector<double> params = std::vector<double>(ZERO)) {

				if (params.size() != this->dimensionsCount) {
					throw new IllegalParameterException();
				}

				std::vector<double> result(this->dimensionsCount);

				double x = params[ZERO];
				double y = params[ONE];
				
				result[ZERO] = std::pow(1 - x, 2.0) + 100 * (std::pow(y - std::pow(x, 2.0), 2.0));

				return result;

			};

			/**
			 * @see pel216::week5::Function#derivativeOfX()
			 */
			virtual double derivativeOfX(std::vector<double> params = std::vector<double>(ZERO)) {
				
				if (params.size() != this->dimensionsCount) {
					throw new IllegalParameterException();
				}

				double x = params[ZERO];
				double y = params[ONE];

				return (-400 * x * (y - std::pow(x, 2.0f)) - (2 * (1 - x))); 

			};

			/**
			 * @see pel216::week5::Function#derivativeOfY()
			 */
			virtual double derivativeOfY(std::vector<double> params = std::vector<double>(ZERO)) {
				
				if (params.size() != this->dimensionsCount) {
					throw new IllegalParameterException();
				}

				double x = params[ZERO];
				double y = params[ONE];

				return (200 * (y - std::pow(x, 2.0f)));

			};
			
			/**
			 * @see pel216::week5::Function#toString()
			 */
			virtual std::string toString() {
				return "f(x,y) = (1 - x)^2 + 100(y - x^2)^2";
			};

		}; /* class ThirdFunction */

	} /* namespace week5 */

} /* namespace pel216 */

#endif /* __THIRD_FUNCTION_H__ */
