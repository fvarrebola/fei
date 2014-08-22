#pragma once

#ifndef __TOROID_FUNCTION_H__
#define __TOROID_FUNCTION_H__

#include <cmath>

#include <inc/Function.h>

namespace pel216 {

	namespace week7 {

		/**
		 * Classe que representa a função de um toróide.<br />
		 *
		 * @author arrebola
		 */
		class ToroidFunction : public pel216::week6::Function {

		public:
			/**
			 * Construtor padrão.<br />
			 */
			ToroidFunction() {
			};

			/**
			 * @see pel216::week6::Function#evaluate()
			 */
			virtual double evaluate(double x, double y = 0.0f, double z = 0.0f) {
				double x_sq = std::pow(x, 2.0f);
				double y_sq = std::pow(y, 2.0f);
				double z_sq = std::pow(z, 2.0f);
				return (((-6.0f * std::sqrt(x_sq + y_sq)) + x_sq + y_sq + z_sq + 9.0f - 1.0f));
			};

			/**
			 * @see pel216::week6::Function#evaluatePreciseIntegration()
			 */
			virtual double evaluatePreciseIntegration(double a = -1, double b = -1) {
				throw new std::exception();
			};

			/**
			 * @see pel216::week6::Function#toString()
			 */
			virtual std::string toString() {
				return "z^2 + (sqrt(x^2 + y^2) - 2)^2 <= 1";
			};

		}; /* class ToroidFunction */

	} /* namespace week7 */

} /* namespace pel216 */

#endif /* __TOROID_FUNCTION_H__ */
