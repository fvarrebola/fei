#pragma once

#ifndef __EIGHTPUZZLESTATE_H__
#define __EIGHTPUZZLESTATE_H__

#include <cstdarg>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include <inc/puzzles/State.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week3 {

		// quantidade de op�ões para o quebra cabe�as
		static const size_t EIGHT_PUZZLE_STATE_LENGTH = 9;

		static const char *RIGHT 	= "right";
		static const char *LEFT 	= "left";
		static const char *UP 		= "up";
		static const char *DOWN 	= "down";

		static const char *DIRECTIONS[] = {RIGHT, LEFT, UP, DOWN, NULL};
		static std::map<const char *, std::vector<int> > NAVIGATION_MAP;
		#define NAVMAP_MAP_PAIR(a,b)			(std::pair<const char*, std::vector<int> >(a, b))

		static std::map<const char *, int> MOVES;
		#define MOVES_MAP_PAIR(a,b)			(std::pair<const char*, int>(a, b))

		/**
		 * Preenche um vetor com um conjunto de valores <code>int</code>.
		 *
		 * @param size
		 * 				o <code>size_t</code> que representa o tamanho do vetor
		 * @param values
		 * 				o vararg de <code>int</code> que representa o conjunto de valores
		 *
		 * @return o <code>std::vector<int></code> que representa o vetor.
		 */
		inline std::vector<int> initVector(IN size_t vectorSize, IN int values, ...) {

			std::vector<int> vector(vectorSize);

			va_list varArgs;

			va_start(varArgs, values);

			vector[0] = values;
			for (size_t idx = 1; idx < vectorSize; idx++) {
			    vector[idx] = va_arg(varArgs, int);
			}

			va_end(varArgs);

			return vector;

		};


		/**
		 * Classe que representa um estado do jogo de 8 pe�as (8 puzzle).
		 *
		 * @author arrebola
		 */
		class EightPuzzleState : public State< std::vector<int> > {

		private:
			/**
			 * Inicializa as vari�veis est�ticas dessa classe.
			 */
			static void initStaticVariables() {

				NAVIGATION_MAP.insert(NAVMAP_MAP_PAIR(RIGHT,
						initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 1, 0, 1, 1, 0, 1, 1, 0)));
				NAVIGATION_MAP.insert(NAVMAP_MAP_PAIR(LEFT,
						initVector(EIGHT_PUZZLE_STATE_LENGTH, 0, 1, 1, 0, 1, 1, 0, 1, 1)));
				NAVIGATION_MAP.insert(NAVMAP_MAP_PAIR(UP,
						initVector(EIGHT_PUZZLE_STATE_LENGTH, 0, 0, 0, 1, 1, 1, 1, 1, 1)));
				NAVIGATION_MAP.insert(NAVMAP_MAP_PAIR(DOWN,
						initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 1, 1, 1, 1, 1, 0, 0, 0)));

				MOVES.insert(MOVES_MAP_PAIR(RIGHT, 1));
				MOVES.insert(MOVES_MAP_PAIR(LEFT, -1));
				MOVES.insert(MOVES_MAP_PAIR(UP,   -3));
				MOVES.insert(MOVES_MAP_PAIR(DOWN,  3));

			};

			/**
			 * Determina se o dado � v�lido.
			 *
			 * @param data
			 * 				o <code>std::vector<int></code> que representa o dado
			 *
			 * @return <code>true</code> caso o dado seja v�lido; do contr�rio <code>false</code>
			 */
			static bool isValidData(IN std::vector<int> data) {
				return (pel216::commons::Utils::isValidHandle(&data) && (data.size() == EIGHT_PUZZLE_STATE_LENGTH));
			};

			/**
			 * Obt�m o �ndice de uma pe�a.
			 *
			 * @param tile
			 * 				o <code>int</code> que representa o n�mero da
			 *
			 * @return o <code>size_t</code> que representa a posi��o da pe�a
			 */
			size_t indexOf(int tile) {

				size_t index = -1;
				bool found = false;
				for (size_t idx = 0; idx < EIGHT_PUZZLE_STATE_LENGTH && !found; idx++) {
					if (this->getData()[idx] == tile) {
						index = idx;
						found = true;
					}
				}
				return index;
			};

			/**
			 * Cria um novo estado a partir da movimenta��o do espa�o em branco.
			 *
			 * @param blankFoundAt
			 * 				o <code>int</code> que indica a posi��o em que o espa�o em branco se encontra
			 * @param moveToDirecton
			 * 				o <code>char *</code> que representa a nova posi��o do espa�o em branco
			 *
			 * @return o <code>std:vector<int</code> que representa o novo estado
			 */
			std::vector<int> newState(int blankFoundAt, const char *moveToDirection) {

				// o novo estado � derivado do estado atual
				std::vector<int> newStateData(this->getData());

				// a nova posi��o do espa�o em branco � determinada pelo mapa de movimentos
			    size_t blankNewIndex = blankFoundAt + MOVES[moveToDirection];

			    // antes de movimentar o espa�o em branco � preciso colocar uma pe�a no lugar
			    newStateData[blankFoundAt] = this->getData()[blankNewIndex];

			    // agora, o espa�o em branco pode assumir a nova posi��o
			    newStateData[blankNewIndex] = 0;

			    // e o novo estado est� definido
				return newStateData;

			};

		public:
			/**
			 * Construtor padr�o.
			 */
			EightPuzzleState() : State() {
			};


			/**
			 * Construtor.
			 *
			 * @param data
			 * 				o <code>std::vector<int></code> que representa o estado
			 *
			 * @throws {@link IllegalParameterException} caso o dado seja inv�lido
			 */
			EightPuzzleState(IN std::vector<int> data) : State() {

				if (!isValidData(data)) {
					throw new pel216::commons::IllegalParameterException();
				}

				initStaticVariables();
				this->setData(data);

			};

			/**
			 * Destrutor.
			 */
			~EightPuzzleState() {
			};

			/**
			 * Expande o estado atual para todos os estados poss�veis, considerando a varia��o da posi��o do espa�o em branco.
			 *
			 * @see pel216::week3::State::expand()
			 */
			virtual void expand() {

				std::vector<std::vector<int> > expandedData;

				size_t blankFoundAt = this->indexOf(0);

				int idx = 0;
				while (DIRECTIONS[idx]) {

					// determina se o movimento � permitido
					if (NAVIGATION_MAP[DIRECTIONS[idx]][blankFoundAt] == 1) {
						expandedData.push_back(newState(blankFoundAt, DIRECTIONS[idx]));
					}
					idx++;

				}

				this->setExpandedData(expandedData);

			};

			/**
			 * @see pel216::week3::State::hashCode()
			 */
			virtual std::string hashCode() {

				std::stringstream stream;

				for (size_t idx = 0; idx < EIGHT_PUZZLE_STATE_LENGTH; idx++) {
					stream << this->getData()[idx];
				}

				return stream.str();

			};

			/**
			 * Retorna a quantidade de blocos fora de posi��o comparando o estado atual com o estado informado.
			 *
			 * @param state
			 * 					o <code>EightPuzzleState*</code> que representa o estado
			 *
			 * @return o <code>size_t</code> que representa a quantidade de blocos fora de posi��o
			 */
			size_t getMisplacedBlocksCount(EightPuzzleState *state) {

				size_t misplacedBlocksCount = 0;
				for (size_t idx = 0; idx < EIGHT_PUZZLE_STATE_LENGTH; idx++) {
					if (this->getData()[idx] != state->getData()[idx]) {
						misplacedBlocksCount++;
					}
				}

				return misplacedBlocksCount;

			};


			/**
			 * Determina se o estado atual � igual ao informado.
			 *
			 * @param state
			 * 					o <code>EightPuzzleState*</code> que representa o estado
			 *
			 * @return <code>true</code> caso o estado atual seja igual ao estado informado; do contr�rio <code>false</code>
			 */
			bool equals(EightPuzzleState *state) {
				return (getMisplacedBlocksCount(state) == 0);
			};

			/**
			 * @see pel216::week3::State::toString()
			 */
			virtual std::string toString() {

				std::stringstream stream;

				stream << "[";
				for (size_t idx = 0; idx < EIGHT_PUZZLE_STATE_LENGTH; idx++) {
					stream << this->getData()[idx];
					if (idx < EIGHT_PUZZLE_STATE_LENGTH - 1) {
						stream << ", ";
					}
				}

				stream << "]";

				return stream.str();

			};

		}; /* class EightPuzzleState */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __EIGHTPUZZLESTATE_H__ */
