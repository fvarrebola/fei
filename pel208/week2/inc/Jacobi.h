#pragma once

#ifndef __JACOBI_EIGEN_METHOD_H__
#define __JACOBI_EIGEN_METHOD_H__

#include <inc/Matrix.h>

using namespace pel208::commons;

namespace pel208 {

	namespace week2 {

		/**
		 * Implementação do método Jacobi iterativo para determinação de autovalores e autovetores conforme 
		 * descrito em <a href="http://www.nr.com/">Numerical Recipes: The Art of Scientific Computing</a>.<br />
		 * Também é utilizada a referência <a href="http://www.icmc.usp.br/pessoas/marialuisa/cursos201002/autovalor_autovetor.pdf">Autovalores e autovertores</a>.<br />
		 *
		 * @author arrebola
		 */
		class Jacobi {
		private:
			/**
			 * Obtém o elemento com maior valor absoluto fora da diagonal da matriz.<br />
			 *
			 * @param maxAbs
			 *			o <code>double</code> que representa o maior valor absoluto encontrado
			 * @param maxRowIdx
			 *			o <code>size_t</code> que representa o índice da linha do maior valor absoluto encontrado
			 * @param maxColIdx
			 *			o <code>size_t</code> que representa o índice da coluna do maior valor absoluto encontrado
			 *
			 * @return <code>true</code> caso a obtenção tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool max_off_diag(IN Matrix *C, OUT double *maxAbs, OUT size_t *maxRowIdx, OUT size_t *maxColIdx) {
				
				if (pel216::commons::Utils::isInvalidHandle(C)) {
					throw new IllegalParameterException();
				}

				size_t rowsCount = C->getRows();
        
				*maxAbs = 0.0f;
				for (size_t rowIdx = 0; rowIdx < rowsCount - 1; rowIdx++) {
					for (size_t colIdx = rowIdx + 1; colIdx < rowsCount; colIdx++) {
						register double abs = std::abs(C->data()[rowIdx][colIdx]);
						if (abs >= (*maxAbs)) {
							*maxAbs = abs;
							*maxRowIdx = rowIdx;
							*maxColIdx = colIdx;
						}
					}
				}
				
			    return true;

			};

			/**
			 * Rotaciona uma matriz.<br />
			 * 
			 * @param C
			 *				o Matrix que representa a matriz de covariância
			 * @param U
			 *				o Matrix que representa a matriz de rotação
			 * @param p
			 *				o <code>size_t</code> que representa o índice da linha do elemento a ser zerado na rotação
			 * @param q
			 *				o <code>size_t</code> que representa o índice da coluna do elemento a ser zerado na rotação
			 *
			 * @return <code>true</code> caso a rotação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool rotateUsingStandardMethod(
					IN OUT Matrix **C, 
					IN OUT Matrix **U, 
					IN size_t p, 
					IN size_t q) {
				
				if (pel216::commons::Utils::isInvalidHandle(*C) || pel216::commons::Utils::isInvalidHandle(*U)) {
					throw new IllegalParameterException();
				}

				double rows = (*C)->getRows();

				// calcula o phi
				double phi = ((*C)->data()[q][q] - (*C)->data()[p][p]) / (2.0f * (*C)->data()[p][q]);

				// calcula o t
				//int sign = (phi > 0 ? 1 : -1);
				//double t = 1.0f / (phi + (sign * std::sqrt(std::pow(phi, 2) + 1.0f)));
				double t = (phi < 0.0f ? -1 : 1) / (std::abs(phi) + std::sqrt(std::pow(phi, 2) + 1.0f));

				// calcula o coseno e o seno de rotação
				double cos = 1.0f / sqrt(std::pow(t, 2) + 1.0); // cos (lower_phi) = 1 / sqrt (1 + t^2)
				double sin = t * cos; // sin (lower_phi) = t / sqrt (1 + t^2)
				double tau = sin / (1.0f + cos);

				// zera o maior valor fora da diagonal e atualiza (i, i) e (j, j)
				double target = (*C)->data()[p][q];
				double t_times_target = t * target;
				(*C)->data()[p][p] -= t_times_target;
				(*C)->data()[q][q] += t_times_target;
				(*C)->data()[p][q] = 0.0f;

				// atualiza a matriz de dados
				for (size_t idx = 0; idx < p; idx++) { // 0 <= idx < p
					register double value_idx_rowIdx = (*C)->data()[idx][p];
					register double value_idx_colIdx = (*C)->data()[idx][q];
					(*C)->data()[idx][p] -= sin *(value_idx_colIdx + tau * value_idx_rowIdx);
					(*C)->data()[idx][q] += sin *(value_idx_rowIdx - tau * value_idx_colIdx);
				}
				for (size_t idx = p + 1; idx < q; idx++) { // p < idx < q
					register double value_rowIdx_idx = (*C)->data()[p][idx];
					register double value_idx_colIdx = (*C)->data()[idx][q];
					(*C)->data()[p][idx] -= sin *(value_idx_colIdx + tau * value_rowIdx_idx);
					(*C)->data()[idx][q] += sin *(value_rowIdx_idx - tau * value_idx_colIdx);
				}
				for (size_t idx = q + 1; idx < rows; idx++) { // q < idx < n
					register double value_rowIdx_idx = (*C)->data()[p][idx];
					register double value_colIdx_idx = (*C)->data()[q][idx];
					(*C)->data()[p][idx] -= sin *(value_colIdx_idx + tau * value_rowIdx_idx);
					(*C)->data()[q][idx] += sin *(value_rowIdx_idx - tau * value_colIdx_idx);
				}

				// atualiza a matriz de rotação
				for (size_t idx = 0; idx < rows; idx++) {
					register double value_idx_rowIdx = (*U)->data()[idx][p];
					register double value_idx_colIdx = (*U)->data()[idx][q];
					(*U)->data()[idx][p] -= sin * (value_idx_colIdx + (tau * value_idx_rowIdx));
					(*U)->data()[idx][q] += sin * (value_idx_rowIdx - (tau * value_idx_colIdx));
				}

				return true;

			};

			/**
			 * Rotaciona uma matriz utilizando multiplicações.<br />
			 * Baseado no método interativo encontrado em 
			 * <a href="http://www.math.utoledo.edu/~codenth/Linear_Algebra/Calculators/jacobi_algorithm.html">
			 * Linear Algebra Calculators - Jacobi Algorithm</a>.<br />
			 * 
			 * @param C
			 *				o Matrix que representa a matriz de covariância
			 * @param U
			 *				o Matrix que representa a matriz de rotação
			 * @param tolerance
			 *				o <code>double</code> que representa a tolerância para o método de Jacobi
			 *
			 * @return <code>true</code> caso a rotação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool rotateUsingMatrixMul(
					IN OUT Matrix **C, 
					IN OUT Matrix **U, 
					IN double tolerance) {

				size_t dimensions = (*C)->getRows();

				for (size_t p = 0; p < dimensions; p++) {

					for (size_t q = p + 1; q < dimensions; q++) {
						
						if (p == q) {
							continue;
						}

						register double phi = ((*C)->data()[p][p] - (*C)->data()[q][q]) / (2.0f * (*C)->data()[p][q]);
						if (std::abs((*C)->data()[p][q]) < tolerance) {
							continue;
						}

						register double t = (phi < 0.0f ? -1 : 1) / (std::abs(phi) + std::sqrt(std::pow(phi, 2) + 1.0f));
						register double cos = 1.0f / sqrt(std::pow(t, 2) + 1.0);
						register double sin = t * cos;

						Matrix *R = NULL;
						
						(*C)->identity(&R);
						R->data()[p][p] = cos;
						R->data()[p][q] = -sin;
						R->data()[q][p] = sin;
						R->data()[q][q] = cos;
						
						(*C) = R->transpose()->multiply((*C)->multiply(R));
						(*U) = (*U)->multiply(R);

						delete R;				

					}

				}

				return true;

			};

			/**
			 * Ordena os autovalores e autovetores.<br />
			 * 
			 * @param C
			 *				o Matrix que representa a matriz de covariância
			 * @param U
			 *				o Matrix que representa a matriz de rotação
			 * @param components
			 *				o <code>size_t</code> que representa a quantidade de componentes a serem considerados
			 * @param L
			 *				o Matrix que representa a matriz de autovalores
			 * @param V
			 *				o Matrix que representa a matriz de autovetores
			 */
			PRIVATE static void sortEigenValuesAndVectors(
					IN Matrix *C, 
					IN Matrix *U, 
					IN size_t components,
					IN OUT Matrix **L, 
					IN OUT Matrix **V) {

				if (pel216::commons::Utils::isInvalidHandle(C)) {
					throw new IllegalParameterException();
				}
				
				size_t dimensions = C->getRows();
				size_t *indexes = new size_t[dimensions];

				// obtém os índices dos autovalores de forma decrescente
				Matrix *diagonal = C->diagonal();
				for (size_t idx = 0; idx < dimensions; idx++) {
					register double max = LONG_MIN;
					register size_t r = UINT_MAX;
					register size_t c = UINT_MAX;
					diagonal->max(&max, &r, &c);
					indexes[idx] = r;
					diagonal->data()[r][c] = LONG_MIN;	
				}

				delete diagonal;

				// cria as matrizes L e V com base nos índices obtidos anteriormente
				(*L) = new Matrix(components, 1);
				(*V) = new Matrix(dimensions, dimensions);
				for (size_t i = 0; i < components; i++) {
					(*L)->data()[i][0] = C->data()[indexes[i]][indexes[i]];
					for (size_t j = 0; j < dimensions; j++) {
						(*V)->data()[j][i] = U->data()[j][indexes[i]];
					}
				}

			};

