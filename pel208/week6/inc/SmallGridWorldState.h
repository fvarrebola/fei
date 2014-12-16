#pragma once

#ifndef __SMALL_GRID_WORLD_STATE_H__
#define __SMALL_GRID_WORLD_STATE_H__

#include <inc\Utils.h>
#include <inc\Matrix.h>
#include <inc\Random.h>
#include <inc\ex\IllegalParameterException.h>

#include <inc\RLConstants.h>

#define ALLOWED_ACTIONS_QTY							4

#define NEXT_STATE_COMPLETE_INFO_MATRIX_ROWS		3
#define NEXT_STATE_IDX								0
#define TRANSITION_PROBABILITY_IDX					1
#define TRANSITION_REWARD_IDX						2

using namespace pel208::commons;

namespace pel208 {

	namespace week6 {

		/**
		 * Classe que representa um estado do <i>small grid world</i>.<br />
		 *
		 * @author arrebola
		 */
		class SmallGridWorldState {

		private:
			size_t stateIdx;
			Matrix *nextStatesCompleteInfo;
			Matrix *nextStates;
			Matrix *transitionProbabilities;
			Matrix *transitionRewards;

			Matrix *Q;
			Matrix *E;

			double stateValue_V;

			/**
			 * Atualiza uma célula de uma matriz.<br />
			 *
			 * @param matrix
			 *					o Matrix a ser atualizada
			 * @param rowIdx
			 *					o índice da linha
			 * @param colIdx
			 *					o índice da coluna
			 * @param value
			 *					o valor
			 */
			PRIVATE static void updateMatrix(IN Matrix *matrix, IN size_t rowIdx, IN size_t colIdx, IN double value) {
				matrix->data()[rowIdx][colIdx] = value;
			};

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o mundo
			 * @para stateIdx
			 *					o <code>size_t</code> que representa o estado
			 * @param nextStatesCompleteInfo
			 *					o Matrix de informações sobre os próximos estados
			 */
			SmallGridWorldState(IN size_t stateIdx, IN Matrix *nextStatesCompleteInfo, IN bool initQ = true) {
				
				if (Utils::isInvalidHandle(nextStatesCompleteInfo)) {
					throw new IllegalParameterException();
				}

				if (nextStatesCompleteInfo->getRows() != NEXT_STATE_COMPLETE_INFO_MATRIX_ROWS || 
							nextStatesCompleteInfo->getColumns() != ALLOWED_ACTIONS_QTY) {
					throw new IllegalParameterException();
				}

				this->stateIdx = stateIdx;
				this->nextStatesCompleteInfo = nextStatesCompleteInfo->clone();

				// inicializa as matrizes auxiliares, que serão atualizadas conforme o algoritmo
				this->nextStates = new Matrix(1, ALLOWED_ACTIONS_QTY);
				this->transitionProbabilities = new Matrix(1, ALLOWED_ACTIONS_QTY, DEFAULT_TRANSITION_PROBABILITY);
				this->transitionRewards = new Matrix(1, ALLOWED_ACTIONS_QTY, DEFAULT_ACTION_REWARD);
				for (size_t colIdx = 0; colIdx < ALLOWED_ACTIONS_QTY; colIdx++) {
					this->nextStates->data()[0][colIdx] = this->nextStatesCompleteInfo->data()[0][colIdx];
					this->transitionProbabilities->data()[0][colIdx] = this->nextStatesCompleteInfo->data()[1][colIdx];
					this->transitionRewards->data()[0][colIdx] = this->nextStatesCompleteInfo->data()[2][colIdx];
				}

				this->stateValue_V = 0.0f;

				if (initQ) {
					this->Q = new Matrix(1, ALLOWED_ACTIONS_QTY);
					if (stateIdx > 0 && stateIdx < 15) {
						this->Q->randomFill(ZERO, ONE);
					}
				}

				this->E = new Matrix(1, ALLOWED_ACTIONS_QTY);

			};

			/**
			 * Destrutor.<br />
			 */
			~SmallGridWorldState() {

				if (Utils::isValidHandle(this->nextStates)) {
					delete this->nextStates;
				}

				if (Utils::isValidHandle(this->transitionProbabilities)) {
					delete this->transitionProbabilities;
				}
				
				if (Utils::isValidHandle(this->transitionRewards)) {
					delete this->transitionRewards;
				}
				
				if (Utils::isValidHandle(this->nextStatesCompleteInfo)) {
					delete this->nextStatesCompleteInfo;
				}

				if (Utils::isValidHandle(this->Q)) {
					delete this->Q;
				}

				if (Utils::isValidHandle(this->E)) {
					delete this->E;
				}
			};

