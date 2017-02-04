#pragma once

#ifndef __LDA_METHOD_H__
#define __LDA_METHOD_H__

#include <map>
#include <string>

#include <inc/Matrix.h>
#include <inc/Jacobi.h>

using namespace pel208::commons;
using namespace pel208::week2;

namespace pel208 {

	namespace week3 {

		class LDAClassDataSet {
		private:
			std::string name;
			size_t samples;
			size_t maxSamples;
			size_t maxDimensions;
			Matrix *matrix;
			Matrix *mean;
			Matrix *adjusted;
			Matrix *covariate;

			void shrink() {
				this->matrix->shrink(samples);
			};

		public:
			
			LDAClassDataSet(std::string name, size_t maxSamples, size_t maxDimensions) {
				this->name = name;
				this->matrix = new Matrix(maxSamples, maxDimensions);
				this->maxSamples = maxSamples;
				this->maxDimensions = maxDimensions;
				this->samples = 0;
			};

			~LDAClassDataSet() {
				if (pel216::commons::Utils::isValidHandle(covariate)) {
					delete covariate;
					delete adjusted;
					delete mean;
				}
				delete this->matrix;
			}

			void addNDimensionalSample(double values[], size_t skipColumn = 0) {
				size_t colIdx = 0;
				for (size_t idx = 0; idx < this->maxDimensions + 1; idx++) {
					if (idx == skipColumn) {
						continue;
					}
					this->matrix->data()[this->samples][colIdx++] = values[idx];
				}
				this->samples++;
			};

			bool evaluateMeanAndCov() {
				this->shrink();
				this->mean = this->matrix->mean();
				this->covariate = this->matrix->covariate(&adjusted);
				return (pel216::commons::Utils::isValidHandle(covariate));
			};
			
			Matrix *getMean() {
				return this->mean;
			};
			
			Matrix *getAdjusted() {
				return this->adjusted;
			};

			Matrix *getCovariate() {
				return this->covariate;
			};

		};


		/**
		 * Implementação do método LDA.<br />
		 *
		 * @author arrebola
		 */
		class LDAMethod {
		private:
			typedef std::map<std::string, LDAClassDataSet*>::iterator it_type;