		public:
			/**
			 * Construtor.
			 */
			Jacobi() {
			};

			/**
			 * Executa o método de busca.<br />
			 *
			 * @param covarMatrix
			 *				o Matrix que representa a matrix de covariância
			 * @param eigenValues
			 *				o Matrix que representa os autovalores
			 * @param eigenVectors
			 *				o Matrix que representa os autovetores
			 * @param maxComponents
			 *				o <code>size_t</code> que representa a quantidade máxima de componentes a serem considerados
			 * @param useMaxOffDiagonal
			 *				indica se deve ser utilizado o método que rotaciona a matriz a partir do maior valor fora da diagonal
			 *				encontrado no triangulo superior
			 * @param sort
			 *				indica se os componentes devem ser ordenados por importância
			 * @param maxRotations
			 *				o <code>size_t</code> que representa a quantidade máxima de rotações utilizadas pelo método de Jacobi
			 * @param tolerance
			 *				o <code>double</code> que representa a tolerância para o método de Jacobi
			 * @param debug
			 *				indica se devem ser exibidas mensagens de debug
			 *
			 * @return <code>true</code> caso o cálculo tenha sido bem sucedido; do contrário <code>false</code>
			 */
			PUBLIC static bool evaluate(
					IN Matrix *covarMatrix, 
					OUT Matrix **eigenValues, 
					OUT Matrix **eigenVectors, 
					IN size_t maxComponents = UINT_MAX,
					IN bool useMaxOffDiagonal = false,
					IN bool sort = true,
					IN size_t maxRotations = UINT_MAX, 
					IN double tolerance = 0.000001f, 
					IN bool debug = false) {

				if (pel216::commons::Utils::isInvalidHandle(covarMatrix)) {
					throw new IllegalParameterException();
				}

				if (debug) {
					Logger::log("%s\n", STARS);
					Logger::log("Metodo de Jacobi para autovalores e autovetores\n");
					Logger::log("  rotacoes = %d\n", maxRotations);
					Logger::log("  tolerancia = %f\n", tolerance);
					if (useMaxOffDiagonal) {
						Logger::log("  tecnica = maior valor no triangulo superior acima da diagonal\n");
					} else {
						Logger::log("  tecnica = ciclica\n");
					}
					Logger::log("%s\n", STARS);
				}

				// a matriz de rotação
				Matrix *U = NULL;
				if (!covarMatrix->identity(&U)) {
					return false;
				}

				// a matriz que será rotacionada
				Matrix *C = covarMatrix->clone();

				bool converged = false;
				size_t rotations = (maxRotations == UINT_MAX) ? 5 * C->getRows() * C->getRows() : maxRotations;
				for (size_t idx = 0; idx < rotations && !converged; idx++) {
					
					register double maxAbs = 0.0f;
					register size_t maxRowIdx = UINT_MAX;
					register size_t maxColIdx = UINT_MAX;

					if (debug) {
						Logger::log(">> Iteracao #%d\n", idx + 1);
						U->dump("rotacao");
						C->dump("dados");
					}

					if (!max_off_diag(C, &maxAbs, &maxRowIdx, &maxColIdx)) {
						break;
					}

					if (maxAbs < tolerance) {
						converged = true;
					} else {
						if (useMaxOffDiagonal) {
							rotateUsingStandardMethod(&C, &U, maxRowIdx, maxColIdx);
						} else {
							rotateUsingMatrixMul(&C, &U, tolerance);
						}
					}

				}

				// caso a solução tenha convergido...
				if (converged) {
					size_t dimensions = C->getRows();
					size_t components = (maxComponents != UINT_MAX && maxComponents < dimensions) ? maxComponents : dimensions;
					if (sort) {
						sortEigenValuesAndVectors(C, U, components, eigenValues, eigenVectors);
					}
				}

				delete U;
				delete C;

				return true;

			};

		}; /* class Jacobi */

	} /* namespace week2 */

} /* namespace pel208 */

#endif /* __JACOBI_EIGEN_METHOD_H__ */