			/**
			 * Clona um estado.<br />
			 *
			 * @return o SmallGridWorldState que representa o estado
			 */
			PUBLIC SmallGridWorldState *clone() {
				
				SmallGridWorldState *clone = new SmallGridWorldState(
						this->stateIdx, 
						this->nextStatesCompleteInfo,
						false);
				
				clone->setValue(this->getValue());
				clone->updateTransitionProbabilities(this->transitionProbabilities);
				clone->Q = this->Q->clone();

				return clone;

			};

			/**
			 * Obtém o índice do estado.<br />
			 *
			 * @return o <code>size_t</code> que representa o índice do estado
			 */
			PUBLIC size_t getStateIdx() {
				return this->stateIdx;
			};
			
			/**
			 * Obtém o valor V de um estado.<br />
			 *
			 * @return o <code>double</code> que representa o valor
			 */
			PUBLIC double getValue() {
				return this->stateValue_V;
			};

			/**
			 * Configura o valor V de um estado.<br />
			 *
			 * @param value
			 *					o <code>double</code> que representa o valor
			 */
			PUBLIC void setValue(IN double value) {
				this->stateValue_V = value;
			};

			/**
			 * Obtém a matriz de próximos estados.<br />
			 *
			 * @return o Matrix de informações sobre os próximos estados
			 */
			PUBLIC Matrix *getNextStates() {
				return this->nextStates;
			};
			
			/**
			 * Obtém a matriz de probabilidades de transição para os próximos estados.<br />
			 *
			 * @return o Matrix de probabilidades de transição para os próximos estados
			 */
			PUBLIC Matrix *getTransitionProbabilities() {
				return this->transitionProbabilities;
			};

			/**
			 * Obtém a matriz de recompensas de transição para os próximos estados.<br />
			 *
			 * @return o Matrix de recompensas de transição para os próximos estados
			 */
			PUBLIC Matrix *getTransitionRewards() {
				return this->transitionRewards;
			};

			/**
			 * Obtém a matriz Q.<br />
			 *
			 * @return o Matrix Q
			 */
			PUBLIC Matrix *getQ() {
				return this->Q;
			};

			/**
			 * Obtém a matriz E.<br />
			 *
			 * @return o Matrix E
			 */
			PUBLIC Matrix *getE() {
				return this->E;
			};
			
			/**
			 * Obtém o valor máximo de Q(s, a) de um estado.<br />
			 *
			 * @return <code>true</code> caso a operação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool getMaxQValue(OUT double *max) {
				return this->getQ()->max(&(*max));
			};

			/**
			 * Atualiza a matriz de probabilidades de transição para os próximos estados.<br />
			 *
			 * @param matrix
			 *					o Matrix de probabilidades de transição para os próximos estados
			 */
			PUBLIC void updateTransitionProbabilities(IN Matrix *matrix) {

				if (Utils::isInvalidHandle(matrix)) {
					throw new IllegalParameterException();
				}

				size_t rows = matrix->getRows();
				size_t columns = matrix->getColumns();

				if (rows != this->transitionProbabilities->getRows() || 
						columns != this->transitionProbabilities->getColumns()) {
					throw new IllegalParameterException();
				}

				for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) {
					updateMatrix(this->transitionProbabilities, 0, idx, matrix->data()[0][idx]);
				}

			};

			/**
			 * Imprime detalhes sobre o estado.<br />
			 *
			 * @param dumpToFile
			 *					indica se os valores de devem ser impressos em arquivo
			 */
			PUBLIC void dump(IN bool dumpToFile = false) {

				if (dumpToFile) {
					Logger::logToFile("%3d %8.2f  ", this->stateIdx, this->getValue());
				} else {
					Logger::log("%3d %8.2f  ", this->stateIdx, this->getValue());
				}

				const char *printPFormat = "%02d=%.2f   ";
				for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) {
					if (dumpToFile) {
						Logger::logToFileWithoutTimestamp(printPFormat, (size_t)this->nextStates->data()[0][idx], this->transitionProbabilities->data()[0][idx]);
					} else {
						Logger::logWithoutTimestamp(printPFormat, (size_t)this->nextStates->data()[0][idx], this->transitionProbabilities->data()[0][idx]);
					}
				}
				
				const char *printQFormat = "%12.6f  ";
				for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) {
					if (dumpToFile) {
						Logger::logToFileWithoutTimestamp(printQFormat, this->getQ()->data()[0][idx]);
					} else {
						Logger::logWithoutTimestamp(printQFormat, this->getQ()->data()[0][idx]);
					}
				}

				if (dumpToFile) {
					Logger::logToFileWithoutTimestamp("\n");
				} else {
					Logger::logWithoutTimestamp("\n");
				}

			};

			/**
			 * Imprime em arquivo os detalhes sobre o estado.<br />
			 */
			PUBLIC void dumpToFile() {
				dump(true);
			};

		}; /* class SmallGridWorldState */

	} /* namespace week6 */

} /* namespace pel208 */

#endif /* __SMALL_GRID_WORLD_STATE_H__ */
