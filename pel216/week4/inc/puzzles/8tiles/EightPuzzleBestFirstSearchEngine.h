#pragma once

#ifndef __8PUZZLE_BEST_FIRST_SEARCH_H__
#define __8PUZZLE_BEST_FIRST_SEARCH_H__

#include <list>

#include <vector>
#include <map>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/queue/PriorityQueue.h>

#include <inc/search/SearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleNode.h>

using namespace pel216::commons;
using namespace pel216::week3;

namespace pel216 {

	namespace week4 {

		/**
		 * Classe que representa a busca da melhor opção (<i>best-first-search</i>) utilizando a heurística de blocos fora do lugar.
		 *
		 * @author arrebola
		 */
		class EightPuzzleBestFirstSearchEngine : public SearchEngine<EightPuzzleNode> {

		private:
			PriorityQueue *queue;
			EightPuzzleState *goalState;

		protected:
			/**
			 * @see pel216::week3::SearchEngine::expandNode()
			 */
			virtual void expandNode(EightPuzzleNode *node) {

				EightPuzzleState *state = node->getState();

				state->expand();
				this->expandedNodesCount++;

				std::vector<EightPuzzleState*> children = state->getChildren();
				size_t len = children.size();
				for (size_t idx = 0; idx < len; idx++) {
					EightPuzzleState *child = children.at(idx);
					size_t h = child->h(this->goalState, this->heuristicType);
					EightPuzzleNode *childNode = new EightPuzzleNode(child, state, node->getDepth() + 1, h);
					this->queue->push_asc(childNode);
				}

			};

		public:
			/**
			 * Construtor padrão.
			 *
			 * @param maxDepth
			 *				o <code>size_t</code> que representa a profundidade máxima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 * @param heuristicType
			 *				o <code>int</code> que representa o tipo da heurística	
			 */
			EightPuzzleBestFirstSearchEngine(IN size_t maxDepth = -1, IN bool debug = false, IN int heuristicType = H_MISPLACED_BLOCKS) : 
					SearchEngine("Best First Search") {
				setup(maxDepth, debug, heuristicType);
				this->queue = new PriorityQueue();
			};

			/**
			 * @see pel216::week3::SearchEngine::search()
			 */
			virtual void doSearch() {

				this->solutionDepth = 0;
				this->expandedNodesCount = 0;

				EightPuzzleNode *goalNode = getGoalNode();
				this->goalState = goalNode->getState();
				
				EightPuzzleState *initialState = startingNode->getState();
				EightPuzzleNode *startingNode = new EightPuzzleNode(
					initialState, NULL, 0, initialState->h(this->goalState, this->heuristicType));

				this->queue->push_asc(startingNode);

				size_t iteractions = 0;
				while (!this->queue->isEmpty()) { 

					iteractions++;

					if (this->debug) {
						this->queue->dumpToFile();
					}

					EightPuzzleNode *node = this->queue->pop();
					EightPuzzleState *state = node->getState();
					
					bool discard = isKnownNode(node);

					if (this->debug) {
						Logger::logToFile("\n");
						Logger::logToFile("#%06d %s no %s...\n", 
							iteractions, (discard ? "Descartando" : "Visitando"), (state)->toString().c_str());
					}

					if (discard) {
						continue;
					}

					addKnownNode(node);

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
