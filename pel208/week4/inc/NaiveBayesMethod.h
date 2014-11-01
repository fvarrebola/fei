#pragma once

#ifndef __NAIVE_BAYES_METHOD_H__
#define __NAIVE_BAYES_METHOD_H__

#include <map>
#include <string>

#include <inc/Matrix.h>

using namespace pel208::commons;

namespace pel208 {

	namespace week4 {

		class NBStatsMatrix : public Matrix {
		public:
			/**
			 * Construtor.
			 */
			NBStatsMatrix(size_t rows) : Matrix(rows, 5) {
			};

		};

		/**
		 * Implementação do método Naive Bayes.<br />
		 *
		 * @author arrebola
		 */
		class NaiveBayes {
		private:
			typedef std::map<std::string, NBStatsMatrix*>::iterator it_type;
			
			size_t classColumnIdx;
			NBStatsMatrix *classStats;
			std::map<std::string, NBStatsMatrix*> *model;

			/**
			 * Gera uma matriz de contagem de características.<br />
			 *
			 * @param dataMatrix
			 *			o Matrix que representa a matriz de dados
			 * @param featureColumnIdx
			 *			o <code>size_t</code> que representa o índice da coluna
			 * @param classColumnIdx
			 *			o <code>size_t</code> que representa o índice da coluna
			 *
			 * @return o NBStatsMatrix  que representa a matriz de contagem de características
			 */
			PRIVATE static NBStatsMatrix *buildFeatureCountMatrix(
					IN Matrix *dataMatrix, 
					IN size_t featureColumnIdx, 
					IN size_t classColumnIdx) {

				// em termos de quantidade de linhas a matriz de valores únicos
				// é, no máximo, igual à matriz atual
				size_t rows = dataMatrix->getRows();
				NBStatsMatrix *stats = new NBStatsMatrix(rows);

				size_t count = 0;
				
				for (size_t rowIdx = 0; rowIdx < rows; rowIdx++) {

					register double valueA = dataMatrix->data()[rowIdx][featureColumnIdx];
					register double valueB = dataMatrix->data()[rowIdx][classColumnIdx];

					bool known = false;

					if (rowIdx > 0) {
						size_t invRowIdx = rowIdx;
						while (invRowIdx > 0 && !known) {
							if ((dataMatrix->data()[rowIdx][featureColumnIdx] == 
										dataMatrix->data()[invRowIdx - 1][featureColumnIdx]) &&
									(dataMatrix->data()[rowIdx][classColumnIdx] == 
										dataMatrix->data()[invRowIdx - 1][classColumnIdx])) {
								known = true;							
							}
							invRowIdx--;
						}
					}

					if (known) {
						for (size_t idx = 0; idx < count; idx++) {
							if ((stats->data()[idx][0] == valueA) && (stats->data()[idx][1] == valueB)) {
								stats->data()[idx][2] += 1;
								break;
							}
						}
					} else {
						stats->data()[count][0] = valueA;
						stats->data()[count][1] = valueB;
						stats->data()[count][2] = 1;
						count++;
					}

				}

				stats->shrink(count);

				for (size_t statsIdx = 0; statsIdx < count; statsIdx ++) {
					stats->data()[statsIdx][3] = stats->data()[statsIdx][2] / (rows * 1.0f);
				}

				return stats;

			};

