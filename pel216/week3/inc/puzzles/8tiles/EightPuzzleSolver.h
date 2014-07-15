#pragma once

#ifndef __EIGHTPUZZLESOLVER_H__
#define __EIGHTPUZZLESOLVER_H__

#include <inc/puzzles/Solver.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleBFSSearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleDFSSearchEngine.h>

#include <inc/search/SearchEngine.h>

#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Classe que representa um solucionador do jogo de 8 pe�as (8 puzzle).
		 *
		 * @author arrebola
		 */
		class EightPuzzleSolver : public Solver {

		private:
			EightPuzzleState *initialState; /* o estado inicial */
			EightPuzzleState *goalState; /* o estado final */
			SearchEngine<EightPuzzleNode> *searchEngine;

		public:
			/**
			 * Construtor.
			 *
			 * @param searchEngine
			 * 				o <code>EightPuzzleNode</code> que representa o mecanismo de busca
			 * @param initialState
			 * 				o <code>EightPuzzleState*</code> que representa o estado inicial
			 * @param goalState
			 * 				o <code>EightPuzzleState*</code> que representa o estado final
			 *
			 * @throws {@link IllegalParameterException} caso o dado seja inv�lido
			 */
			EightPuzzleSolver(SearchEngine<EightPuzzleNode> *searchEngine, EightPuzzleState *initialState, EightPuzzleState *goalState) {

				if (pel216::commons::Utils::isInvalidHandle(searchEngine) ||
						pel216::commons::Utils::isInvalidHandle(initialState) ||
							pel216::commons::Utils::isInvalidHandle(goalState)) {
					throw new pel216::commons::IllegalParameterException();
				}

				this->initialState = initialState;
				this->goalState = goalState;

				this->searchEngine = searchEngine;
				this->searchEngine->setStartingNode(
					new EightPuzzleNode(initialState, NULL, 0, initialState->getMisplacedBlocksCount(goalState)));
				this->searchEngine->setGoalNode(new EightPuzzleNode(goalState));

			};

			/**
			 * Destrutor.
			 */
			~EightPuzzleSolver() {
			};

			/**
			 * #see pel216::week3::Solver::solve()
			 */
			virtual void solve() const {

				this->searchEngine->search();

				if (!this->searchEngine->hasFoundSolution()) {
					Logger::log("\n");
					Logger::log("!!!SOLUCAO NAO ENCONTRADA!!!\n");
					Logger::log("\n");
					throw new SolutionNotFoundException();
				}

				std::vector<EightPuzzleNode*> *nodePath = this->searchEngine->getSolutionPath();
				size_t solutionPathLen = nodePath->size();

				Logger::log("Imprimindo movimentos...\n");
				for (size_t idx = 0; idx < solutionPathLen; idx++) {
					Logger::log("> Movimento #%d {%s}\n", (idx + 1), nodePath->at(idx)->getState()->toString().c_str());
				}

			};

		}; /* class EightPuzzleSolver */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __EIGHTPUZZLESOLVER_H__ */
