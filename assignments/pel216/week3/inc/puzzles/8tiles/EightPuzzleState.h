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

		// quantidade de opções para o quebra cabeças
		static const size_t EIGHT_PUZZLE_STATE_LENGTH = 9;

		static const char *RIGHT 	= "right";
		static const char *LEFT 	= "left";
		static const char *UP 		= "up";
		static const char *DOWN 	= "down";

		static const char *DIRECTIONS[] = {RIGHT, LEFT, UP, DOWN, NULL};
		static std::map<const char *, std::vector<int> > NAVIGATION_MAP;
		static std::map<const char *, int> MOVES;
		
		#define NAVMAP_MAP_PAIR(a,b)(std::pair<const char*, std::vector<int> >(a, b))
		#define MOVES_MAP_PAIR(a,b)	(std::pair<const char*, int>(a, b))

		static const int H_MISPLACED_BLOCKS		= 0;
		static const int H_MANHATTAN_DISTANCE	= 1;

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
		 * Classe que representa um estado do jogo de 8 peças (8 puzzle).
		 *
		 * @author arrebola
		 */
		class EightPuzzleState : public State< std::vector<int> > {

		private:
			std::vector<EightPuzzleState*> children;

			/**
			 * Inicializa as variáveis estáticas dessa classe.
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
			 * Determina se o dado é válido.
			 *
			 * @param data
			 * 				o <code>std::vector<int></code> que representa o dado
			 *
			 * @return <code>true</code> caso o dado seja válido; do contrário <code>false</code>
			 */
			static bool isValidData(IN std::vector<int> data) {
				return (pel216::commons::Utils::isValidHandle(&data) && (data.size() == EIGHT_PUZZLE_STATE_LENGTH));
			};

			/**
			 * Obtém o índice de uma peça.
			 *
			 * @param tile
			 * 				o <code>int</code> que representa o número da
			 *
			 * @return o <code>size_t</code> que representa a posição da peça
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
			 * Cria um novo estado a partir da movimentação do espaço em branco.
			 *
			 * @param blankFoundAt
			 * 				o <code>int</code> que indica a posição em que o espaço em branco se encontra
			 * @param moveToDirecton
			 * 				o <code>char *</code> que representa a nova posição do espaço em branco
			 *
			 * @return o <code>std:vector<int</code> que representa o novo estado
			 */
			std::vector<int> newState(int blankFoundAt, const char *moveToDirection) {

				// o novo estado é derivado do estado atual
				std::vector<int> newStateData(this->getData());

				// a nova posição do espaço em branco é determinada pelo mapa de movimentos
			    size_t blankNewIndex = blankFoundAt + MOVES[moveToDirection];

			    // antes de movimentar o espaço em branco é preciso colocar uma peça no lugar
			    newStateData[blankFoundAt] = this->getData()[blankNewIndex];

			    // agora, o espaço em branco pode assumir a nova posição
			    newStateData[blankNewIndex] = 0;

			    // e o novo estado está definido
				return newStateData;

			};

			/**
			 * Retorna a quantidade de blocos fora de posição comparando o estado atual com o estado informado.
			 *
			 * @param goal
			 * 					o <code>EightPuzzleState*</code> que representa o alvo
			 *
			 * @return o <code>size_t</code> que representa a quantidade de blocos fora de posição
			 */
			size_t getMisplacedBlocksCount(EightPuzzleState *goal) {

				size_t misplacedBlocksCount = 0;
				
				register std::vector<int> goalData = goal->getData();
				for (size_t idx = 0; idx < EIGHT_PUZZLE_STATE_LENGTH; idx++) {
					if (this->getData()[idx] != goalData[idx]) {
						misplacedBlocksCount++;
					}
				}

				return misplacedBlocksCount;

			};

			/**
			 * Obtém a distância <i>Manhattan</i> de todos os blocos de um estado.
			 *
			 * @param goal
			 * 					o <code>EightPuzzleState*</code> que representa o alvo
			 *
			 * @return o <code>size_t</code> que representa a distância Manhattan de todos os blocos
			 */
			size_t getManhattanDistance(EightPuzzleState *goal) {

				size_t manhattanDistance = 0;

				register std::vector<int> goalData = goal->getData();
				for (size_t idx = 0; idx < EIGHT_PUZZLE_STATE_LENGTH; idx++) {
					register int tile = this->getData()[idx];
					if (tile != goalData[idx]) {
						size_t indexOf = goal->indexOf(tile);
						manhattanDistance += std::abs((int)((idx / 3) - (indexOf / 3))) + std::abs((int)((idx % 3) - (indexOf % 3)));
					}
				}

				return manhattanDistance;

			};

		public:
			/**
			 * Construtor padrão.
			 */
			EightPuzzleState() : State() {
			};


			/**
			 * Construtor.
			 *
			 * @param data
			 * 				o <code>std::vector<int></code> que representa o estado
			 *
			 * @throws {@link IllegalParameterException} caso o dado seja inválido
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
			 * Expande o estado atual para todos os estados possíveis, considerando a variação da posição do espaço em branco.
			 *
			 * @see pel216::week3::State::expand()
			 */
			virtual void expand() {

				size_t blankFoundAt = this->indexOf(0);

				int idx = 0;
				while (DIRECTIONS[idx]) {

					// determina se o movimento é permitido
					if (NAVIGATION_MAP[DIRECTIONS[idx]][blankFoundAt] == 1) {
						this->children.push_back(new EightPuzzleState(newState(blankFoundAt, DIRECTIONS[idx])));
					}
					idx++;

				}

			};

			/**
			 * Obtém os estados filhos.
			 *
			 * @return o <code>std:vector</code> de @link{EightPuzzleState} que representa o vetor de estados filhos
			 */
			std::vector<EightPuzzleState*> getChildren() {
				return this->children;
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
			 * Obtém a heurística do nó em relação a um estado informado.
			 * 
			 * @param goal
			 * 				o <code>EightPuzzleState*</code> que representa o alvo
			 * @param heuristicType
			 *				o <codfe>int</code> que representa o tipo da heurística	
			 *
			 * @return o <code>size_t</code> que representa a quantidade de blocos fora de posição
			 */
			size_t h(IN EightPuzzleState *goal, IN int heuristicType = H_MISPLACED_BLOCKS) {

				if (pel216::commons::Utils::isInvalidHandle(goal)) {
					throw new pel216::commons::IllegalParameterException();
				}

				size_t heuristic = 0;
				switch (heuristicType) {
					case H_MANHATTAN_DISTANCE:
						heuristic = getManhattanDistance(goal);
						break;
					default:
						heuristic = getMisplacedBlocksCount(goal);
						break;
				}

				return heuristic;

			};

			/**
			 * Determina se o estado atual é igual ao informado.
			 *
			 * @param state
			 * 					o <code>EightPuzzleState*</code> que representa o estado
			 *
			 * @return <code>true</code> caso o estado atual seja igual ao estado informado; do contrário <code>false</code>
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
