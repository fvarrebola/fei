#pragma once

#ifndef __EIGHTPUZZLENODE_H__
#define __EIGHTPUZZLENODE_H__

#include <vector>

#include <inc/Utils.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Representa um no com estado para o jogo de 8 pe�as.
		 *
		 * @author arrebola
		 */
		class EightPuzzleNode {

		private:
			EightPuzzleState *state; /* representa o estado em si */
			EightPuzzleState *parent; /* representa o estado pai */
			int depth; /* representa a profundidade do n� */
			double heuristic; /* representa o 'custo' do n� */

		public:
			/**
			 * Construtor.
			 *
			 * @param state 
			 *				o @link{EightPuzzleState} que representa o estado atual
			 * @param parent 
			 *				o @link{EightPuzzleState} que representa o estado pai
			 * @param depth
			 *				o <code>double</code> que representa a heur�stica associada ao n�
			 * @param heuristic 
			 *				o <code>double</code> que representa a heur�stica associada ao n�
			 */
			EightPuzzleNode(EightPuzzleState *state, EightPuzzleState *parent = NULL, int depth = 0, double heuristic = 0.0f) {

				this->state = state;
				this->parent = parent;
				this->depth = depth;
				this->heuristic = heuristic;
			
			};

			/**
			 * Destrutor.
			 */
			virtual ~EightPuzzleNode() {
			};

			/**
			 * Retorna o estado atual.
			 *
			 * @return o @link{EightPuzzleState} que representa o estado atual
			 */
			EightPuzzleState *getState() {
				return this->state;
			};
			
			/**
			 * Retorna o estado pai.
			 *
			 * @return o @link{EightPuzzleState} que representa o estado pai
			 */
			EightPuzzleState *getParent() {
				return this->parent;
			};
			
			/**
			 * Retorna a profundidade do n� em rela��o a raiz.
			 *
			 * @return o <code>size_t</code> que representa a profundidade do n�
			 */
			size_t getDepth() {
				return this->depth;
			};
			
			/**
			 * Retorna a heur�stica associada ao n�.
			 *
			 * @return o <code>double</code> que representa a heur�stica associada ao n�
			 */
			double getHeuristic() {
				return this->heuristic;
			};

			/**
			 * Retorna a representa��o da classe.
			 *
			 * @return o <code>std::string</code> que representa a classe
			 */
			std::string toString() {

				std::stringstream stream;

				stream << "[state: " << (this->state == NULL ? UNKNOWN : this->state->toString().c_str());
				stream << ", depth: " << this->depth;
				stream << ", heuristic: " << this->heuristic << "]";

				return stream.str();

			};

		}; /* class EightPuzzleNode */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __EIGHTPUZZLENODE_H__ */