			/**
			 * Inicializa o <code>std::map</code> de amostras por classe.<br />
			 *
			 * @param dataMatrix
			 *				o Matrix que representa a matriz com as entradas que se quer analisar
			 * @param classColumnIdx
			 *				o <code>size_t</code> que indica o índice da coluna que representa a classe
			 * @param map
			 *				o <code>std::map</code> que representa as amostras por classe
			 *
			 * @return <code>true</code> caso a inicialização seja bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool initDataByClassMap(
					IN Matrix *dataMatrix, 
					IN size_t classColumnIdx, 
					OUT std::map<std::string, LDAClassDataSet*> **map) {
			
				// determina se a matriz é válida
				if (pel216::commons::Utils::isInvalidHandle(dataMatrix)) {
					throw new IllegalParameterException();
				}

				size_t maxSamples = dataMatrix->getRows();
				size_t maxDimensions = dataMatrix->getColumns() - 1;

				*map = new std::map<std::string, LDAClassDataSet*>();
				Matrix *classes = dataMatrix->unique(classColumnIdx);
				size_t classCount = classes->getRows();
				for (size_t idx = 0; idx < classCount; idx++) {
					register std::string classId = std::to_string(classes->data()[idx][0]);
					(*map)->insert(
						std::pair<std::string, LDAClassDataSet*>(
							classId, 
							new LDAClassDataSet(classId, maxSamples, maxDimensions)));
				}

				delete classes;

				return true;
			
			};

			/**
			 * Calcula a média a covariância das classes contidas no <code>std::map</code>.<br />
			 *
			 * @param dataMatrix
			 *				o Matrix que representa a matriz com as entradas que se quer analisar
			 * @param classColumnIdx
			 *				o <code>size_t</code> que indica o índice da coluna que representa a classe
			 * @param map
			 *				o <code>std::map</code> que representa as amostras por classe
			 *
			 * @return <code>true</code> caso a distribuição seja bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool distributeSamples(
					IN Matrix *dataMatrix, 
					IN size_t classColumnIdx, 
					IN OUT std::map<std::string, LDAClassDataSet*> **map) {

				// determina se a matriz é válida
				if (pel216::commons::Utils::isInvalidHandle(dataMatrix)) {
					throw new IllegalParameterException();
				}

				// determina se o mapa é válido
				if (pel216::commons::Utils::isInvalidHandle(*map)) {
					throw new IllegalParameterException();
				}

				size_t samples = dataMatrix->getRows();
				size_t classCount = (*map)->size();
				
				for (size_t rowIdx = 0; rowIdx < samples; rowIdx++) {
					register std::string classId = std::to_string(dataMatrix->data()[rowIdx][classColumnIdx]);
					(*map)->at(classId)->addNDimensionalSample(dataMatrix->data()[rowIdx], classColumnIdx);
				}

				return true;
			};

			/**
			 * Calcula a média a covariância das classes contidas no <code>std::map</code>.<br />
			 *
			 * @param map
			 *				o <code>std::map</code> que representa as amostras por classe
			 * @param overallMean
			 *				o Matrix que representa as médias gerais (independentes de classe)
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return <code>true</code> caso o cálculo seja bem sucedido; do contrário <code>false</code>
			 */
			PRIVATE static bool evaluateMeanAndCov(
					IN std::map<std::string, LDAClassDataSet*> *map, 
					IN OUT Matrix **overallMean,
					IN bool debug = false) {

				// determina se o mapa é válido
				if (pel216::commons::Utils::isInvalidHandle(map)) {
					throw new IllegalParameterException();
				}

				// determina se a matriz é válida
				if (pel216::commons::Utils::isInvalidHandle(*overallMean)) {
					throw new IllegalParameterException();
				}

				for (it_type iterator = map->begin(); iterator != map->end(); iterator++) {
					
					register std::string className = iterator->first;
					register LDAClassDataSet *ldaClass = iterator->second;
					
					ldaClass->evaluateMeanAndCov();

					Matrix *mean = ldaClass->getMean();
					Matrix *covariate = ldaClass->getCovariate();

					if (debug) {
						mean->dump(std::string("mean^T for class '").append(className).append("'"));
						covariate->dump(std::string("covariate for class '").append(className).append("'"));
					}

					(*overallMean)->sum(mean, &(*overallMean));
				
				}

				// divisão pela quantidade de classes
				*overallMean = (*overallMean)->divide(map->size());

				if (debug) {
					(*overallMean)->dump("overall mean");
				}

				return true;

			};

			/**
			 * Calcula a matriz <code>within</code> das classes contidas no <code>std::map</code>.<br />
			 *
			 * @param map
			 *				o <code>std::map</code> que representa as amostras por classe
			 * @param withinClassMatrix
			 *				o Matrix que representa a matriz <code>within</code>
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return <code>true</code> caso o cálculo seja bem sucedido; do contrário <code>false</code>
			 */
			PRIVATE static bool evaluateWithinClassMatrix(
					IN std::map<std::string, LDAClassDataSet*> *map, 
					OUT Matrix **withinClassMatrix,
					IN bool debug = false) {

				// determina se a matriz é válida
				if (pel216::commons::Utils::isInvalidHandle(map)) {
					throw new IllegalParameterException();
				}

				for (it_type iterator = map->begin(); iterator != map->end(); iterator++) {
					register LDAClassDataSet *ldaClass = iterator->second;
					(*withinClassMatrix)->sum(ldaClass->getCovariate(), &(*withinClassMatrix));
				}

				if (debug) {
					(*withinClassMatrix)->dump("within class");
				}

				return true;

			};

