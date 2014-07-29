#pragma once

#ifndef __8PUZZLE_HILL_CLIMBING_H__
#define __8PUZZLE_HILL_CLIMBING_H__

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
		 * Classe que representa a busca <i>hill climbing</i>.
		 *
		 * @author arrebola
		 */
		class EightPuzzleHillClimbingSearchEngine : public SearchEngine<EightPuzzleNode> {

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

					size_t heuristic = child->h(this->goalState, this->heuristicType);

					EightPuzzleNode *childNode = new EightPuzzleNode(child, state, node->getDepth() + 1, heuristic);

					// determina se a heur�stica � melhor que a heur�stica do n� pai 
					bool discard = isKnownNode(childNode) || (heuristic > node->getHeuristic());

					if (this->debug) {
						Logger::logToFile("> Estado #%d: %s (%s)\n", (idx + 1),  child->toString().c_str(), (discard ? "D" : "M"));
					}

					if (discard) {
						continue;
					}

					addKnownNode(childNode);
					this->queue->push_asc(childNode);

				}

			};

		public:
			/**
			 * Construtor padr�o.
			 *
			 * @param maxDepth
			 *				o <code>size_t</code> que representa a profundidade m�xima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 * @param heuristicType
			 *				o <code>int</code> que representa o tipo da heur�stica	
			 */
			EightPuzzleHillClimbingSearchEngine(IN size_t maxDepth = -1, IN bool debug = false, IN int heuristicType = H_MISPLACED_BLOCKS) : 
					SearchEngine("Hill Climbing Search") {
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
				size_t maxHeuristic = initialState->h(this->goalState, this->heuristicType);
				EightPuzzleNode *startingNode = new EightPuzzleNode(initialState, NULL, 0, maxHeuristic);

				this->queue->push_asc(startingNode);
				addKnownNode(startingNode);

				size_t iteractions = 0;
				size_t curHeuristic = 0;
				while (!this->queue->isEmpty() && curHeuristic <= maxHeuristic) { 

					iteractions++;

					if (this->debug) {
						this->queue->dumpToFile();
					}

					EightPuzzleNode *node = this->queue->pop();
					EightPuzzleState *state = node->getState();
					curHeuristic = node->getHeuristic();
					
					if (this->debug) {
						Logger::logToFile("\n");
						Logger::logToFile("#%d Visitando no %s...\n", iteractions, state->toString().c_str());
					}

					// verifica se o alvo foi atingido
					if (state->equals(goalState)) { 

						this->solutionDepth = node->getDepth();

						Logger::log("\n");
						Logger::log("!!! SOLUCAO ENCONTRADA !!! (em profundidade %d apos expandir %d nos)\n", 
							this->solutionDepth, this->expandedNodesCount);
						Logger::log("\n");

						do { /* constr�i o caminho da solu��o */
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

					// determina a profundidade m�xima foi atingida
					if (node->getDepth() == this->maxAllowedDepth) {
						Logger::log("A profundidade %d foi atingida e nenhuma solucao foi encontrada\n", this->maxAllowedDepth); 
						break;
					}

					expandNode(node);

				}

			};

		}; /* class EightPuzzleHillClimbingSearchEngine */

	} /* namespace week4 */

} /* namespace pel216 */

#endif /* __8PUZZLE_HILL_CLIMBING_H__ */
