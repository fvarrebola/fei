#pragma once

#ifndef __LEAST_SQUARES_METHOD_H__
#define __LEAST_SQUARES_METHOD_H__

#include <list>
#include <queue>
#include <functional>

#include <inc/Matrix.h>

using namespace pel208::commons;

namespace pel208 {

	namespace week1 {

		/**
		 * Implementação do método least squares.<br />
		 *
		 * @author arrebola
		 */
		class LeastSquaresMethod {
		private:
			Matrix *xMatrix;
			Matrix *yMatrix;
			double bias;

		public:
			/**
			 * Construtor.
			 *
			 * @param xMatrix
			 *				o Matrix que representa a matriz de entradas
			 * @param yMatrix
			 *				o Matrix que representa a matriz de resultados
			 * @param bias
			 *				o <code>double</code> que representa o bias
			 */
			LeastSquaresMethod(Matrix *xMatrix, Matrix *yMatrix, double bias = 1.0f) {
				this->xMatrix = xMatrix;
				this->yMatrix = yMatrix;
				this->bias = bias;
			};

			/**
			 * Executa o método dos mínimos quadrados.
			 *
			 * @param target
			 *				o Matrix que representa a matriz com as entradas que se quer estimar
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return o <code>double</code> que representa o valor encontrado para o alvo
			 */
			double evaluate(Matrix *target, bool debug = false) {

				double result = 0.0f;

				// configura o B(0)
				xMatrix->setColumnCellsValue(0, bias);

				// X^T
				Matrix *x_t = xMatrix->transpose();

				// X * X^T
				Matrix *x___times___x_t = x_t->multiply(xMatrix);
	
				// X^T * Y
				Matrix *x_t___times___y = x_t->multiply(yMatrix);

				// (X * X^T) ^ -1
				Matrix *inverted = NULL;
				x___times___x_t->invert(&inverted);

				// B
				Matrix *beta_approx = inverted->multiply(x_t___times___y);

				// alvo
				Matrix target_matrix(1, target->getColumns() + 1);
				target_matrix.data()[0][0] = bias;
				for (size_t idx = 0; idx < target->getColumns(); idx++) {
					target_matrix.data()[0][idx + 1] = target->data()[0][idx];
				}

				// matriz de resultado
				Matrix *result_matrix = target_matrix.multiply(beta_approx);

				if (debug) {
					xMatrix->dump("X");
					yMatrix->dump("Y");
					x_t->dump("X^T");
					x___times___x_t->dump("X * X^T");
					x_t___times___y->dump("X^T * y");
					inverted->dump("(X * X^T) ^ -1");
					beta_approx->dump("B");
				}

				result = result_matrix->data()[0][0];

				return result;

			};

		}; /* class LeastSquaresMethod */

	} /* namespace week1 */

} /* namespace pel208 */

#endif /* __LEAST_SQUARES_METHOD_H__ */