			/**
			 * Gera um mapa de matrizes de estatísticas de características.<br />
			 *
			 * @param dataMatrix
			 *			o Matrix que representa a matriz de dados
			 * @param debug
			 *			indica se as matrizes devem ser impressas
			 *
			 * @return <code>true</code> caso a geração tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE bool buildStatsMatrixMap(
					IN Matrix *dataMatrix,
					IN bool debug = false) {

				size_t rows = dataMatrix->getRows();
				size_t columns = dataMatrix->getColumns();

				this->model = new std::map<std::string, NBStatsMatrix*>();

				// obtém as quantidades de cada classe de características
				for (size_t colIdx = 0; colIdx < columns; colIdx++) {
					this->model->insert(
						std::pair<std::string, NBStatsMatrix*>(
							std::to_string(colIdx), 
							buildFeatureCountMatrix(dataMatrix, colIdx, this->classColumnIdx)));
				}

				// calcula as estatísticas com base nas classes disponíveis
				NBStatsMatrix *classesMatrix = this->model->at(std::to_string(this->classColumnIdx));
				for (it_type iterator = this->model->begin(); iterator != this->model->end(); iterator++) {

					NBStatsMatrix *featureMatrix = iterator->second;
					for (size_t featIdx = 0; featIdx < featureMatrix->getRows(); featIdx++) {
						for (size_t classIdx = 0; classIdx < classesMatrix->getRows(); classIdx++) {
							if (featureMatrix->data()[featIdx][1] == classesMatrix->data()[classIdx][0]) {
								featureMatrix->data()[featIdx][4] = featureMatrix->data()[featIdx][2] / (classesMatrix->data()[classIdx][2] * 1.0f);
							}
						}
					}

					if (debug) {
						featureMatrix->dump(iterator->first);
					}
				
				}

				this->classStats = this->model->find(std::to_string(this->classColumnIdx))->second;

				return true;

 			};

			/**
			 * Constrói a tabela de hipótesis para a característica.<br />
			 *
			 * @param dataMatrix
			 *				o Matrix que representa a matriz com as entradas que se quer analisar
			 * @param featureColIdx
			 *				o <code>size_t</code> que indica o índice da coluna que representa a caracterísitca
			 * @param hipothesis
			 *				o Matrix que representa a matriz de hiótesis
			 *
			 * @return o <code>true</code> caso a construção do modelo tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE bool buildFeatureHipothesis(
					IN Matrix *dataMatrix, 
					IN size_t featureColIdx,
					IN OUT Matrix **hipothesis) {

				size_t classes = this->classStats->getRows();

				if (pel216::commons::Utils::isInvalidHandle((*hipothesis))) {
					*hipothesis = new Matrix(classes, 2);
				}

				for (size_t classIdx = 0; classIdx < classes; classIdx++) {

					register double classId = classStats->data()[classIdx][0];
					register double featStatsValue = 0.0f;
					
					NBStatsMatrix *featStats = this->model->find(std::to_string(featureColIdx))->second;
					for (size_t statsRowIdx = 0; statsRowIdx < featStats->getRows(); statsRowIdx++) {
						if ((dataMatrix->data()[0][featureColIdx] == featStats->data()[statsRowIdx][0]) &&
							(featStats->data()[statsRowIdx][1]) == classId) {
								featStatsValue = featStats->data()[statsRowIdx][4];
								break;
						}
					}

					register double curValue = (*hipothesis)->data()[classIdx][1];
					(*hipothesis)->data()[classIdx][0] = classId;
					(*hipothesis)->data()[classIdx][1] = (curValue > 0.0f ? curValue * featStatsValue : featStatsValue); 

				}

				return true;

			};

		public:
			/**
			 * Construtor.<br />
			 */
			NaiveBayes() {
				this->model = NULL;
				this->classStats = NULL;
			};

			/**
			 * Destrutor.<br />
			 */
			~NaiveBayes() {
				if (pel216::commons::Utils::isValidHandle(this->model)) {
					for (it_type iterator = (this->model)->begin(); iterator != (this->model)->end(); iterator++) {
						delete iterator->second;
					}
					delete this->model;
				}
			};

			/**
			 * Executa o método Naive Bayes.<br />
			 *
			 * @param dataMatrix
			 *				o Matrix que representa a matriz com as entradas que se quer analisar
			 * @param classColumnIdx
			 *				o <code>size_t</code> que indica o índice da coluna que representa as classes
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return o <code>true</code> caso a construção do modelo tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool buildModel(
					IN Matrix *dataMatrix,
					IN size_t classColumnIdx,
					IN bool debug = false) {

				bool result = false;

				// determina se a matriz é válida
				if (pel216::commons::Utils::isInvalidHandle(dataMatrix)) {
					throw new IllegalParameterException();
				}

				// determina se a matriz é válida
				if (classColumnIdx > dataMatrix->getColumns()) {
					throw new IllegalParameterException();
				}

				this->classColumnIdx = classColumnIdx;

				// constrói as estatísticas relacionando características e classes
				return buildStatsMatrixMap(dataMatrix, debug);

			};

			/**
			 * Avalia um exemplo contra o modelo.<br />
			 *
			 * @param dataMatrix
			 *				o Matrix que representa a matriz com as entradas que se quer analisar
			 * @param hipothesis
			 *				o Matrix que representa a matriz de hiótesis
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return o <code>true</code> caso a construção do modelo tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool evaluate(
					IN Matrix *dataMatrix, 
					IN OUT Matrix **hipothesis, 
					IN bool debug = false) {

				// determina se a matriz é válida
				if (pel216::commons::Utils::isInvalidHandle(dataMatrix)) {
					throw new IllegalParameterException();
				}

				// verifica se o modelo é válido
				if (pel216::commons::Utils::isInvalidHandle(this->model)) {
					throw new IllegalParameterException();
				}

				// verifica se o modelo é válido
				if (pel216::commons::Utils::isInvalidHandle(this->classStats)) {
					throw new IllegalParameterException();
				}

				// verifica se o modelo é válido
				size_t columns = dataMatrix->getColumns();
				if (dataMatrix->getRows() != 1 || columns > this->model->size() - 1) {
					throw new IllegalParameterException();
				}

				// calcula as hipóteses de cada característica
				for (size_t colIdx = 0; colIdx < columns; colIdx++) {
					buildFeatureHipothesis(dataMatrix, colIdx, &(*hipothesis));
				}

				// aplica a hipótese da classe
				for (size_t classIdx = 0; classIdx < classStats->getRows(); classIdx++) {
					(*hipothesis)->data()[classIdx][1] *= classStats->data()[classIdx][3];
				}

				if (debug) {
					(*hipothesis)->dump("hipoteses");
				}

				return true;
				
			};

		}; /* class NaiveBayes */

	} /* namespace week4 */

} /* namespace pel208 */

#endif /* __NAIVE_BAYES_METHOD_H__ */
