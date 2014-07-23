#pragma once

#ifndef __8PUZZLE_BEST_FIRST_SEARCH_H__
#define __8PUZZLE_BEST_FIRST_SEARCH_H__

#include <list>

#include <vector>
#include <map>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/search/SearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleNode.h>

using namespace pel216::commons;
using namespace pel216::week3;

namespace pel216 {

	namespace week4 {

		/**
		 * Classe que representa a busca da melhor opção (<i>best-first-search</i>).
		 *
		 * @author arrebola
		 */
		class EightPuzzleBestFirstSearchEngine : public SearchEngine<EightPuzzleNode> {

		private:
			/**
			 * @see pel216::week3::SearchEngine::expandNode()
			 */
			void expandNode(EightPuzzleNode *node) {

				EightPuzzleState *state = node->getState();

				state->expand();
				this->expandedNodesCount++;

				// avalia cada um dos novos estados

			};

		public:
			/**
			 * Construtor padrão.
			 *
			 * @param maxDepth
			 *				o <code>size_t</code> que representa a profundidade máxima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			EightPuzzleBestFirstSearchEngine(size_t maxDepth = -1, bool debug = false) : SearchEngine("Best First Search") {
				setup(maxDepth, debug);
			};

			/**
			 * @see pel216::week3::SearchEngine::search()
			 */
			virtual void doSearch() {

				this->solutionDepth = 0;
				this->expandedNodesCount = 0;

				EightPuzzleNode *startingNode = getStartingNode();
				EightPuzzleState *initialState = startingNode->getState();
				EightPuzzleNode *goalNode = getGoalNode();
				EightPuzzleState *goalState = goalNode->getState();

				// inicia a lista com o primeiro nó
				list->push_back(startingNode);
				addKnownNode(startingNode);

				size_t iteractions = 1;
				while (list->size() != 0) { 

					EightPuzzleNode *node = list->pop_front();
					EightPuzzleState *state = node->getState();
					
					if (this->debug) {
						Logger::log("\n");
						Logger::log("#%d Visitando no %s...\n", iteractions++, state->toString().c_str());
					}
					// verifica se o alvo foi atingido
					if (state->equals(goalState)) { 

						this->solutionDepth = node->getDepth();

						Logger::log("\n");
						Logger::log("!!! SOLUCAO ENCONTRADA !!! (em profundidade %d apos expandir %d nos)\n", 
							this->solutionDepth, this->expandedNodesCount);
						Logger::log("\n");

						do { /* constrói o caminho da solução */
							addPath(node);
							EightPuzzleState *parentState = node->getParent();
							if (Utils::isInvalidHandle(parentState)) {
								break;
							}
							node = knownNodes->at(parentState->hashCode());
						} while(!initialState->equals(node->getState()));
						
						hasSolution = true;
						break;

					}

					// determina a profundidade máxima foi atingida
					if (node->getDepth() == this->maxAllowedDepth) {
						Logger::log("A profundidade %d foi atingida e nenhuma solucao foi encontrada\n", this->maxAllowedDepth); 
						break;
					}

					expandNode(node);

				}

			};


		}; /* class EightPuzzleBestFirstSearchEngine */

	} /* namespace week4 */

} /* namespace pel216 */

#endif /* __8PUZZLE_BEST_FIRST_SEARCH_H__ */
