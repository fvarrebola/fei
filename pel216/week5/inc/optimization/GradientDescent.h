#pragma once

#ifndef __GRADIENT_DESCENT_H__
#define __GRADIENT_DESCENT_H__

#include <cmath>
#include <limits>

#include <inc/Function.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week5 {

		/**
		 * Classe de testes.
		 *
		 * @author arrebola
		 */
		class GradientDescent {

		private:
			bool debug;

			/**
			 * Determina se um vetor de <code>double</code> contém valores válidos.
			 *
			 * @param value
			 *			o <code>std::vector</code> de <code>double</code> que representa o vetor de valores
			 *
			 * @return <code>true</code> caso o vetor seja válido; do contrário <code>false</code>
			 */
			static bool _isValid(std::vector<double> vector) {

				bool isValid = true;

				if (vector.empty()) {
					return isValid;
				}

				size_t size = vector.size();
				for (size_t idx = 0; (idx < size) && isValid; idx++) {
					double value = vector[idx];
					isValid = (!_isnan(value) && _finite(value));
				}

				return isValid;

			};

			/**
			 * Determina se a função convergiu.<br />
			 * A convergência é determinada com base na...
			 *
			 * @return <code>true</code> caso a função tenha convergido; do contrário <code>false</code>
			 */
			static bool _hasConverged(std::vector<double> value1, std::vector<double> value2, double precision) {

				bool converged = true;
				size_t size = value1.size();

				for (size_t idx = 0; idx < size && converged; idx++) {
					converged = (std::fabs(value1[idx] - value2[idx]) < precision);
				}

				return converged;

			};

			/**
			 * Determina o novo valor de uma iteração no algoritmo de descida de gradiente.<br />
			 * O novo valor é determinado para todas as dimensões da função utilizando a seguinte fórmula:<br />
			 * valor = valor - beta * derivada(valor)
			 *
			 * @param function
			 *			o @link{Function} que determina a função
			 * @param beta 
			 *			o <code>double</code> que representa a descida em pequenas etapas
			 * @param value
			 *			o <code>std::vector<double></code> que representa o valor atual
			 * 
			 * @return o <code>std::vector<double></code> que representa o novo valor
			 */
			static std::vector<double> _computeNewValue(Function *function, double beta, std::vector<double> value) {

				size_t dimensionCount = function->getDimesionsCount();

				std::vector<double> newValue(dimensionCount);

				double dX = function->derivativeOfX(value);
				newValue[ZERO] = (value[ZERO] - beta * dX);

				if (dimensionCount == TWO) {
					std::vector<double> newValueForYDerivative(TWO);
					newValueForYDerivative[ZERO] = newValue[ZERO];
					newValueForYDerivative[ONE] = value[ONE];
					double dY = function->derivativeOfY(newValueForYDerivative);
					newValue[ONE] = (value[ONE] - beta * dY);
				}

				return newValue;

			};

		public:
			/**
			 * Construtor.
			 *
			 * @param debug
			 *			o <code>bool</code> que indica se as mensagens de <i>debug</i> devem ser exibidas
			 */
			GradientDescent(bool debug = false) {
				this->debug = debug;
			};

			/**
			 * Avalia a descida de gradiente de uma função.
			 *
			 * @param function
			 *			o @link{Function} que determina a função
			 * @param lambda 
			 *			o <code>double</code> que representa a descida em pequenas etapas
			 * @param precision
			 *			o <code>double</code> que representa a precisão das comparações
			 * @param max_iteractions
			 *			o <code>size_t</code> que representa a quantidade máxima de iterações
			 */
			void evaluate(Function *function, double lambda = 0.1f, double precision = 0.00001f, size_t max_iteractions = 100) {

				Logger::log("\n");
				Logger::log("%s\n", STARS);
				Logger::log("* Avaliando funcao: %s\n", function->toString().c_str());
				Logger::log("* Parametros:\n");
				Logger::log("*   Lambda: %.5f\n", lambda);
				Logger::log("*   Precisao: %.5f\n", precision);
				Logger::log("*   Qtde maxima de iteracoes: %d\n", max_iteractions);
				Logger::log("%s\n", STARS);

				if (this->debug) {
					Logger::log("Imprimindo valores...\n");
				}

				size_t dimensionCount = function->getDimesionsCount();
				
				std::vector<double> temporaryValue(dimensionCount);
				std::vector<double> value = function->getInitialValue();
			
				size_t iteractions = 0;
				bool converged = _hasConverged(value, temporaryValue, precision);
				while (_isValid(value) && !converged && (iteractions < max_iteractions)) {

					iteractions++;

					temporaryValue = value;

					if (this->debug) {
						Logger::log("%s, %s\n", 
							Utils::doubleVectorToString(value).c_str(),
							Utils::doubleVectorToString(function->evaluate(value)).c_str());
					}

					value = _computeNewValue(function, lambda, value);
					converged = _hasConverged(value, temporaryValue, precision);
				
				}

				Logger::log("A funcao %s apos %d iteracoes\n", (converged ? "convergiu" : "divergiu"), iteractions);
				Logger::log("%s\n", STARS);

			};

		}; /* class GradientDescent */

	} /* namespace week5 */

} /* namespace pel216 */

#endif /* __GRADIENT_DESCENT_H__ */
