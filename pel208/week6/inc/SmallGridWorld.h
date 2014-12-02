#pragma once

#ifndef __SMALL_GRID_WORLD_H__
#define __SMALL_GRID_WORLD_H__

#include <vector>

#include <inc\Utils.h>
#include <inc\ex\IllegalParameterException.h>

#include <inc\SmallGridWorldState.h>

using namespace pel216::commons;

namespace pel208 {

	namespace week6 {

		/**
		 * Classe que representa o <i>small grid world</i>.<br />
		 *
		 * @author arrebola
		 */
		class SmallGridWorld {

		private:
			size_t rows;
			size_t stateCount;
			std::vector<SmallGridWorldState*> *states;

			/**
			 * Constrói a matriz de próximos estados.<br />
			 *
			 * @param stateIdx
			 *					o <code>size_t</code> que representa o índice do estado atual
			 *
			 * @return o Matrix que representa a matriz de próximos estados
			 */
			PRIVATE Matrix *buildNextStatesCompleteInfo(IN size_t stateIdx) {
				
				Matrix *matrix = new Matrix(NEXT_STATE_COMPLETE_INFO_MATRIX_ROWS, ALLOWED_ACTIONS_QTY);

				// configura os próximos estados (up, down, left, right)
				matrix->data()[0][0] = (stateIdx < ALLOWED_ACTIONS_QTY) ? stateIdx : (stateIdx - ALLOWED_ACTIONS_QTY);
				matrix->data()[0][1] = (stateIdx < this->stateCount - ALLOWED_ACTIONS_QTY) ? stateIdx + ALLOWED_ACTIONS_QTY : stateIdx;
				matrix->data()[0][2] = (stateIdx % ALLOWED_ACTIONS_QTY == 0) ? stateIdx : stateIdx - 1;
				matrix->data()[0][3] = (stateIdx % ALLOWED_ACTIONS_QTY == 3) ? stateIdx : stateIdx + 1;

				// configura as probabilidades de transição e as recompensas
				for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) {
					matrix->data()[1][idx] = 0.25f;
					matrix->data()[2][idx] = -1.0f;
					if (stateIdx == 0 || stateIdx == this->stateCount - 1) {
						matrix->data()[1][idx] = 0.0f;
						matrix->data()[2][idx] = 0.0f;
					}
				}

				return matrix;

			};

		public:
			/**
			 * Determina se a quantidade de estados é um quadrado perfeito.<br />
			 *
			 * @param stateCount
			 *					o <code>size_t</code> que representa a quantidade de estados
			 * @param root
			 *					o <code>size_t</code> que representa a raiz
			 *
			 * @return <code>true</code> caso a quantidade de estados seja um quadrado perfeito; do contrário <code>false</code>
			 */
			PUBLIC static bool isPerfectSquare(IN size_t stateCount, IN size_t *root) {
				
				*root = 0;
				size_t temp = (*root) * (*root);
				
				while (temp < stateCount) {
					(*root) = (*root) + 1;
					temp = (*root) * (*root);
				}

				return (temp == stateCount);

			};

			/**
			 * Construtor.<br />
			 *
			 * @param stateCount
			 *					o <code>size_t</code> que representa a quantidade de estados
			 * @param initalizeStates
			 *					o <code>bool</code> que indica se os estados devem ser inicializados
			 */
			SmallGridWorld(IN size_t stateCount, IN bool initalizeStates = true) {

				size_t root = 0;
				if (!isPerfectSquare(stateCount, &root)) {
					throw new IllegalParameterException();
				}
				
				this->rows = root;
				this->stateCount = stateCount;

				if (initalizeStates) {
					this->states = new std::vector<SmallGridWorldState*>(this->stateCount);
					for (size_t stateIdx = 0; stateIdx < this->stateCount; stateIdx++) {
						this->states->at(stateIdx) = new SmallGridWorldState(stateIdx, buildNextStatesCompleteInfo(stateIdx));
					}
				}

			};

			/**
			 * Destrutor.<br />
			 */
			~SmallGridWorld() {

				if (Utils::isValidHandle(this->states)) {
					delete this->states;
				}
	
			};

			/**
			 * Clona um <i>small grid world</i>.<br />
			 *
			 * @return o SmallGridWorld que representa o clone
			 */
			PUBLIC SmallGridWorld *clone() {

				SmallGridWorld *clone = new SmallGridWorld(this->stateCount, false);
				clone->states = new std::vector<SmallGridWorldState*>(this->stateCount);
				for (size_t stateIdx = 0; stateIdx < this->stateCount; stateIdx++) {
					clone->states->at(stateIdx) = this->states->at(stateIdx)->clone();
				}
				return clone;

			};

			/**
			 * Obtém a quantidade de linhas do <i>grid</i>.<br />
			 *
			 * @return o <code>size_t</code> que representa a quantidade de linhas
			 */
			PUBLIC size_t getRows() {
				return this->rows;
			};

			/**
			 * Obtém a quantidade de estados do <i>grid</i>.<br />
			 *
			 * @return o <code>size_t</code> que representa a quantidade de estados
			 */
			PUBLIC size_t getStateCount() {
				return this->stateCount;
			};

			/**
			 * Obtém a um estados do <i>grid</i>.<br />
			 *
			 * @return o SmallGridWorldState que representa o estado
			 */
			PUBLIC SmallGridWorldState *getState(IN size_t stateIdx) {
				
				if (stateIdx > this->stateCount - 1) {
					throw new IllegalParameterException();
				}

				return this->states->at(stateIdx);

			};

			/**
			 * Imprime detalhes sobre o <i>grid</i>.
			 */
			PUBLIC void dump(IN bool printP = true, IN bool printQ = true) {

				Logger::log("Imprimindo detalhes sobre o grid...\n");
				Logger::log("#   V         P(U)      P(D)      P(L)      P(R)      Q(U)       Q(D)       Q(L)       Q(R)\n");
				Logger::log("--- --------  --------  --------  --------  --------  ---------  ---------  ---------  ---------\n");
				for (size_t stateIdx = 0; stateIdx < this->stateCount; stateIdx++) {
					this->states->at(stateIdx)->dump(printP, printQ);
				}
			};

		}; /* class SmallGridWorld */

	} /* namespace week6 */

} /* namespace pel208 */

#endif /* __SMALL_GRID_WORLD_H__ */
