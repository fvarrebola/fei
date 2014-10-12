#pragma once

#ifndef __PCA_METHOD_H__
#define __PCA_METHOD_H__

#include <inc/Matrix.h>
#include <inc/Jacobi.h>

using namespace pel208::commons;

namespace pel208 {

	namespace week2 {

		/**
		 * Implementação do método PCA.<br />
		 *
		 * @author arrebola
		 */
		class PCAMethod {
		private:

		public:
			/**
			 * Construtor.
			 */
			PCAMethod() {
			};

			/**
			 * Executa o método PCA.<br />
			 *
			 * @param data
			 *				o Matrix que representa a matriz com as entradas que se quer analisar
			 * @param pca
			 *				o Matrix que representa a matriz com as entradas ajustadas
			 * @param components
			 *				o <code>size_t</code> que indica a quantidade de componentes a considerar
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return o <code>double</code> que representa o valor encontrado para o alvo
			 */
			PUBLIC static bool evaluate(
					IN Matrix *data, 
					IN OUT Matrix **pca, 
					IN size_t components = UINT_MAX, 
					IN bool debug = false) {

				if (pel216::commons::Utils::isInvalidHandle(data)) {
					throw new IllegalParameterException();
				}

				size_t dimensions = data->getRows();

				// calculando a matriz de covariância
				Matrix *adjusted = NULL;
				Matrix *covariate = data->covariate(&adjusted);
				if (pel216::commons::Utils::isInvalidHandle(covariate)) {
					return false;
				}

				if (debug) {
					data->dump("data");
					adjusted->dump("adjusted");
					covariate->dump("covariate");
				}

				// calculando as matrizes de auto valores e auto vetores
				Matrix *eigenValues = NULL;
				Matrix *eigenVectors = NULL;
				if (Jacobi::evaluate(covariate, &eigenValues, &eigenVectors, components)) {

					Matrix *eigenVectors_T = eigenVectors->transpose();
					*pca = adjusted->multiply(eigenVectors_T);

					if (debug) {
						eigenValues->dump("eigenValues");
						eigenVectors->dump("eigenVectors");
						(*pca)->dump("pca");
					}

					delete eigenVectors_T;

				}

				delete eigenVectors;
				delete eigenValues;
				delete adjusted;
				delete covariate;

				return true;

			};

		}; /* class PCAMethod */

	} /* namespace week2 */

} /* namespace pel208 */

#endif /* __PCA_METHOD_H__ */