			/**
			 * Calcula a matriz <code>within</code> das classes contidas no <code>std::map</code>.<br />
			 *
			 * @param map
			 *				o <code>std::map</code> que representa as amostras por classe
			 * @param overallBetweenClassMatrix
			 *				o Matrix que representa a matriz <code>within</code>
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return <code>true</code> caso o cálculo seja bem sucedido; do contrário <code>false</code>
			 */
			PRIVATE static bool evaluateBetweenClassMatrix(
					IN std::map<std::string, LDAClassDataSet*> *map, 
					IN Matrix *overallMean,
					OUT Matrix **overallBetweenClassMatrix,
					IN bool debug = false) {

				// determina se a matriz é válida
				if (pel216::commons::Utils::isInvalidHandle(map)) {
					throw new IllegalParameterException();
				}

				for (it_type iterator = map->begin(); iterator != map->end(); iterator++) {
					
					register LDAClassDataSet *ldaClass = iterator->second;
					
					Matrix *meanMinusOveral = NULL;
					ldaClass->getMean()->minus(overallMean, &meanMinusOveral);
					
					Matrix *meanMinusOveralT = meanMinusOveral->transpose();
					Matrix *meanMinusOveralT_X_MeanMinusOveral = meanMinusOveralT->multiply(meanMinusOveral);
					Matrix *betweenClassMatrix = meanMinusOveralT_X_MeanMinusOveral->multiply(overallMean->getColumns());

					(*overallBetweenClassMatrix)->sum(betweenClassMatrix, &(*overallBetweenClassMatrix));

					delete betweenClassMatrix;
					delete meanMinusOveralT_X_MeanMinusOveral;
					delete meanMinusOveralT;
					delete meanMinusOveral;
				
				}

				if (debug) {
					(*overallBetweenClassMatrix)->dump("between class");	
				}

				return true;

			};

		public:
			/**
			 * Construtor.
			 */
			LDAMethod() {
			};

			/**
			 * Executa o método LDA.<br />
			 *
			 * @param dataMatrix
			 *				o Matrix que representa a matriz com as entradas que se quer analisar
			 * @param classColumnIdx
			 *				o <code>size_t</code> que indica o índice da coluna que representa a classe
			 * @param eigenValues
			 *				o Matrix que representa a matriz de autovalores
			 * @param eigenVectors
			 *				o Matrix que representa a matriz de autovetores
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return o <code>double</code> que representa o valor encontrado para o alvo
			 */
			PUBLIC static bool evaluate(
					IN Matrix *dataMatrix,
					IN size_t classColumnIdx,
					OUT Matrix **eigenValues,
					OUT Matrix **eigenVectors,
					IN bool debug = false) {

				bool result = false;

				// determina se a matriz é válida
				if (pel216::commons::Utils::isInvalidHandle(dataMatrix)) {
					throw new IllegalParameterException();
				}

				// verifica se o índice da coluna de classificação é válido
				if (classColumnIdx > dataMatrix->getColumns()) {
					throw new IllegalParameterException();
				}

				// a quantidade de amostras e suas dimensões
				size_t samples = dataMatrix->getRows();
				size_t dimensions = dataMatrix->getColumns() - 1;

				// obtém a classes e inicializa matrizes separadas para cada uma
				std::map<std::string, LDAClassDataSet*> *dataByClassMap = NULL;
				initDataByClassMap(dataMatrix, classColumnIdx, &dataByClassMap);
				
				// analisa as amostras e distribui por classes
				distributeSamples(dataMatrix, classColumnIdx, &dataByClassMap);

				// calcula as médias e a covariância de cada classe
				Matrix *M = new Matrix(1, dimensions);
				evaluateMeanAndCov(dataByClassMap, &M, debug);

				// calcula a withinclass 
				Matrix *SW = new Matrix(dimensions);
				evaluateWithinClassMatrix(dataByClassMap, &SW, debug);

				// calcula a betweenclass 
				Matrix *SB = new Matrix(dimensions);
				evaluateBetweenClassMatrix(dataByClassMap, M, &SB, debug);
				delete M;

				// calcula as projeções LDA
				Matrix *invSW = NULL;
				SW->invert(&invSW);

				Matrix *invSW_by_SB = NULL;
				invSW_by_SB = invSW->multiply(SB);

				if (debug) {
					invSW->dump("projecoes LDA (Sw^-1)");
					invSW_by_SB->dump("projecoes LDA (Sw^-1 * Sb)");
				}

				delete SW;
				delete invSW;
				delete SB;

				// calcula os autovalores e autovetores
				if (Jacobi::evaluate(invSW_by_SB, &(*eigenValues), &(*eigenVectors), dimensions)) {
					if (debug) {
						(*eigenValues)->dump("auto valores");
						(*eigenVectors)->dump("auto vetores");
					}
					result = true;
				}

				delete invSW_by_SB;
				delete dataByClassMap;

				return result;

			};

		}; /* class LDAMethod */

	} /* namespace week3 */

} /* namespace pel208 */

#endif /* __LDA_METHOD_H__ */
