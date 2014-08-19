#pragma once

#ifndef __THIRD_FUNCTION_H__
#define __THIRD_FUNCTION_H__

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/Function.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week6 {

		/**
		 * Classe que representa a função f(x) = e^(-x^2).<br />
		 * A primeira derivada é df/dx = -2x * e^(-x^2).<br />
		 * A segunda derivada é df/dx = ((4x^2) * e^(-x^2)) - 2*(-x^2).<br />
		 *
		 * @author arrebola
		 */
		class ThirdFunction : public Function {

		private:

			/**
			 * Reprodução da função erf() obtida de http://www.johndcook.com/cpp_erf.html.<br />
			 */
			static double erf(double x) {

				double a1 =  0.254829592;
				double a2 = -0.284496736;
				double a3 =  1.421413741;
				double a4 = -1.453152027;
				double a5 =  1.061405429;
				double p  =  0.3275911;

				int sign = (x < 0) ? -1 : 1;
				x = fabs(x);

				double t = 1.0/(1.0 + p*x);
				double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

				return sign*y;

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
			virtual double evaluate(double x) {
				return std::exp(-1.0f * std::pow(x, 2.0f));
			};

			/**
			 * @see pel216::week6::Function#evaluatePreciseIntegration()
			 */
			virtual double evaluatePreciseIntegration(double a = -1, double b = -1) {
				return (0.5f * std::sqrt(pel216::commons::pi) * erf(b)) - (0.5f * std::sqrt(pel216::commons::pi) * erf(a));
			};

			/**
			 * @see pel216::week6::Function#toString()
			 */
			virtual std::string toString() {
				return "f(x) = e^(-x^2)";
			};

		}; /* class ThirdFunction */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __THIRD_FUNCTION_H__ */
